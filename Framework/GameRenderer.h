#pragma once

// 표준 라이브러리 및 SDL2를 사용하기 위한 헤더 선언을 추가합니다.
#include "CommonHeader.h"

// 수학 기능을 사용하기 위한 헤더 선언을 추가합니다.
#include "MathUtil.h"


// 렌더링을 수행하는 클래스입니다.
class GameRenderer
{
public:
	// 생성자입니다.
	GameRenderer() = default;


	// 가상 소멸자입니다.
	virtual ~GameRenderer();


	// 복사 생성자 및 대입연산자입니다.
	// 앝은 복사 이슈가 발생할 가능성이 있어 처음부터 사용할 수 없도록 삭제합니다.
	GameRenderer(GameRenderer&& InInstance) = delete;
	GameRenderer& operator=(GameRenderer&& InInstance) = delete;


	// 복사 생성자 및 대입연산자입니다.
	// 앝은 복사 이슈가 발생할 가능성이 있어 처음부터 사용할 수 없도록 삭제합니다.
	GameRenderer(const GameRenderer& InInstance) = delete;
	GameRenderer& operator=(const GameRenderer& InInstance) = delete;


	// 렌더러를 초기화합니다.
	// 
	// @param InWindow - SDL_Window의 포인터입니다.
	// @throws - 렌더러 생성에 실패할 경우, C++ 표준 예외를 반환합니다.
	void Init(SDL_Window* InWindow);


	// 프레임 렌더링을 시작합니다.
	//
	// @param InColor - 벡버퍼를 비울 색상입니다.
	// @throws - 백버퍼 초기화에 실패할 경우, C++ 표준 예외를 반환합니다.
	void BeginFrame(const LinearColor& InColor);


	// 프레임 렌더링을 종료하고, 벡버퍼를 화면에 표시합니다.
	void EndFrame();


	// SDL_Renderer 포인터를 반환합니다.
	//
	// @return - SDL_Renderer 포인터를 반환합니다. 
	SDL_Renderer* GetRenderer() noexcept { return Renderer; }


	// 벡버퍼에 2D 점을 그립니다.
	//
	// @param InPosition - 점의 위치입니다.
	// @param InColor - 점의 색상입니다.
	// @throws - 렌더링에 실패할 경우, C++ 표준 예외를 반환합니다.
	void DrawPoint2D(const Vec2i& InPosition, const LinearColor& InColor);


	// 벡버퍼에 2D 선을 그립니다.
	// 
	// @param InP0 - 선분의 한 끝점입니다.
	// @param InP1 - 선분의 InP0이 아닌 한 끝점입니다.
	// @param InColor - 선분의 색상입니다.
	// @throws - 렌더링에 실패할 경우, C++ 표준 예외를 반환합니다.
	void DrawLine2D(const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor);


	// 벡버퍼에 2D 사각형을 그립니다.
	// 
	// @param InP0 - 사각형의 왼쪽 상단점입니다.
	// @param InP1 - 사각형의 오른쪽 하단점입니다.
	// @param InColor - 사각형의 색상입니다.
	// @throws - 렌더링에 실패할 경우, C++ 표준 예외를 반환합니다.
	void DrawWireframeRectangle2D(const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor);


	// 벡버퍼에 2D 사각형을 그립니다.
	// 
	// @param InCenterPosition - 사각형의 중심이 위치할 화면상의 좌표입니다.
	// @param InWidth - 사각형의 가로 길이입니다.
	// @param InHeight - 사각형의 세로 길이입니다.
	// @param InColor - 사각형의 색상입니다.
	// @throws - 렌더링에 실패할 경우, C++ 표준 예외를 반환합니다.
	void DrawWireframeRectangle2D(const Vec2i& InCenterPosition, int32_t InWidth, int32_t InHeight, const LinearColor& InColor);


	// 벡버퍼에 채움 2D 사각형을 그립니다.
	// 
	// @param InP0 - 채움 사각형의 왼쪽 상단점입니다.
	// @param InP1 - 채움 사각형의 오른쪽 하단점입니다.
	// @param InColor - 채움 사각형의 색상입니다.
	// @throws - 렌더링에 실패할 경우, C++ 표준 예외를 반환합니다.
	void DrawRectangle2D(const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor);


	// 벡버퍼에 채움 2D 사각형을 그립니다.
	// 
	// @param InCenterPosition - 사각형의 중심이 위치할 화면상의 좌표입니다.
	// @param InWidth - 사각형의 가로 길이입니다.
	// @param InHeight - 사각형의 세로 길이입니다.
	// @param InColor - 사각형의 색상입니다.
	// @throws - 렌더링에 실패할 경우, C++ 표준 예외를 반환합니다.
	void DrawRectangle2D(const Vec2i& InCenterPosition, int32_t InWidth, int32_t InHeight, const LinearColor& InColor);


	// 백버퍼에 텍스처를 그립니다.
	// 
	// @param InCenterPosition - 텍스처의 중심이 위치할 화면상의 좌표입니다.
	// @param InTexture - 백버퍼에 그릴 텍스처입니다.
	// @param InWidthScaling - 렌더링할 텍스처의 원본 텍스처 대비 가로 크기 비율입니다.
	// @param InHeightScaling - 렌더링할 텍스처의 원본 텍스처 대비 세로 크기 비율입니다.
	// @throws - 렌더링에 실패할 경우, C++ 표준 예외를 반환합니다.
	void DrawTexture2D(const Vec2i& InCenterPosition, const class GameTexture2D& InTexture, float InWidthScaling = 1.0f, float InHeightScaling = 1.0f);


	// 벡버퍼에 UTF-16 텍스트를 그립니다.
	//
	// @param InCenterPosition - 렌더링 할 텍스트의 중심 좌표입니다.
	// @param InFont - 렌더링 시 참조할 폰트입니다.
	// @param InText - 렌더링할 UTF-16 텍스트입니다.
	// @param InColor - 렌더링할 텍스트의 색상입니다.
	// @throws - 렌더링에 실패할 경우, C++ 표준 예외를 반환합니다.
	void DrawText2D(const Vec2i& InCenterPosition, const class GameFont& InFont, const std::wstring& InText, const LinearColor& InColor);
	

private:
	// SDL 렌더러의 컬러 상태를 설정합니다.
	// 
	// @param InColor - 변경할 SDL 렌더러의 컬러 상태입니다.
	// @throws - 렌더 색상 설정에 실패할 경우, C++ 표준 예외를 반환합니다.
	void SetDrawColor(const LinearColor& InColor);


	// SDL 렌더러의 컬러 상태를 설정합니다.
	// 
	// @param InRed - 변경할 SDL 렌더러의 컬러 Red값 입니다.
	// @param InGreen - 변경할 SDL 렌더러의 컬러 Green값 입니다.
	// @param InBlue - 변경할 SDL 렌더러의 컬러 Blue값 입니다.
	// @param InAlpha - 변경할 SDL 렌더러의 컬러 Alpha값 입니다.
	// @throws - 렌더 색상 설정에 실패할 경우, C++ 표준 예외를 반환합니다.
	void SetDrawColor(uint8_t InRed, uint8_t InGreen, uint8_t InBlue, uint8_t InAlpha);


private:
	// 렌더러 초기화 여부입니다.
	bool bIsInitialize = false;


	// SDL_Renderer의 포인터입니다.
	SDL_Renderer* Renderer = nullptr;
};