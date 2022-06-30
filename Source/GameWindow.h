#pragma once

// 표준 라이브러리 및 SDL2를 사용하기 위한 헤더 선언을 추가합니다.
#include "CommonHeader.h"


// Window 창을 관리하는 클래스입니다.
class GameWindow
{
public:
	// 생성자입니다.
	GameWindow() = default;


	// 가상 소멸자입니다.
	// 내부에서 윈도우 창을 소멸하므로, 이 클래스를 사용 시 윈도우 창을 해제할 의무는 없습니다.
	virtual ~GameWindow();


	// 복사 생성자 및 대입연산자입니다.
	// 앝은 복사 이슈가 발생할 가능성이 있어 처음부터 사용할 수 없도록 삭제
	GameWindow(GameWindow&& InInstance) = delete;
	GameWindow& operator=(GameWindow&& InInstance) = delete;


	// 복사 생성자 및 대입연산자입니다.
	// 앝은 복사 이슈가 발생할 가능성이 있어 처음부터 사용할 수 없도록 삭제
	GameWindow(const GameWindow& InInstance) = delete;
	GameWindow& operator=(const GameWindow& InInstance) = delete;


	// 윈도우 창을 생성합니다. 단위는 픽셀 단위입니다.
	// https://wiki.libsdl.org/SDL_CreateWindow
	// 
	// @param InTitle - 윈도우 타이틀 창의 이름입니다.
	// @param InX - 윈도우의 왼쪽 상단 점의 x 좌표입니다.
	// @param InY - 윈도우의 왼쪽 상단 점의 y 좌표입니다.
	// @param InWidth - 윈도우의 가로 크기입니다.
	// @param InHeight - 위도우의 세로 크기입니다.
	// @param InFlags - 윈도우의 형식입니다.
	// @throws - C++ 표준 예외를 반환합니다.
	void CreateWindow(const std::string InTitle, int32_t InX, int32_t InY, int32_t InWidth, int32_t InHeight, uint32_t InFlags);


	// 윈도우 창을 파괴합니다.
	// 윈도우 창 생성에 실패할 경우, 호출하더라도 어떠한 동작도 수행하지 않습니다.
	void DestroyWindow();


	// SDL 윈도우의 포인터를 반환합니다.
	// 이 함수는 윈도우 창 생성의 실패 여부에 상관 없이 윈도우 포인터를 반환합니다.
	//
	// @return - SDL 윈도우의 포인터를 반환합니다.
	SDL_Window* GetWindow() noexcept;


	// 현재 SDL 윈도우의 크기를 반환합니다.
	//
	// @param OutWidth - 윈도우의 가로 크기입니다.
	// @param OutHeight - 윈도우의 세로 크기입니다.
	template <typename T>
	void GetWindowSize(T& OutWidth, T& OutHeight)
	{
		int W = 0, H = 0;
		SDL_GetWindowSize(Window, &W, &H);

		OutWidth  = static_cast<T>(W);
		OutHeight = static_cast<T>(H);
	}


	// 현재 SDL 윈도우의 타이틀을 변경합니다.
	//
	// @param InTitle - 변경할 윈도우 타이틀입니다.
	void SetWindowTitle(const std::string& InTitle) noexcept;


	// 현재 콘솔 창의 상태를 설정합니다.
	//
	// @param bIsShow - 콘솔창을 표시할 것인지의 여부입니다.
	void SetVisibleConsoleWindow(bool bIsShow) noexcept;


	// 현재 SDL 윈도우의 가로 세로 크기의 비율을 반환합니다.
	//
	// @return - 윈도우의 가로 세로 비율을 반환합니다.
	float GetWindowAspectRatio()
	{
		float Width = 0.0f, Height = 0.0f;
		GetWindowSize<float>(Width, Height);

		return Width / Height;
	}


private:
	// SDL 윈도우의 포인터입니다.
	SDL_Window* Window = nullptr;
};