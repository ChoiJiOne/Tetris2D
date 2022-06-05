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
	// 
	// @param InWindow - SDL_Window의 포인터입니다.
	// @throws - 렌더러 생성에 실패할 경우, C++ 표준 예외를 반환합니다.
	GameRenderer(SDL_Window* InWindow);


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


	// 프레임 렌더링을 시작합니다.
	//
	// @param InColor - 벡버퍼를 비울 색상입니다.
	// @throws - C++ 표준 예외를 반환합니다.
	void BeginFrame(const LinearColor& InColor);


	// 프레임 렌더링을 종료하고, 벡버퍼를 화면에 표시합니다.
	void EndFrame();


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
	// SDL_Renderer의 포인터입니다.
	SDL_Renderer* Renderer = nullptr;
};