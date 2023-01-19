#include "GraphicsManager.h"
#include "Window.h"

#include <array>
#include <cstdint>
#include <windows.h>

void GraphicsManager::Init(Window* RenderTargetWindow)
{
	RenderTargetWindow_ = RenderTargetWindow;

	CHECK_HR(CreateDeviceAndContext(RenderTargetWindow_->GetHandle()), "failed to create device and context");
	CHECK_HR(CreateSwapChain(RenderTargetWindow_->GetHandle()), "failed to create swapchain");
	CHECK_HR(CreateRenderTargetView(), "failed to create render target view");
}

void GraphicsManager::Cleanup()
{
	if (RenderTargetWindow_->IsFullScreen())
	{
		CHECK_HR(SwapChain_->SetFullscreenState(false, nullptr), "failed to set full screen state");
	}

	SAFE_RELEASE(RenderTargetView_);
	SAFE_RELEASE(SwapChain_);

	if (Context_)
	{
		Context_->ClearState();
	}

	SAFE_RELEASE(Context_);
	SAFE_RELEASE(Device_);
}

void GraphicsManager::Resize()
{
	uint32_t BackBufferWidth = 0, BackBufferHeight = 0;
	DXGI_FORMAT BackBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
	uint32_t BackBufferCount = 2;

	SAFE_RELEASE(RenderTargetView_);

	RenderTargetWindow_->GetSize<uint32_t>(BackBufferWidth, BackBufferHeight);

	CHECK_HR(SwapChain_->ResizeBuffers(BackBufferCount, BackBufferWidth, BackBufferHeight,BackBufferFormat, 0), "failed to resize buffer");
	CHECK_HR(CreateRenderTargetView(), "failed to create render target view");
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

void GraphicsManager::SetScreenViewport(float MinDepth, float MaxDepth)
{
	float Width = 0.0f, Height = 0.0f;
	RenderTargetWindow_->GetSize<float>(Width, Height);

	SetViewport(0.0f, 0.0f, Width, Height, MinDepth, MaxDepth);
}

void GraphicsManager::Clear(float Red, float Green, float Blue, float Alpha)
{
	Context_->OMSetRenderTargets(1, &RenderTargetView_, nullptr);

	float ColorRGBA[4] = { Red, Green, Blue, Alpha };
	Context_->ClearRenderTargetView(RenderTargetView_, ColorRGBA);
}

void GraphicsManager::Present(bool bIsVSync)
{
	CHECK_HR(SwapChain_->Present(static_cast<uint32_t>(bIsVSync), 0), "failed to present backbuffer");
}

GraphicsManager::~GraphicsManager()
{
	Cleanup();
}

HRESULT GraphicsManager::CreateDeviceAndContext(HWND WindowHandle)
{
	SAFE_RELEASE(Context_);
	SAFE_RELEASE(Device_);

	HRESULT HR = S_OK;

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
	SAFE_RELEASE(SwapChain_);

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

	uint32_t WindowWidth = 0, WindowHeight = 0;
	RenderTargetWindow_->GetSize<uint32_t>(WindowWidth, WindowHeight);

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
	SwapChainDesc.Windowed = !RenderTargetWindow_->IsFullScreen();

	HR = Factory->CreateSwapChain(Device_, &SwapChainDesc, &SwapChain_);

	HR = Factory->MakeWindowAssociation(WindowHandle, DXGI_MWA_NO_ALT_ENTER);

	SAFE_RELEASE(Factory);
	SAFE_RELEASE(Adapter);
	SAFE_RELEASE(Device);

	return HR;
}

HRESULT GraphicsManager::CreateRenderTargetView()
{
	SAFE_RELEASE(RenderTargetView_);

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
