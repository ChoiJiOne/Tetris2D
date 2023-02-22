#include "GraphicsManager.h"
#include "CommandLineManager.h"
#include "Font.h"
#include "Window.h"
#include "Shader.h"
#include "Math.hpp"
#include "Texture2D.h"
#include "Primitive2DRenderShader.h"
#include "Texture2DRenderShader.h"
#include "Text2DRenderShader.h"

#include <array>
#include <cstdint>
#include <windows.h>

void GraphicsManager::Setup(Window* RenderTargetWindow)
{
	RenderTargetWindow_ = RenderTargetWindow;

	CHECK_HR(CreateDeviceAndContext(RenderTargetWindow_->GetHandle()), "failed to create device and context");
	CHECK_HR(CreateSwapChain(RenderTargetWindow_->GetHandle()), "failed to create swapchain");
	CHECK_HR(CreateRenderTargetView(), "failed to create render target view");
	CHECK_HR(CreateDepthStencilView(), "failed to create depth stencil view");
	CHECK_HR(CreateDepthStencilState(&DepthStencilState_["EnableZ"], true, true), "failed to create enable z depth stencil state");
	CHECK_HR(CreateDepthStencilState(&DepthStencilState_["DisableZ"], false, true), "failed to create disable z depth stencil state");
	CHECK_HR(CreateBlendState(&BlendState_["Alpha"], true), "failed to create alpha blend state");
	CHECK_HR(CreateRasterizerState(&RasterizerState_["Fill"], false, true), "failed to create fill mode rasterizer state");
	CHECK_HR(CreateRasterizerState(&RasterizerState_["Wireframe"], false, false), "failed to create wireframe mode rasterizer state");


	std::wstring ShaderPath = CommandLineManager::Get().GetValue(L"-Shader");

	Shader_["Primitive"] = std::make_unique<Primitive2DRenderShader>(
		Device_,
		ShaderPath + L"Primitive2DRenderVS.hlsl",
		ShaderPath + L"Primitive2DRenderPS.hlsl"
	);

	Shader_["Texture"] = std::make_unique<Texture2DRenderShader>(
		Device_,
		ShaderPath + L"Texture2DRenderVS.hlsl",
		ShaderPath + L"Texture2DRenderPS.hlsl"
	);

	Shader_["Text"] = std::make_unique<Text2DRenderShader>(
		Device_,
		ShaderPath + L"Text2DRenderVS.hlsl",
		ShaderPath + L"Text2DRenderPS.hlsl"
	);

	float Width = 0.0f, Height = 0.0f;
	GetBackBufferSize(Width, Height);
	SetViewport(0.0f, 0.0f, Width, Height);

	Matrix4x4F OrthoMatrix = GetOrthographicMatrix(Width, Height, 0.0001f, 100.0f);

	Primitive2DRenderShader* PrimitiveShader = reinterpret_cast<Primitive2DRenderShader*>(Shader_["Primitive"].get());
	PrimitiveShader->SetProjectionMatrix(OrthoMatrix);

	Texture2DRenderShader* TextureShader = reinterpret_cast<Texture2DRenderShader*>(Shader_["Texture"].get());
	TextureShader->SetProjectionMatrix(OrthoMatrix);

	Text2DRenderShader* TextShader = reinterpret_cast<Text2DRenderShader*>(Shader_["Text"].get());
	TextShader->SetProjectionMatrix(OrthoMatrix);
}

void GraphicsManager::Cleanup()
{
	if (RenderTargetWindow_->IsFullScreen() && SwapChain_)
	{
		CHECK_HR(SwapChain_->SetFullscreenState(false, nullptr), "failed to set full screen state");
	}

	for (auto& ManageShader : Shader_)
	{
		ManageShader.second.reset();
	}

	for (auto& DeptnStencilState : DepthStencilState_)
	{
		SAFE_RELEASE(DeptnStencilState.second);
	}

	for (auto& BlendState : BlendState_)
	{
		SAFE_RELEASE(BlendState.second);
	}

	for (auto& RasterizerState : RasterizerState_)
	{
		SAFE_RELEASE(RasterizerState.second);
	}

	SAFE_RELEASE(DepthStencilView_);
	SAFE_RELEASE(DepthStencilBuffer_);
	SAFE_RELEASE(RenderTargetView_);
	SAFE_RELEASE(SwapChain_);

	if (Context_)
	{
		Context_->ClearState();
	}

	SAFE_RELEASE(Context_);
	SAFE_RELEASE(Device_);
}

