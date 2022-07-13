#pragma once

// @third party code - BEGIN SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
// @third party code - END


namespace Game
{
	/**
	 * 윈도우 창 생성을 위한 파라미터 구조체입니다.
	 * @see https://docs.unrealengine.com/4.26/ko/ProductionPipelines/DevelopmentSetup/CodingStandard/#API:~:text=%EB%8D%94%EC%9A%B1%20%EB%AA%85%ED%99%95%ED%95%B4%20%EC%A7%91%EB%8B%88%EB%8B%A4.-,API%20%EB%94%94%EC%9E%90%EC%9D%B8%20%EC%A7%80%EC%B9%A8,-bool%20%ED%95%A8%EC%88%98%20%ED%8C%8C%EB%9D%BC%EB%AF%B8%ED%84%B0%EB%8A%94
	 * @see https://wiki.libsdl.org/SDL_CreateWindow
	 */
	struct WindowConstructParams
	{
		const char* Title = nullptr;
		int32_t x = SDL_WINDOWPOS_CENTERED;
		int32_t y = SDL_WINDOWPOS_CENTERED;
		int32_t w = 0;
		int32_t h = 0;
		uint32_t Flags = SDL_WINDOW_SHOWN;
	};


	/**
	 * SDL2 기반의 윈도우 클래스입니다.
	 */
	class Window
	{
	public:
		/**
		 * 윈도우 클래스의 생성자입니다.
		 *
		 * @note 윈도우 창 생성 시 Create 메서드를 호출해야 합니다.
		 */
		Window() = default;


		/**
		 * 윈도우 클래스의 가상 소멸자입니다
		 */
		virtual ~Window();


		/**
		 * 윈도우 창을 초기화합니다.
		 *
		 * @param InWindowConstructParams - 윈도우 창 생성을 위한 파라미터입니다.
		 *
		 * @throws 윈도우 창 생성에 실패할 경우, C++ 표준 예외를 던집니다.
		 */
		void Initialize(const WindowConstructParams& InInWindowConstructParams);


		/**
		 * SDL 윈도우의 크기를 반환합니다.
		 *
		 * @param OutWidth - 윈도우의 가로 크기입니다.
		 * @param OutHeight - 윈도우의 세로 크기입니다.
		 */
		template <typename T>
		void GetWindowSize(T& OutWidth, T& OutHeight)
		{
			int WindowWidth = 0, WindowHeight = 0;
			SDL_GetWindowSize(SDLWindow, &WindowWidth, &WindowHeight);

			OutWidth = static_cast<T>(WindowWidth);
			OutHeight = static_cast<T>(WindowHeight);
		}


		/**
		 * SDL 윈도우의 가로 세로 크기의 비율을 반환합니다.
		 *
		 * @return 윈도우의 가로 세로 비율을 반환합니다.
		 */
		float GetWindowAspectRatio();


		/**
		 * SDL윈도우의 포인터를 반환합니다.
		 *
		 * @return SDL 윈도우의 포인터를 반환합니다.
		 */
		SDL_Window* GetSDLWindow() { return SDLWindow; }


		/**
		 * 현재 SDL 윈도우의 타이틀을 변경합니다.
		 *
		 * @param InTitle - 변경할 윈도우 타이틀입니다.
		 */
		void SetWindowTitle(const char* InTitle);


	private:
		/**
		 * SDL 윈도우 포인터입니다.
		 */
		SDL_Window* SDLWindow = nullptr;
	};
}