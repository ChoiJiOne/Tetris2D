#pragma once

#include "Macro.h"

#include <windows.h>


/**
 * @brief ������ â�� �����ϴ� Ŭ�����Դϴ�.
 */
class Window
{
public:
	/**
	 * @brief ������ �Ķ�����Դϴ�.
	 *
	 * @note Ÿ��Ʋ�� ���ڿ� ������ UTF-16 �Դϴ�.
	 */
	struct ConstructorParam
	{
		std::wstring Title;
		int32_t PositionX;
		int32_t PositionY;
		int32_t Width;
		int32_t Height;
		bool bIsFullScreen; /* Ǯ ��ũ�� ��� Ȱ��ȭ �� Ÿ��Ʋ�� ������ ��Ҵ� ���õ˴ϴ�. */
	};


public:
	/**
	 * @brief ������ â�� ���� �� �����ϴ� Ŭ������ �������Դϴ�.
	 *
	 * @note Ÿ��Ʋ�� ���ڿ� ������ UTF-16 �Դϴ�.
	 *
	 * @param Param ������ �Ķ�����Դϴ�.
	 *
	 * @throws ������ â ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	explicit Window(const ConstructorParam& Param);


	/**
	 * @brief ������ â�� ���� �� �����ϴ� Ŭ������ �������Դϴ�.
	 *
	 * @param Title UTF-16 ����� �������� Ÿ��Ʋ�Դϴ�.
	 * @param PositionX ������ ���� ����� X��ǥ�Դϴ�.
	 * @param PositionY ������ ���� ����� Y��ǥ�Դϴ�.
	 * @param Width �������� ���� ũ���Դϴ�.
	 * @param Height �������� ���� ũ���Դϴ�.
	 * @param bIsFullScreen �������� Ǯ ��ũ�� ��� �����Դϴ�. Ȱ��ȭ �Ǿ��ٸ� Ÿ��Ʋ�� ������ ��Ҵ� ���õ˴ϴ�.
	 *
	 * @throws ������ â ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	explicit Window(const std::wstring& Title, int32_t PositionX, int32_t PositionY, int32_t Width, int32_t Height, bool bIsFullScreen);


	/**
	 * @brief ������ â�� ���� �� �����ϴ� Ŭ������ ���� �Ҹ����Դϴ�
	 */
	virtual ~Window();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Window);


	/**
	 * @brief ������ â�� �ڵ��� ����ϴ�.
	 *
	 * @return ������ â�� �ڵ� ���� ��ȯ�մϴ�.
	 */
	HWND GetWindowHandle() { return WindowHandle_; }


	/**
	 * @brief ������ â�� Ǯ ��ũ�� ������� Ȯ���մϴ�.
	 *
	 * @return ������ ���� Ǯ ��ũ�� ����� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsFullScreen() const { return bIsFullScreen_; }


private:
	/**
	 * @brief ������ Ŭ������ ����մϴ�.
	 *
	 * @param ClassName ����� ������ Ŭ������ UTF-16 ��� �̸��Դϴ�.
	 *
	 * @throws ������ Ŭ���� ��Ͽ� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	void RegisterWindowClass(const std::wstring& ClassName);


private:
	/**
	 * @brief ������ â�� Ǯ ��ũ�� ������� Ȯ���մϴ�.
	 */
	bool bIsFullScreen_ = false;


	/**
	 * @brief ������ â �ڵ鷯�Դϴ�.
	 *
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/creating-a-window
	 */
	HWND WindowHandle_ = nullptr;
};