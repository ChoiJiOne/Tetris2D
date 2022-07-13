#pragma once

// 표준 라이브러리와 SDL2를 사용하기 위해서 헤더 파일을 추가합니다.
#include "Header.h"

// 수학 관련 기능을 사용하기 위해서 헤더 파일을 추가합니다.
#include "MathHelper.h"


/**
 * 그래픽스 클래스입니다.
 */
class Graphics
{
public:
	/**
	 * 그래픽스 클래스 생성자입니다.
	 */
	Graphics() = default;


	/**
	 * 그래픽스 클래스의 가상 소멸자입니다.
	 */
	virtual ~Graphics();


	/**
	 * Graphics 클래스를 초기화합니다.
	 * 
	 * @parma InWindow - SDL 윈도우의 포인터입니다.
	 * 
	 * @throws 초기화에 실패할 경우, C++ 표준 예외를 던집니다.
	 */
	void Initialize(SDL_Window* InWindow);


	/**
	 * SDL Renderer의 포인터를 반환합니다.
	 * 
	 * @return SDL Renderer의 포인터를 반환합니다.
	 */
	SDL_Renderer* GetRenderer() const { return Renderer; }


	/**
	 * 프레임 렌더링을 시작합니다.
	 * 
	 * @param InColor - 벡버퍼를 비울 색상입니다.
	 * 
	 * @throws 백버퍼 초기화에 실패할 경우, C++ 표준 예외를 던집니다.
	 */
	void BeginFrame(const LinearColor& InColor);


	/**
	 * 프레임 렌더링을 종료하고, 벡버퍼를 화면에 표시합니다.
	 */
	void EndFrame();


	/**
	 * 벡버퍼에 2D 점을 그립니다.
	 * 
	 * @param InPosition - 점의 위치입니다.
	 * @param InColor - 점의 색상입니다.
	 * 
	 * @throws 렌더링에 실패할 경우, C++ 표준 예외를 던집니다.
	 */
	void DrawPoint2D(const Vec2i& InPosition, const LinearColor& InColor);


	/**
	 * 벡버퍼에 2D 선을 그립니다.
	 * 
	 * @param InP0 - 선분의 한 끝점입니다.
	 * @param InP1 - 선분의 InP0이 아닌 한 끝점입니다.
	 * @param InColor - 선분의 색상입니다.
	 * 
	 * @throws 렌더링에 실패할 경우, C++ 표준 예외를 던집니다.
	 */
	void DrawLine2D(const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor);


	/**
	 * 벡버퍼에 2D 사각형을 그립니다.
	 * 
	 * @param InP0 - 사각형의 왼쪽 상단점입니다.
	 * @param InP1 - 사각형의 오른쪽 하단점입니다.
	 * @param InColor - 사각형의 색상입니다.
	 * 
	 * @throws 렌더링에 실패할 경우, C++ 표준 예외를 던집니다.
	 */
	void DrawRect2D(const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor);


	/**
	 * 벡버퍼에 2D 사각형을 그립니다.
	 * 
	 * @param InCenterPosition - 사각형의 중심이 위치할 화면상의 좌표입니다.
	 * @param InWidth - 사각형의 가로 길이입니다.
	 * @param InHeight - 사각형의 세로 길이입니다.
	 * @param InColor - 사각형의 색상입니다.
	 * 
	 * @throws 렌더링에 실패할 경우, C++ 표준 예외를 던집니다.
	 */
	void DrawRect2D(const Vec2i& InCenterPosition, int32_t InWidth, int32_t InHeight, const LinearColor& InColor);


	/**
	 * 벡버퍼에 채움 2D 사각형을 그립니다.
	 * 
	 * @param InP0 - 채움 사각형의 왼쪽 상단점입니다.
	 * @param InP1 - 채움 사각형의 오른쪽 하단점입니다.
	 * @param InColor - 채움 사각형의 색상입니다.
	 * 
	 * @throws 렌더링에 실패할 경우, C++ 표준 예외를 던집니다.
	 */
	void DrawFillRect2D(const Vec2i& InP0, const Vec2i& InP1, const LinearColor& InColor);


	/**
	 * 벡버퍼에 채움 2D 사각형을 그립니다.
	 * 
	 * @param InCenterPosition - 사각형의 중심이 위치할 화면상의 좌표입니다.
	 * @param InWidth - 사각형의 가로 길이입니다.
	 * @param InHeight - 사각형의 세로 길이입니다
	 * @param InColor - 사각형의 색상입니다.
	 * 
	 * @throws 렌더링에 실패할 경우, C++ 표준 예외를 던집니다.
	 */
	void DrawFillRect2D(const Vec2i& InCenterPosition, int32_t InWidth, int32_t InHeight, const LinearColor& InColor);


	/**
	 * 백버퍼에 텍스처를 그립니다.
	 * 
	 * @param InHashKey - 백버퍼에 그릴 텍스처의 해쉬 키값입니다.
	 * @param InCenterPosition - 텍스처의 중심이 위치할 화면상의 좌표입니다.
	 * @param InWidthScaling - 렌더링할 텍스처의 원본 텍스처 대비 가로 크기 비율입니다 
	 * @param InHeightScaling - 렌더링할 텍스처의 원본 텍스처 대비 세로 크기 비율입니다.
	 * 
	 * @throws 렌더링에 실패할 경우, C++ 표준 예외를 반환합니다.
	 */
	void DrawTexture2D(const std::size_t& InHashKey, const Vec2i& InCenterPosition, float InWidthScaling = 1.0f, float InHeightScaling = 1.0f);


	/**
	 * 벡버퍼에 UTF-16 텍스트를 그립니다.
	 * 
	 * @param InFont - 렌더링 시 참조할 폰트의 해쉬 키값입니다.
	 * @param InPosition - 렌더링 할 텍스트 영역의 왼쪽 상단 좌표입니다.
	 * @param InText - 렌더링할 UTF-16 텍스트입니다.
	 * @param InColor - 렌더링할 텍스트의 색상입니다.
	 * 
	 * @throws 렌더링에 실패할 경우, C++ 표준 예외를 던집니다.
	 */
	void DrawText2D(const std::size_t& InHashKey, const Vec2i& InPosition, const std::wstring& InText, const LinearColor& InColor);


private:
	/**
	 * SDL 렌더러의 컬러 상태를 설정합니다.
	 * 
	 * @param InColor - 변경할 SDL 렌더러의 컬러 상태입니다.
	 * 
	 * @throws 렌더 색상 설정에 실패할 경우, C++ 표준 예외를 던집니다.
	 */
	void SetDrawColor(const LinearColor& InColor);


	/**
	 * SDL 렌더러의 컬러 상태를 설정합니다.
	 * 
	 * @param InRed - 변경할 SDL 렌더러의 컬러 Red값 입니다.
	 * @param InGreen - 변경할 SDL 렌더러의 컬러 Green값 입니다.
	 * @param InBlue - 변경할 SDL 렌더러의 컬러 Blue값 입니다. 
	 * @param InAlpha - 변경할 SDL 렌더러의 컬러 Alpha값 입니다.
	 * 
	 * @throws 렌더 색상 설정에 실패할 경우, C++ 표준 예외를 던집니다.
	 */
	void SetDrawColor(uint8_t InRed, uint8_t InGreen, uint8_t InBlue, uint8_t InAlpha);


private:
	/**
	 * SDL Renderer의 포인터입니다.
	 */
	SDL_Renderer* Renderer = nullptr;
};