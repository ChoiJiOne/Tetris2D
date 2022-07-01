#pragma once

// 표준 라이브러리 및 SDL2를 사용하기 위한 헤더 선언을 추가합니다.
#include "CommonHeader.h"


// 전체 게임을 초기화하고 관리하는 클래스입니다.
class Game
{
public:
	// 생성자입니다.
	// 이때, 생성자는 전체 게임에 대한 초기화를 수행하지 않으므로 반드시 Setup 메서드를 호출해서 초기화 해야 합니다.
	Game() = default;


	// 가상 소멸자입니다.
	virtual ~Game();


	// 게임 클래스의 요소를 초기화합니다.
	virtual void Setup();


	// 게임을 실행합니다.
	virtual void Run() = 0;



protected:
	/*
	// SDL 윈도우 창을 생성합니다. 단위는 픽셀 단위입니다.
	// https://wiki.libsdl.org/SDL_CreateWindow
	// 
	// @param InWindow - 생성할 SDL 윈도우의 포인터입니다.
	// @param InTitle - 윈도우 타이틀 창의 이름입니다.
	// @param InX - 윈도우의 왼쪽 상단 점의 x 좌표입니다.
	// @param InY - 윈도우의 왼쪽 상단 점의 y 좌표입니다.
	// @param InWidth - 윈도우의 가로 크기입니다.
	// @param InHeight - 위도우의 세로 크기입니다.
	// @param InFlags - 윈도우의 형식입니다.
	// @throws - SDL 윈도우 창 생성에 실패할 경우, C++ 표준 예외를 던집니다.
	void CreateWindow(SDL_Window* InWindow, const std::string InTitle, int32_t InX, int32_t InY, int32_t InWidth, int32_t InHeight, uint32_t InFlags);


	// 윈도우 창을 파괴합니다.
	// 이때, 윈도우 창 생성에 실패할 경우 호출하더라도 어떠한 동작도 수행하지 않습니다.
	//
	// @param InWindow - 파괴할 SDL 윈도우의 포인터입니다.
	void DestroyWindow(SDL_Window* InWindow);


	// SDL 렌더러를 생성합니다.
	//
	// @throws - SDL 렌더러 생성에 실패할 경우, C++ 표준 예외를 던집니다.
	void CreateRenderer();


	// SDL 렌더러를 파괴합니다.
	// 이때, SDL 렌더러 생성에 실패할 경우 호출하더라도 어떠한 동작도 수행하지 않습니다.
	void DestroyRenderer();
	*/

protected:
	// 게임 종료 여부입니다.
	bool bIsDone = false;


private:
	// 실행파일 경로입니다.
	std::string ExecuteDirectory;


	// 게임 프로젝트의 루트 디렉토리입니다.
	std::string ProjectRootDirectory;


	// SDL_Window의 포인터입니다.
	SDL_Window* Window = nullptr;
	
	
	// SDL_Renderer의 포인터입니다.
	SDL_Renderer* Renderer = nullptr;
};