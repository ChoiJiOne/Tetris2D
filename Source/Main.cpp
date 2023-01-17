#include <cstdint>
#include <memory>
#include <array>

#include <windows.h>
#include <d3d11_1.h>

#include "Macro.h"


/**
 * @brief 윈도우 메시지 핸들러입니다.
 * 
 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/writing-the-window-procedure
 * 
 * @param WindowHandle 윈도우 창에 대한 핸들입니다.
 * @param Message 윈도우 메시지 코드입니다.
 * @param WParam 윈도우 메시지의 추가 데이터입니다.
 * @param LParam 윈도우 메시지의 추가 데이터입니다.
 * 
 * @return 윈도우에 반환할 값입니다.
 */
LRESULT CALLBACK WindowMessageHandler(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
	case WM_CLOSE:
		DestroyWindow(WindowHandle);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(WindowHandle, Message, WParam, LParam);
	}

	return 0;
}


/**
 * @brief 테트리스 게임을 초기화 및 실행합니다.
 */
class Tetris
{
public:
	/**
	 * @brief 테트리스 게임의 기본 생성자입니다.
	 */
	Tetris() = default;


	/**
	 * @brief 테트리스 게임의 가상 소멸자입니다.
	 */
	virtual ~Tetris()
	{
		SAFE_RELEASE(RenderTargetView_);
		SAFE_RELEASE(SwapChain_);
		SAFE_RELEASE(Context_);
		SAFE_RELEASE(Device_);
	}


	/**
	 * @brief 테트리스 게임을 초기화합니다.
	 */
	void Init()
	{
		WNDCLASSEX WC;
		WC.cbSize = sizeof(WNDCLASSEX);
		WC.style = CS_HREDRAW | CS_VREDRAW;
		WC.lpfnWndProc = WindowMessageHandler;
		WC.cbClsExtra = 0;
		WC.cbWndExtra = 0;
		WC.hInstance = GetModuleHandle(nullptr);
		WC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		WC.hCursor = LoadCursor(NULL, IDC_ARROW);
		WC.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		WC.lpszMenuName = NULL;
		WC.lpszClassName = L"Tetris2D";
		WC.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		RegisterClassEx(&WC);

		RECT Rect = { 0, 0, 800, 600 };
		AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, FALSE);

		WindowHandle_ = CreateWindow(
			L"Tetris2D",
			L"Tetris2D",
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT, CW_USEDEFAULT,
			Rect.right - Rect.left, Rect.bottom - Rect.top,
			nullptr,
			nullptr,
			GetModuleHandle(nullptr),
			nullptr
		);

		ShowWindow(WindowHandle_, SW_SHOW);

		HRESULT HR = S_OK;
		uint32_t Width = Rect.right - Rect.left;
		uint32_t Height = Rect.bottom - Rect.top;

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
				std::size(FeatureLevels),
				D3D11_SDK_VERSION, 
				&Device_, 
				&FeatureLevel_, 
				&Context_
			);

			if (HR == E_INVALIDARG)
			{
				HR = D3D11CreateDevice(
					nullptr, 
					DriverType_,
					nullptr, 
					CreateDeviceFlags,
					&FeatureLevels[1],
					std::size(FeatureLevels) - 1,
					D3D11_SDK_VERSION, 
					&Device_,
					&FeatureLevel_,
					&Context_
				);
			}

			if (SUCCEEDED(HR)) break;
		}

		if (FAILED(HR)) return;

		IDXGIDevice* Device = nullptr;
		HR = Device_->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&Device));

		IDXGIAdapter* Adapter = nullptr;
		HR = Device->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&Adapter));

		IDXGIFactory* Factory = nullptr;
		HR = Adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferCount = 1;
		sd.BufferDesc.Width = Width;
		sd.BufferDesc.Height = Height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = WindowHandle_;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		//sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		sd.Windowed = TRUE;

		Factory->CreateSwapChain(Device_, &sd, &SwapChain_);

		SAFE_RELEASE(Factory);
		SAFE_RELEASE(Adapter);
		SAFE_RELEASE(Device);

		ID3D11Texture2D* BackBuffer = nullptr;
		HR = SwapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBuffer));
		if (FAILED(HR)) return;

		HR = Device_->CreateRenderTargetView(BackBuffer, nullptr, &RenderTargetView_);
		SAFE_RELEASE(BackBuffer);

		if (FAILED(HR)) return;

		Context_->OMSetRenderTargets(1, &RenderTargetView_, nullptr);

		// Setup the viewport
		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)Width;
		vp.Height = (FLOAT)Height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		
		Context_->RSSetViewports(1, &vp);
	}


	/**
	 * @brief 테트리스 게임을 실행합니다.
	 */
	void Run()
	{
		MSG msg = { 0 };
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				FLOAT Color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

				Context_->ClearRenderTargetView(RenderTargetView_, Color);
				SwapChain_->Present(0, 0);
			}
		}
	}


private:
	/**
	 * @brief 윈도우 창 핸들러입니다.
	 * 
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/creating-a-window
	 */
	HWND WindowHandle_ = nullptr;

	
	/**
	 * @brief 드라이버 타입입니다.
	 * 
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/d3dcommon/ne-d3dcommon-d3d_driver_type
	 */
	D3D_DRIVER_TYPE	DriverType_ = D3D_DRIVER_TYPE_NULL;


	/**
	 * @brief 디바이스가 대상으로 하는 기능입니다.
	 * 
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/d3dcommon/ne-d3dcommon-d3d_feature_level
	 */
	D3D_FEATURE_LEVEL FeatureLevel_ = D3D_FEATURE_LEVEL_11_0;


	/**
	 * @brief 리소스를 만들고 디스플레이 어댑터의 기능을 열거하는 데 사용합니다.
	 * 
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/direct3d11/overviews-direct3d-11-devices-intro
	 */
	ID3D11Device* Device_ = nullptr;


	/**
	 * @brief 디바이스가 소유한 리소스를 사용하여 파이프라인 상태를 설정하고 렌더링 명령을 생성하는 데 사용합니다.
	 * 
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/direct3d11/overviews-direct3d-11-devices-intro
	 */
	ID3D11DeviceContext* Context_ = nullptr;


	/**
	 * @brief 렌더링된 데이터를 출력에 표시하기 전에 저장합니다.
	 * 
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiswapchain
	 */
	IDXGISwapChain* SwapChain_ = nullptr;


	/**
	 * @brief 렌더링 중 엑세스 할 수 있는 리소스입니다.
	 * 
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11rendertargetview
	 */
	ID3D11RenderTargetView* RenderTargetView_ = nullptr;
};


/**
 * @brief Windows 애플리케이션 진입점입니다.
 * 
 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/winmain--the-application-entry-point
 * 
 * @param hInstance 인스턴스에 대한 핸들입니다.
 * @param hPrevInstance 아무 의미 없는 파라미터입니다.
 * @param CmdLine 명령줄 인수입니다.
 * @param CmdShow 기본 애플리케이션 창을 최소화할지, 최대화할지 또는 정상적으로 표시할지를 나타내는 플래그입니다.
 * 
 * @return 다른 프로그램에 전달할 수 있는 상태 코드를 반환합니다.
 */
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR CmdLine, int32_t CmdShow)
{
	auto Game = std::make_unique<Tetris>();
	Game->Init();
	Game->Run();

	return 0;
}