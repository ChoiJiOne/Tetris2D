#pragma once

#include "Macro.h"

#include <cstdint>
#include <string>

#include <windows.h>


/**
 * @brief 윈도우 클래스의 생성자 파라미터입니다.
 */
struct WindowConstructorParam
{
	const std::wstring Title;
	int32_t PositionX;
	int32_t PositionY;
	int32_t Width;
	int32_t Height;
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
	 * @param ConstructorParam 윈도우 클래스의 생성 파라미터입니다.
	 */
	explicit Window(const WindowConstructorParam& ConstructorParam);


	/**
	 * @brief 윈도우 창을 생성 및 관리하는 클래스의 생성자입니다.
	 *
	 * @param Title 윈도우의 타이틀입니다.
	 * @param PositionX 윈도우 왼쪽 상단의 X좌표입니다.
	 * @param PositionY 윈도우 왼쪽 상단의 Y좌표입니다.
	 * @param Width 윈도우의 가로 크기입니다.
	 * @param Height 윈도우의 세로 크기입니다.
	 */
	explicit Window(
		const std::wstring& Title,
		int32_t PositionX,
		int32_t PositionY,
		int32_t Width,
		int32_t Height
	);


	/**
	 * @brief 윈도우 창을 생성 및 관리하는 클래스의 가상 소멸자입니다
	 */
	virtual ~Window();


	/**
	 * @brief 복사 생성자와 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Window);


private:
	/**
	 * @brief 윈도우 창 핸들러입니다.
	 *
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/creating-a-window
	 */
	HWND WindowHandle_ = nullptr;
};