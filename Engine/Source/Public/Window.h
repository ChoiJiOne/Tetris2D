#pragma once

#include "Macro.h"

#include <cstdint>
#include <string>

#include <windows.h>


/**
 * @brief 윈도우 클래스의 생성자 파라미터입니다.
 * 
 * @note 타이틀의 문자열 형식이 UTF-16 입니다.
 */
struct WindowConstructorParam
{
	std::wstring Title;
	int32_t PositionX;
	int32_t PositionY;
	int32_t Width;
	int32_t Height;
	bool bIsFullScreen; /* 풀 스크린 모드 활성화 시 타이틀을 제외한 요소는 무시됩니다. */
};


/**
 * @brief 윈도우 창을 생성 및 관리합니다.
 */
class Window
{
public:
	/**
	 * @brief 윈도우 창을 생성 및 관리하는 클래스의 생성자입니다.
	 * 
	 * @note 타이틀의 문자열 형식이 UTF-16 입니다.
	 *
	 * @param ConstructorParam 윈도우 클래스의 생성 파라미터입니다.
	 *
	 * @throws 윈도우 창 생성에 실패하면 C++ 표준 예외를 던집니다.
	 */
	explicit Window(const WindowConstructorParam& ConstructorParam);


	/**
	 * @brief 윈도우 창을 생성 및 관리하는 클래스의 생성자입니다.
	 *
	 * @param Title UTF-16 기반의 윈도우의 타이틀입니다.
	 * @param PositionX 윈도우 왼쪽 상단의 X좌표입니다.
	 * @param PositionY 윈도우 왼쪽 상단의 Y좌표입니다.
	 * @param Width 윈도우의 가로 크기입니다.
	 * @param Height 윈도우의 세로 크기입니다.
	 * @param bIsFullScreen 윈도우의 풀 스크린 모드 여부입니다. 활성화 되었다면 타이틀을 제외한 요소는 무시됩니다.
	 * 
	 * @throws 윈도우 창 생성에 실패하면 C++ 표준 예외를 던집니다.
	 */
	explicit Window(
		const std::wstring& Title,
		int32_t PositionX,
		int32_t PositionY,
		int32_t Width,
		int32_t Height,
		bool bIsFullScreen
	);


	/**
	 * @brief 윈도우 창을 생성 및 관리하는 클래스의 가상 소멸자입니다
	 */
	virtual ~Window();


	/**
	 * @brief 복사 생성자와 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Window);


	/**
	 * @brief 현재 윈도우의 크기를 얻습니다.
	 * 
	 * @param Width[out] 현재 윈도우의 가로 크기입니다.
	 * @param Height[out] 현재 윈도우의 세로 크기입니다.
	 * 
	 * @throws 윈도우 창의 크기를 얻는 데 실패하면 C++ 표준 예외를 던집니다.
	 */
	template <typename T>
	void GetSize(T& Width, T& Height)
	{
		RECT WindowRect = {};
		CHECK(GetClientRect(WindowHandle_, &WindowRect), "failed to get client size");

		Width = static_cast<T>(WindowRect.right - WindowRect.left);
		Height = static_cast<T>(WindowRect.bottom - WindowRect.top);
	}


	/**
	 * @brief 현재 윈도우 크기를 변경합니다.
	 * 
	 * @param Width 변경할 윈도우의 가로 크기입니다.
	 * @param Height 변경할 윈도우의 세로 크기입니다.
	 * 
	 * @throws 윈도우 창의 크기를 설정하는 데 실패하면 C++ 표준 예외를 던집니다.
	 */
	template<typename T>
	void SetSize(T Width, T Height)
	{
		RECT Rect = { 0, 0, static_cast<LONG>(Width), static_cast<LONG>(Height) };
		CHECK(AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false), "failed to adjust window size");
	}


	/**
	 * @brief 윈도우 창의 핸들을 얻습니다.
	 * 
	 * @return 윈도우 창의 핸들 값을 반환합니다.
	 */
	HWND GetHandle() { return WindowHandle_; }


	/**
	 * @brief 윈도우 창이 풀 스크린 모드인지 확인합니다.
	 * 
	 * @return 윈도우 차이 풀 스크린 모드라면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsFullScreen() const { return bIsFullScreen_; }


private:
	/**
	 * @brief 윈도우 클래스를 등록합니다.
	 * 
	 * @param ClassTitle UTF-16 기반의 윈도우 클래스의 타이틀입니다.
	 * 
	 * @throws 윈도우 클래스 등록에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void RegisterWindowClass(const std::wstring& ClassTitle);


private:
	/**
	 * @brief 윈도우 창이 풀 스크린 모드인지 확인합니다.
	 */
	bool bIsFullScreen_ = false;


	/**
	 * @brief 윈도우 창 핸들러입니다.
	 *
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/creating-a-window
	 */
	HWND WindowHandle_ = nullptr;
};