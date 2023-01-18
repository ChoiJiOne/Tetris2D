#pragma once

#include "Macro.h"

#include <d3d11.h>


/**
 * @brief 그래픽 관련 처리를 수행합니다.
 * 
 * @note 이 클래스는 싱글턴으로 헤더만 추가하면 바로 사용할 수 있습니다.
 */
class GraphicsManager
{
public:
	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GraphicsManager);


	/**
	 * @brief GraphicsManager의 인스턴스를 얻습니다.
	 * 
	 * @return GraphicsManager의 인스턴스 참조자를 반환합니다.
	 */
	static GraphicsManager& Get()
	{
		static GraphicsManager Instance;
		return Instance;
	}


	/**
	 * @brief GraphicsManager를 명시적으로 초기화합니다.
	 * 
	 * @throws 내부 리소스 생성에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Init();


	/**
	 * @brief GraphicsManager의 내부 요소를 명시적으로 정리합니다.
	 */
	void Cleanup();


	/**
	 * @brief 내부 버퍼 리소스의 크기를 변경합니다.
	 * 
	 * @throws 버퍼의 크기 변경에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Resize();


	/**
	 * @brief 파이프라인의 뷰 포트를 설정합니다.
	 * 
	 * @param TopLeftX 뷰 포트 왼쪽 상단의 X좌표입니다.
	 * @param TopLeftY 뷰 포트 왼쪽 상단의 Y좌표입니다.
	 * @param Width 뷰 포트의 가로 크기입니다.
	 * @param Height 뷰 포트의 세로 크기입니다.
	 * @param MinDepth 뷰 포트의 최소 깊이입니다. 기본 값은 0.0 입니다.
	 * @param MaxDepth 뷰 포트의 최대 깊이입니다. 기본 값은 1.0 입니다.
	 */
	void SetViewport(float TopLeftX, float TopLeftY, float Width, float Height, float MinDepth = 0.0f, float MaxDepth = 1.0f);


	/**
	 * @brief 백 버퍼를 초기화합니다.
	 * 
	 * @param Red 백 버퍼의 초기화할 빨강 색상입니다.
	 * @param Green 백 버퍼의 초기화할 초록 색상입니다.
	 * @param Blue 백 버퍼의 초기화할 파랑 색상입니다.
	 * @param Alpha 백 버퍼의 초기화할 알파 색상입니다.
	 */
	void Clear(float Red, float Green, float Blue, float Alpha);


	/**
	 * @brief 백 버퍼와 프론트 버퍼를 교환합니다.
	 * 
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiswapchain-present
	 * 
	 * @param bIsVSync 수직 동기화 여부를 확인합니다. 기본적으로 수직 동기화 처리합니다.
	 * 
	 * @throws 백 버퍼와 프론트 버퍼의 교환에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Present(bool bIsVSync = true);


private:
	/**
	 * @brief 그래픽 관련 처리를 수행하는 클래스의 생성자입니다.
	 * 
	 * @note 생성자는 아무런 동작도 수행하지 않습니다.
	 */
	GraphicsManager() = default;


	/**
	 * @brief 그래픽 관련 리소스를 정리하는 가상 소멸자입니다.
	 */
	virtual ~GraphicsManager();


	/**
	 * @brief 디바이스 및 컨텍스트를 생성합니다.
	 * 
	 * @param WindowHandle 대상이 되는 윈도우 핸들입니다.
	 * 
	 * @return 디바이스 및 컨텍스트의 생성 결과를 반환합니다. 성공했다면 S_OK, 그렇지 않다면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateDeviceAndContext(HWND WindowHandle);


	/**
	 * @brief 스왑 체인을 생성합니다.
	 * 
	 * @param WindowHandle 대상이 되는 윈도우 핸들입니다.
	 * 
	 * @return 스왑 체인 생성 결과를 반환합니다. 성공했다면 S_OK, 그렇지 않다면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateSwapChain(HWND WindowHandle);


	/**
	 * @brief 렌더 타겟 뷰를 생성합니다.
	 * 
	 * @return 렌더 타겟 뷰 생성 결과를 반환합니다. 성공했다면 S_OK, 그렇지 않다면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateRenderTargetView();


private:
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