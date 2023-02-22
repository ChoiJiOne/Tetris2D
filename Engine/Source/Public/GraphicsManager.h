#pragma once

#include "Macro.h"
#include "Color.h"

#include <memory>
#include <unordered_map>

#include <d3d11.h>

class Window;
class Texture2D;
class Font;
class Shader;


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
	 * @param RenderTargetWindow 렌더링 대상이 되는 윈도우의 포인터입니다.
	 * 
	 * @throws 내부 리소스 생성에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Setup(Window* RenderTargetWindow);


	/**
	 * @brief GraphicsManager의 내부 요소를 명시적으로 정리합니다.
	 */
	void Cleanup();


	/**
	 * @brief 리소스를 만들고 디스플레이 어댑터의 기능을 열거하는 데 사용하는 디바이스를 얻습니다.
	 * 
	 * @return 디바이스의 포인터를 반환합니다.
	 */
	ID3D11Device* GetDevice() { return Device_; }


	/**
	 * @brief 디바이스가 소유한 리소스를 사용하여 파이프라인 상태를 설정하고 렌더링 명령을 생성하는 데 사용하는 컨텍스트를 얻습니다.
	 * 
	 * @return 컨텍스트의 포인터를 반환합니다.
	 */
	ID3D11DeviceContext* GetContext() { return Context_; }


	/**
	 * @brief 백버퍼의 크기를 얻습니다.
	 * 
	 * @param Width[out] 벡버퍼의 가로 크기입니다.
	 * @param Height[out] 벡버퍼의 세로 크기입니다. 
	 */
	void GetBackBufferSize(float& Width, float& Height);


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
	 * @brief Z 버퍼 활성화 여부를 설정합니다.
	 * 
	 * @param bIsEnable Z 버퍼 활성화 여부입니다.
	 */
	void SetDepthBuffer(bool bIsEnable);


	/**
	 * @brief 알파 블랜딩 활성화 여부를 설정합니다.
	 * 
	 * @param bIsEnable 알파 블랜딩 활성화 여부입니다.
	 */
	void SetAlphaBlend(bool bIsEnable);


	/**
	 * @brief 채움 모드 활성화 여부를 설정합니다.
	 * 
	 * @note 비활성화 설정할 경우 와이어 프레임 모드로 설정됩니다.
	 * 
	 * @brief bIsEnble 채움 모드 활성화 여부입니다.
	 */
	void SetFillMode(bool bIsEnable);


	/**
	 * @brief 백 버퍼를 초기화합니다.
	 * 
	 * @param Color 초기화 할 색상입니다.
	 * @param Depth 깊이 버퍼의 초기화 할 값입니다. 기본 값은 1.0 입니다.
	 * @param Stencil 스텐실 버퍼의 초기화 할 값입니다. 기본 값은 0입니다.
	 */
	void Clear(const LinearColor& Color, float Depth = 1.0f, uint8_t Stencil = 0);


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


	/**
	 * @brief 화면에 2D 점을 그립니다.
	 * 
	 * @param Position 점의 위치입니다.
	 * @param Color 점의 색상입니다.
	 */
	void DrawPoint2D(const Vec2f& Position, const LinearColor& Color);


	/**
	 * @brief 화면에 2D 선을 그립니다.
	 * 
	 * @param PositionFrom 선의 시작점입니다.
	 * @param ColorFrom 선의 시작점 색상입니다.
	 * @param PositionTo 선의 끝점입니다.
	 * @param ColorTo 선의 끝점 색상입니다.
	 */
	void DrawLine2D(
		const Vec2f& PositionFrom, const LinearColor& ColorFrom,
		const Vec2f& PositionTo, const LinearColor& ColorTo
	);


	/**
	 * @brief 화면에 2D 채움 삼각형을 그립니다.
	 * 
	 * @param PositionFrom 삼각형 정점의 시작점입니다.
	 * @param ColorFrom 삼각형 정점의 시작점 색상입니다.
	 * @param PositionBy 삼각형 정점의 중간점입니다.
	 * @param ColorBy 삼각형 정점의 중간점 색상입니다.
	 * @param PositionTo 삼각형 정점의 끝점입니다.
	 * @param ColorTo 삼각형 정점의 끝점 색상입니다.
	 */
	void DrawFillTriangle2D(
		const Vec2f& PositionFrom, const LinearColor& ColorFrom,
		const Vec2f& PositionBy, const LinearColor& ColorBy,
		const Vec2f& PositionTo, const LinearColor& ColorTo
	);


	/**
	 * @brief 화면에 2D 와이어 프레임 삼각형을 그립니다.
	 *
	 * @param PositionFrom 삼각형 정점의 시작점입니다.
	 * @param ColorFrom 삼각형 정점의 시작점 색상입니다.
	 * @param PositionBy 삼각형 정점의 중간점입니다.
	 * @param ColorBy 삼각형 정점의 중간점 색상입니다.
	 * @param PositionTo 삼각형 정점의 끝점입니다.
	 * @param ColorTo 삼각형 정점의 끝점 색상입니다.
	 */
	void DrawWireframeTriangle2D(
		const Vec2f& PositionFrom, const LinearColor& ColorFrom,
		const Vec2f& PositionBy, const LinearColor& ColorBy,
		const Vec2f& PositionTo, const LinearColor& ColorTo
	);


	/**
	 * @brief 화면에 2D 채움 사각형을 그립니다.
	 * 
	 * @param PositionFrom 삼각형 정점의 시작점입니다.
	 * @param ColorFrom 삼각형 정점의 시작점 색상입니다.
	 * @param PositionBy0 삼각형 정점의 중간점입니다.
	 * @param ColorBy0 삼각형 정점의 중간점 색상입니다.
	 * @param PositionBy1 삼각형 정점의 중간점입니다.
	 * @param ColorBy1 삼각형 정점의 중간점 색상입니다.
	 * @param PositionTo 삼각형 정점의 끝점입니다.
	 * @param ColorTo 삼각형 정점의 끝점 색상입니다.
	 */
	void DrawFillQuad2D(
		const Vec2f& PositionFrom, const LinearColor& ColorFrom,
		const Vec2f& PositionBy0, const LinearColor& ColorBy0,
		const Vec2f& PositionBy1, const LinearColor& ColorBy1,
		const Vec2f& PositionTo, const LinearColor& ColorTo
	);


	/**
	 * @brief 화면에 2D 와이어 프레임 사각형을 그립니다.
	 *
	 * @param PositionFrom 삼각형 정점의 시작점입니다.
	 * @param ColorFrom 삼각형 정점의 시작점 색상입니다.
	 * @param PositionBy0 삼각형 정점의 중간점입니다.
	 * @param ColorBy0 삼각형 정점의 중간점 색상입니다.
	 * @param PositionBy1 삼각형 정점의 중간점입니다.
	 * @param ColorBy1 삼각형 정점의 중간점 색상입니다.
	 * @param PositionTo 삼각형 정점의 끝점입니다.
	 * @param ColorTo 삼각형 정점의 끝점 색상입니다.
	 */
	void DrawWireframeQuad2D(
		const Vec2f& PositionFrom, const LinearColor& ColorFrom,
		const Vec2f& PositionBy0, const LinearColor& ColorBy0,
		const Vec2f& PositionBy1, const LinearColor& ColorBy1,
		const Vec2f& PositionTo, const LinearColor& ColorTo
	);


	/**
	 * @brief 화면에 2D 텍스처를 그립니다.
	 * 
	 * @ntoe 회전각은 라디안 기준입니다.
	 * 
	 * @param Texture 렌더링 대상이 되는 2D 텍스처입니다.
	 * @param Center 텍스처의 중심 좌표입니다.
	 * @param Width 텍스처의 가로 크기입니다.
	 * @param Height 텍스처의 세로 크기입니다.
	 * @param Rotate 텍스처의 회전 각도입니다. 기본 값은 0.0입니다.
	 */
	void DrawTexture2D(Texture2D& Texture, const Vec2f& Center, float Width, float Height, float Rotate = 0.0f);


	/**
	 * @brief 화면에 2D 텍스트를 그립니다.
	 * 
	 * @param FontResource 텍스트를 렌더링할 때 참조할 폰트 리소스입니다.
	 * @param Text 렌더링할 텍스트입니다.
	 * @param Center 텍스처의 중심 좌표입니다.
	 * @param Color 텍스트의 색상입니다.
	 */
	void DrawText2D(Font& FontResource, const std::wstring& Text, const Vec2f& Center, const LinearColor& Color);


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


	/**
	 * @brief 깊이 스텐실 뷰를 생성합니다.
	 * 
	 * @return 깊이 스텐실 버퍼 생성 결과를 반환합니다. 성공했다면 S_OK, 그렇지 않다면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateDepthStencilView();


	/**
	 * @brief 깊이 스텐실 상태를 생성합니다.
	 * 
	 * @param DepthStencilState 생성한 깊이 스텐실 상태를 저장할 포인터입니다.
	 * @param bIsEnableDepth 깊이 버퍼 활성화 여부입니다.
	 * @param bIsEnableStencil 스텐실 버퍼 활성화 여부입니다.
	 * 
	 * @return 깊이 스텐실 상태 생성 결과를 반환합니다. 성공했다면 S_OK, 그렇지 않다면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateDepthStencilState(ID3D11DepthStencilState**DepthStencilState, bool bIsEnableDepth, bool bIsEnableStencil);


	/**
	 * @brief 블랜딩을 위한 블랜드 상태를 생성합니다.
	 * 
	 * @param BlendState 생성한 블랜드 상태를 저장할 포인터입니다.
	 * @param bIsEnable 블랜드 상태 활성화 여부입니다.
	 * 
	 * @return 블랜딩 상태 생성 결과를 반환합니다. 성공했다면 S_OK, 그렇지 않다면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateBlendState(ID3D11BlendState** BlendState, bool bIsEnable);


	/**
	 * @brief 레스터라이저 상태를 생성합니다.
	 * 
	 * @param RasterizerState 생성한 레스터라이저 상태를 저장할 포인터입니다.
	 * @param bIsEnableCull 컬링을 수행 여부입니다.
	 * @param bIsEnableFill 렌더링 시 채움 모드 수행 여부입니다.
	 * 
	 * @return 레스터라이저 상태 생성 결과를 반환합니다. 성공했다면 S_OK, 그렇지 않다면 그 이외의 값을 반환합니다.
	 */
	HRESULT CreateRasterizerState(ID3D11RasterizerState** RasterizerState, bool bIsEnableCull, bool bIsEnableFill);


private:
	/**
	 * @brief 렌더링 대상이 되는 윈도우입니다.
	 */
	Window* RenderTargetWindow_ = nullptr;


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


	/**
	 * @brief 깊이 스텐실 버퍼 리소스입니다.
	 * 
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11texture2d
	 */
	ID3D11Texture2D* DepthStencilBuffer_ = nullptr;


	/**
	 * @brief 깊이 스텐실 뷰 리소스입니다.
	 * 
	 * @see https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11depthstencilview
	 */
	ID3D11DepthStencilView* DepthStencilView_ = nullptr;


	/**
	 * @brief 렌더링 시 사용할 깊이 스텐실 상태입니다.
	 */
	std::unordered_map<std::string, ID3D11DepthStencilState*> DepthStencilState_;


	/**
	 * @brief 렌더링 시 사용할 블랜딩 상태입니다.
	 */
	std::unordered_map<std::string, ID3D11BlendState*> BlendState_;


	/**
	 * @brief 렌더링 시 사용할 레스터라이저 상태입니다.
	 */
	std::unordered_map<std::string, ID3D11RasterizerState*> RasterizerState_;


	/**
	 * @brief 렌더링 시 사용할 셰이더입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<Shader>> Shader_;
};