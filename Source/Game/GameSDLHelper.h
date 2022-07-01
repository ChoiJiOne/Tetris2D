#pragma once

// 표준 라이브러리와 SDL2를 사용하기 위해서 헤더 파일을 추가합니다.
#include "GameHeader.h"


namespace Game
{
	// 게임 내에 SDL 헬퍼 클래스입니다.
	class SDLHelper
	{
	public:
		// 게임 유틸리티를 초기화합니다.
		static void Init();


		// 게임 유틸리티를 해제합니다.
		static void Release();


		// SDL 윈도우 창을 생성합니다. 단위는 픽셀 단위입니다.
		// https://wiki.libsdl.org/SDL_CreateWindow
		// 
		// @param InTitle - 윈도우 타이틀 창의 이름입니다.
		// @param InX - 윈도우의 왼쪽 상단 점의 x 좌표입니다.
		// @param InY - 윈도우의 왼쪽 상단 점의 y 좌표입니다.
		// @param InWidth - 윈도우의 가로 크기입니다.
		// @param InHeight - 위도우의 세로 크기입니다.
		// @param InFlags - 윈도우의 형식입니다.
		// 
		// @throws - SDL 윈도우 창 생성에 실패할 경우, C++ 표준 예외를 던집니다.
		// 
		// @return - SDL 윈도우의 포인터를 반환합니다.
		static SDL_Window* CreateSDLWindow(
			const std::string InTitle, 
			int32_t InX, 
			int32_t InY, 
			int32_t InWidth, 
			int32_t InHeight, 
			uint32_t InFlags
		);


		// SDL 윈도우 창을 파괴합니다.
		// 
		// @param InWindow - SDL 윈도우의 포인터입니다.
		static void DestroySDLWindow(SDL_Window* InWindow);


		// SDL 렌더러를 생성합니다.
		//
		// @param InWindow - SDL 렌더러의 타겟 윈도우 포인터입니다.
		static SDL_Renderer* CreateSDLRenderer(SDL_Window* InWindow);


		// SDL 렌더러를 파괴합니다.
		//
		// @param InRenderer - SDL 렌더러의 포인터입니다.
		static void DestroySDLRenderer(SDL_Renderer* InRenderer);


		// exe 실행 파일 경로를 반환합니다.
		//
		// @return - 실행 파일 경로를 반환합니다.
		static std::string GetExecuteDirectory();


		// SDL 윈도우의 크기를 반환합니다.
		//
		// @param InWindow - 크기를 확인할 SDL 윈도우의 포인터입니다.
		// @param OutWidth - 윈도우의 가로 크기입니다.
		// @param OutHeight - 윈도우의 세로 크기입니다.
		template <typename T>
		static void GetWindowSize(SDL_Window* InWindow, T& OutWidth, T& OutHeight)
		{
			int WindowWidth = 0, WindowHeight = 0;
			SDL_GetWindowSize(InWindow, &WindowWidth, &WindowHeight);

			OutWidth = static_cast<T>(WindowWidth);
			OutHeight = static_cast<T>(WindowHeight);
		}


		// 현재 SDL 윈도우의 타이틀을 변경합니다.
		//
		// @param InWindow - 타이틀을 변경할 SDL 윈도우의 포인터입니다.
		// @param InTitle - 변경할 윈도우 타이틀입니다.
		static void SetWindowTitle(SDL_Window* InWindow, const std::string& InTitle);


		// 현재 콘솔 창의 시야 상태를 설정합니다.
		//
		// @param bIsShow - 콘솔창을 표시할 것인지의 여부입니다.
		static void SetVisibleConsoleWindow(bool bIsShow);


		// SDL 윈도우의 가로 세로 크기의 비율을 반환합니다.
		//
		// @param - 가로 세로 비율을 확인할 SDL 윈도우의 포인터입니다.
		// @return - 윈도우의 가로 세로 비율을 반환합니다.
		static float GetWindowAspectRatio(SDL_Window* InWindow);


	private:
		// SDLUtility가 초기화 되었는지 확인합니다.
		//
		// @throws - SDLUtility가 초기화되지 않았다면, C++ 표준 예외를 던집니다.
		static void CheckInitializeSDLHelper();
	};
}