void GraphicsManager::GetBackBufferSize(float& Width, float& Height)
{
	RenderTargetWindow_->GetSize<float>(Width, Height);
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
	CHECK_HR(CreateDepthStencilView(), "failed to create depth stencil view");

	SetViewport(0.0f, 0.0f, static_cast<float>(BackBufferWidth), static_cast<float>(BackBufferHeight));

	Matrix4x4F OrthoMatrix = GetOrthographicMatrix(
		static_cast<float>(BackBufferWidth), 
		static_cast<float>(BackBufferHeight),
		0.0001f, 
		100.0f
	);

	Primitive2DRenderShader* PrimitiveShader = reinterpret_cast<Primitive2DRenderShader*>(Shader_["Primitive"].get());
	PrimitiveShader->SetProjectionMatrix(OrthoMatrix);

	Texture2DRenderShader* TextureShader = reinterpret_cast<Texture2DRenderShader*>(Shader_["Texture"].get());
	TextureShader->SetProjectionMatrix(OrthoMatrix);

	Text2DRenderShader* TextShader = reinterpret_cast<Text2DRenderShader*>(Shader_["Text"].get());
	TextShader->SetProjectionMatrix(OrthoMatrix);
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

void GraphicsManager::SetDepthBuffer(bool bIsEnable)
{
	ID3D11DepthStencilState* DepthStencilState = bIsEnable ? DepthStencilState_["EnableZ"] : DepthStencilState_["DisableZ"];

	Context_->OMSetDepthStencilState(DepthStencilState, 1);
}

void GraphicsManager::SetAlphaBlend(bool bIsEnable)
{
	ID3D11BlendState* BlendState = bIsEnable ? BlendState_["Alpha"] : nullptr;
	
	Context_->OMSetBlendState(BlendState, nullptr, 0xFFFFFFFF);
}

void GraphicsManager::SetFillMode(bool bIsEnable)
{
	ID3D11RasterizerState* RasterizerState = bIsEnable ? RasterizerState_["Fill"] : RasterizerState_["Wireframe"];

	Context_->RSSetState(RasterizerState);
}

void GraphicsManager::Clear(const LinearColor& Color, float Depth, uint8_t Stencil)
{
	Context_->OMSetRenderTargets(1, &RenderTargetView_, DepthStencilView_);

	float ColorRGBA[4] = { Color.x, Color.y, Color.z, Color.w };

	Context_->ClearRenderTargetView(RenderTargetView_, ColorRGBA);
	Context_->ClearDepthStencilView(DepthStencilView_, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, Depth, Stencil);
}

void GraphicsManager::Present(bool bIsVSync)
{
	CHECK_HR(SwapChain_->Present(static_cast<uint32_t>(bIsVSync), 0), "failed to present backbuffer");
}

void GraphicsManager::DrawPoint2D(const Vec2f& Position, const LinearColor& Color)
{
	Primitive2DRenderShader* PrimitiveShader = reinterpret_cast<Primitive2DRenderShader*>(Shader_["Primitive"].get());

	PrimitiveShader->RenderPoint(Context_, Vec3f(Position.x, Position.y, 0.0f), Color);
}

void GraphicsManager::DrawLine2D(const Vec2f& PositionFrom, const LinearColor& ColorFrom, const Vec2f& PositionTo, const LinearColor& ColorTo)
{
	Primitive2DRenderShader* PrimitiveShader = reinterpret_cast<Primitive2DRenderShader*>(Shader_["Primitive"].get());

	PrimitiveShader->RenderLine(
		Context_,
		Vec3f(PositionFrom.x, PositionFrom.y, 0.0f), ColorFrom,
		Vec3f(  PositionTo.x,   PositionTo.y, 0.0f), ColorTo
	);
}

void GraphicsManager::DrawFillTriangle2D(const Vec2f& PositionFrom, const LinearColor& ColorFrom, const Vec2f& PositionBy, const LinearColor& ColorBy, const Vec2f& PositionTo, const LinearColor& ColorTo)
{
	Primitive2DRenderShader* PrimitiveShader = reinterpret_cast<Primitive2DRenderShader*>(Shader_["Primitive"].get());

	PrimitiveShader->RenderFillTriangle(
		Context_,
		Vec3f(PositionFrom.x, PositionFrom.y, 0.0f), ColorFrom,
		Vec3f(  PositionBy.x,   PositionBy.y, 0.0f), ColorBy,
		Vec3f(  PositionTo.x,   PositionTo.y, 0.0f), ColorTo
	);
}

void GraphicsManager::DrawWireframeTriangle2D(const Vec2f& PositionFrom, const LinearColor& ColorFrom, const Vec2f& PositionBy, const LinearColor& ColorBy, const Vec2f& PositionTo, const LinearColor& ColorTo)
{
	Primitive2DRenderShader* PrimitiveShader = reinterpret_cast<Primitive2DRenderShader*>(Shader_["Primitive"].get());

	PrimitiveShader->RenderWireframeTriangle(
		Context_,
		Vec3f(PositionFrom.x, PositionFrom.y, 0.0f), ColorFrom,
		Vec3f(  PositionBy.x,   PositionBy.y, 0.0f), ColorBy,
		Vec3f(  PositionTo.x,   PositionTo.y, 0.0f), ColorTo
	);
}

void GraphicsManager::DrawFillQuad2D(const Vec2f& PositionFrom, const LinearColor& ColorFrom, const Vec2f& PositionBy0, const LinearColor& ColorBy0, const Vec2f& PositionBy1, const LinearColor& ColorBy1, const Vec2f& PositionTo, const LinearColor& ColorTo)
{
	Primitive2DRenderShader* PrimitiveShader = reinterpret_cast<Primitive2DRenderShader*>(Shader_["Primitive"].get());

	PrimitiveShader->RenderFillQuad(
		Context_,
		Vec3f(PositionFrom.x, PositionFrom.y, 0.0f), ColorFrom,
		Vec3f( PositionBy0.x,  PositionBy0.y, 0.0f), ColorBy0,
		Vec3f( PositionBy1.x,  PositionBy1.y, 0.0f), ColorBy1,
		Vec3f(  PositionTo.x,   PositionTo.y, 0.0f), ColorTo
	);
}

void GraphicsManager::DrawWireframeQuad2D(const Vec2f& PositionFrom, const LinearColor& ColorFrom, const Vec2f& PositionBy0, const LinearColor& ColorBy0, const Vec2f& PositionBy1, const LinearColor& ColorBy1, const Vec2f& PositionTo, const LinearColor& ColorTo)
{
	Primitive2DRenderShader* PrimitiveShader = reinterpret_cast<Primitive2DRenderShader*>(Shader_["Primitive"].get());

	PrimitiveShader->RenderWireframeQuad(
		Context_,
		Vec3f(PositionFrom.x, PositionFrom.y, 0.0f), ColorFrom,
		Vec3f( PositionBy0.x,  PositionBy0.y, 0.0f), ColorBy0,
		Vec3f( PositionBy1.x,  PositionBy1.y, 0.0f), ColorBy1,
		Vec3f(  PositionTo.x,   PositionTo.y, 0.0f), ColorTo
	);
}

void GraphicsManager::DrawTexture2D(Texture2D& Texture, const Vec2f& Center, float Width, float Height, float Rotate)
{
	Texture2DRenderShader* TextureShader = reinterpret_cast<Texture2DRenderShader*>(Shader_["Texture"].get());

	TextureShader->SetWorldMatrix(GetRotateMatrix(Rotate));
	TextureShader->RenderTexture2D(Context_, Texture, Vec3f(Center.x, Center.y, 0.0f), Width, Height);
}

void GraphicsManager::DrawText2D(Font& FontResource, const std::wstring& Text, const Vec2f& Center, const LinearColor& Color)
{
	Text2DRenderShader* TextShader = reinterpret_cast<Text2DRenderShader*>(Shader_["Text"].get());

	TextShader->RenderText2D(Context_, FontResource, Text, Vec3f(Center.x, Center.y, 0.0f), Color);
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

HRESULT GraphicsManager::CreateDepthStencilView()
{
	SAFE_RELEASE(DepthStencilView_);
	SAFE_RELEASE(DepthStencilBuffer_);

	HRESULT HR = S_OK;

	uint32_t WindowWidth = 0, WindowHeight = 0;
	RenderTargetWindow_->GetSize<uint32_t>(WindowWidth, WindowHeight);

	D3D11_TEXTURE2D_DESC DepthStencilBufferDesc = {};

	DepthStencilBufferDesc.Width = WindowWidth;
	DepthStencilBufferDesc.Height = WindowHeight;
	DepthStencilBufferDesc.MipLevels = 1;
	DepthStencilBufferDesc.ArraySize = 1;
	DepthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthStencilBufferDesc.SampleDesc.Count = 1;
	DepthStencilBufferDesc.SampleDesc.Quality = 0;
	DepthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthStencilBufferDesc.CPUAccessFlags = 0;
	DepthStencilBufferDesc.MiscFlags = 0;

	HR = Device_->CreateTexture2D(&DepthStencilBufferDesc, nullptr, &DepthStencilBuffer_);

	if (SUCCEEDED(HR))
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDesc = {};

		DepthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		DepthStencilViewDesc.Texture2D.MipSlice = 0;

		HR = Device_->CreateDepthStencilView(DepthStencilBuffer_, &DepthStencilViewDesc, &DepthStencilView_);
	}

	return HR;
}

HRESULT GraphicsManager::CreateDepthStencilState(ID3D11DepthStencilState** DepthStencilState, bool bIsEnableDepth, bool bIsEnableStencil)
{
	D3D11_DEPTH_STENCIL_DESC DepthStencilStateDesc = {};

	DepthStencilStateDesc.DepthEnable = bIsEnableDepth;
	DepthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;

	DepthStencilStateDesc.StencilEnable = bIsEnableStencil;
	DepthStencilStateDesc.StencilReadMask = 0xFF;
	DepthStencilStateDesc.StencilWriteMask = 0xFF;

	DepthStencilStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	DepthStencilStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	DepthStencilStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	DepthStencilStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	return Device_->CreateDepthStencilState(&DepthStencilStateDesc, DepthStencilState);
}

HRESULT GraphicsManager::CreateBlendState(ID3D11BlendState** BlendState, bool bIsEnable)
{
	D3D11_BLEND_DESC BlendStateDesc = {};

	BlendStateDesc.RenderTarget[0].BlendEnable = true;
	BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	return Device_->CreateBlendState(&BlendStateDesc, BlendState);
}

HRESULT GraphicsManager::CreateRasterizerState(ID3D11RasterizerState** RasterizerState, bool bIsEnableCull, bool bIsEnableFill)
{
	D3D11_RASTERIZER_DESC RasterizerDesc;

	RasterizerDesc.AntialiasedLineEnable = false;
	RasterizerDesc.CullMode = (bIsEnableCull ? D3D11_CULL_BACK : D3D11_CULL_NONE);
	RasterizerDesc.DepthBias = 0;
	RasterizerDesc.DepthBiasClamp = 0.0f;
	RasterizerDesc.DepthClipEnable = true;
	RasterizerDesc.FillMode = (bIsEnableFill ? D3D11_FILL_SOLID : D3D11_FILL_WIREFRAME);
	RasterizerDesc.FrontCounterClockwise = false;
	RasterizerDesc.MultisampleEnable = false;
	RasterizerDesc.ScissorEnable = false;
	RasterizerDesc.SlopeScaledDepthBias = 0.0f;

	return Device_->CreateRasterizerState(&RasterizerDesc, RasterizerState);
}
