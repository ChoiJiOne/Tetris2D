#include "GraphicsManager.h"

#include <array>
#include <cstdint>
#include <windows.h>

void GraphicsManager::Init()
{
	CleanupAllProperties();
	InitAllProperties();
}

void GraphicsManager::Cleanup()
{
	CleanupAllProperties();
}

void GraphicsManager::SetViewport(float TopLeftX, float TopLeftY, float Width, float Height, float MinDepth, float MaxDepth)
{
	D3D11_VIEWPORT Viewport = {};

	Viewport.TopLeftX = TopLeftX;
	Viewport.TopLeftY = TopLeftY;
	Viewport.Width = Width;
	Viewport.Height = Height;
	Viewport.MinDepth = MinDepth;
	Viewport.MaxDepth = MaxDepth;

	Context_->RSSetViewports(1, &Viewport);
}

void GraphicsManager::Clear(float Red, float Green, float Blue, float Alpha)
{
	Context_->OMSetRenderTargets(1, &RenderTargetView_, nullptr);

	float ColorRGBA[4] = { Red, Green, Blue, Alpha };
	Context_->ClearRenderTargetView(RenderTargetView_, ColorRGBA);
}

void GraphicsManager::Present(bool bIsVSync)
{
	HRESULT HR = SwapChain_->Present(static_cast<uint32_t>(bIsVSync), 0);
}

GraphicsManager::~GraphicsManager()
{
	CleanupAllProperties();
}

void GraphicsManager::InitAllProperties()
{
	HWND CurrentWindowHandle = GetForegroundWindow();
	HRESULT HR = S_OK;

	if (!Device_ && !Context_)
	{
		HR = CreateDeviceAndContext(CurrentWindowHandle);
		HR = CreateSwapChain(CurrentWindowHandle);
		HR = CreateRenderTargetView();
	}
}

void GraphicsManager::CleanupAllProperties()
{
	SAFE_RELEASE(RenderTargetView_);
	SAFE_RELEASE(SwapChain_);
	SAFE_RELEASE(Context_);
	SAFE_RELEASE(Device_);
}

HRESULT GraphicsManager::CreateDeviceAndContext(HWND WindowHandle)
{
	HRESULT HR = S_OK;

	RECT CurrentWindowRect = {};
	GetClientRect(WindowHandle, &CurrentWindowRect);

	uint32_t WindowWidth = static_cast<uint32_t>(CurrentWindowRect.right - CurrentWindowRect.left);
	uint32_t WindowHeight = static_cast<uint32_t>(CurrentWindowRect.bottom - CurrentWindowRect.top);

	uint32_t CreateDeviceFlags = 0;
#ifdef DEBUG
	CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	std::array<D3D_DRIVER_TYPE, 3> DriverTypes = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	std::array<D3D_FEATURE_LEVEL, 7> FeatureLevels = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	for (auto DriverType : DriverTypes)
	{
		DriverType_ = DriverType;

		HR = D3D11CreateDevice(
			nullptr,
			DriverType_,
			nullptr,
			CreateDeviceFlags,
			&FeatureLevels[0],
			static_cast<uint32_t>(std::size(FeatureLevels)),
			D3D11_SDK_VERSION,
			&Device_,
			&FeatureLevel_,
			&Context_
		);

		if (SUCCEEDED(HR)) break;
	}

	return HR;
}

HRESULT GraphicsManager::CreateSwapChain(HWND WindowHandle)
{
	HRESULT HR = S_OK;

	IDXGIDevice* Device = nullptr;
	IDXGIAdapter* Adapter = nullptr;
	IDXGIFactory* Factory = nullptr;

	HR = Device_->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&Device));
	if (SUCCEEDED(HR))
	{
		HR = Device->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&Adapter));
		if (SUCCEEDED(HR))
		{
			Adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));
		}
	}

	RECT CurrentWindowRect = {};
	GetClientRect(WindowHandle, &CurrentWindowRect);

	uint32_t WindowWidth = static_cast<uint32_t>(CurrentWindowRect.right - CurrentWindowRect.left);
	uint32_t WindowHeight = static_cast<uint32_t>(CurrentWindowRect.bottom - CurrentWindowRect.top);

	DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.BufferDesc.Width = WindowWidth;
	SwapChainDesc.BufferDesc.Height = WindowHeight;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = WindowHandle;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.Windowed = TRUE;

	HR = Factory->CreateSwapChain(Device_, &SwapChainDesc, &SwapChain_);

	SAFE_RELEASE(Factory);
	SAFE_RELEASE(Adapter);
	SAFE_RELEASE(Device);

	return HR;
}

HRESULT GraphicsManager::CreateRenderTargetView()
{
	HRESULT HR = S_OK;

	ID3D11Texture2D* BackBuffer = nullptr;
	HR = SwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBuffer));

	if (SUCCEEDED(HR))
	{
		HR = Device_->CreateRenderTargetView(BackBuffer, nullptr, &RenderTargetView_);
	}

	SAFE_RELEASE(BackBuffer);

	return HR;
}
