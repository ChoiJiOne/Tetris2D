#pragma once

#include "Macro.h"

#include <cstdint>
#include <string>

#include <windows.h>


/**
 * @brief ������ Ŭ������ ������ �Ķ�����Դϴ�.
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
 * @brief ������ â�� ���� �� �����մϴ�.
 */
class Window
{
public:
	/**
	 * @brief ������ â�� ���� �� �����ϴ� Ŭ������ �������Դϴ�.
	 *
	 * @param ConstructorParam ������ Ŭ������ ���� �Ķ�����Դϴ�.
	 */
	explicit Window(const WindowConstructorParam& ConstructorParam);


	/**
	 * @brief ������ â�� ���� �� �����ϴ� Ŭ������ �������Դϴ�.
	 *
	 * @param Title �������� Ÿ��Ʋ�Դϴ�.
	 * @param PositionX ������ ���� ����� X��ǥ�Դϴ�.
	 * @param PositionY ������ ���� ����� Y��ǥ�Դϴ�.
	 * @param Width �������� ���� ũ���Դϴ�.
	 * @param Height �������� ���� ũ���Դϴ�.
	 */
	explicit Window(
		const std::wstring& Title,
		int32_t PositionX,
		int32_t PositionY,
		int32_t Width,
		int32_t Height
	);


	/**
	 * @brief ������ â�� ���� �� �����ϴ� Ŭ������ ���� �Ҹ����Դϴ�
	 */
	virtual ~Window();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Window);


private:
	/**
	 * @brief ������ â �ڵ鷯�Դϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/creating-a-window
	 */
	HWND WindowHandle_ = nullptr;
};