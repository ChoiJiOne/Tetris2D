#pragma once

#include "Macro.h"

#include <cstdint>
#include <vector>
#include <functional>
#include <unordered_map>

#include <windows.h>


/**
 * @brief �Է� ���¸� ��Ÿ���ϴ�.
 * 
 * --------------------------------------
 * | ���� ������ | ���� ������ | �Է� ���� |
 * --------------------------------------
 * |     0      |     0      | NONE     |
 * |     0      |     1      | PRESSED  |
 * |     1      |     0      | RELEASED |
 * |     1      |     1      | HELD     |
 * --------------------------------------
 */
enum class EPressState
{
	NONE     = 0,
	PRESSED  = 1,
	RELEASED = 2,
	HELD     = 3
};


/**
 * @brief ������ �̺�Ʈ Ű ���Դϴ�.
 */
enum class EWindowEvent
{
	QUIT     = 0,
	ACTIVE   = 1,
	INACTIVE = 2,
	RESIZE   = 3,
};


/**
 * @brief �Է� ó�� �� Ű����, ���콺�� ���¸� �����մϴ�.
 * 
 * @note �� Ŭ������ �̱������� ����� �߰��ϸ� �ٷ� ����� �� �ֽ��ϴ�.
 */
class InputManager
{
public:
	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(InputManager);


	/**
	 * @brief InputManager�� �ν��Ͻ��� ����ϴ�.
	 * 
	 * @return InputManager�� �ν��Ͻ� �����ڸ� ��ȯ�մϴ�.
	 */
	static InputManager& Get()
	{
		static InputManager Instance;
		return Instance;
	}


	/**
	 * @brief ������ �޽��� �ڵ鷯�Դϴ�.
	 * 
	 * @see https://learn.microsoft.com/ko-kr/windows/win32/learnwin32/writing-the-window-procedure
	 *
	 * @param WindowHandle ������ â�� ���� �ڵ��Դϴ�.
	 * @param Message ������ �޽��� �ڵ��Դϴ�.
	 * @param WParam ������ �޽����� �߰� �������Դϴ�.
	 * @param LParam ������ �޽����� �߰� �������Դϴ�.
	 *
	 * @return �����쿡 ��ȯ�� ���Դϴ�.
	 */
	LRESULT WindowMessageHandler(HWND WindowHandle, uint32_t Message, WPARAM WParam, LPARAM LParam);


	/**
	 * @brief ������ �̺�Ʈ�� ����մϴ�.
	 * 
	 * @note �̺�Ʈ�� �����ϴ� ���� ��ƾ�� �����մϴ�. ���ο� ��ƾ�� �����Ϸ��� �ٽ� ����ؾ� �մϴ�.
	 * 
	 * @param WindowEvent ����� ������ �̺�Ʈ �����Դϴ�.
	 * @param EventCallback �̺�Ʈ ���� �� ������ ��ƾ�Դϴ�.
	 */
	void RegisterWindowEvent(const EWindowEvent& WindowEvent, const std::function<void()>& EventCallback);


	/**
	 * @brief ������ �̺�Ʈ�� ��� �����մϴ�.
	 * 
	 * @param WindowEvent ��� ������ ������ �̺�Ʈ�Դϴ�.
	 */
	void UnregisterWindowEvent(const EWindowEvent& WindowEvent);


	/**
	 * @brief �Է� ���¸� ������Ʈ�մϴ�.
	 * 
	 * @note �� �޼���� �� ������ ȣ���ؾ� �մϴ�.
	 */
	void Tick();


	/**
	 * @brief QUIT �޽����� �����Ǿ����� Ȯ���մϴ�.
	 * 
	 * @return QUIT �޽����� �����Ǿ��ٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsDetectQuit() const { return bIsQuit_; }


	/**
	 * @brief Ű�� �Է� ���¸� ��ȯ�մϴ�.
	 *
	 * @param KeyCode - �˻縦 ������ Ű�Դϴ�.
	 *
	 * @return Ű�� ��ư ���¸� ��ȯ�մϴ�.
	 */
	EPressState GetKeyPressState(int32_t KeyCode) const;
	

private:
	/**
	 * @brief �Է� ó���� �����ϴ� Ŭ������ �������Դϴ�.
	 */
	InputManager();


	/**
	 * @brief �Է� ó���� �����ϴ� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~InputManager() {}


	/**
	 * @brief Ư�� Ű�� ���ȴ��� �˻��մϴ�.
	 * 
	 * @param KeyboardState �˻縦 ������ Ű���� �����Դϴ�.
	 * @param KeyCode �˻縦 ������ Ű �ڵ��Դϴ�.
	 * 
	 * @return Ű�� ���ȴٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsPressKey(const std::vector<uint8_t>& KeyboardState, int32_t KeyCode) const;


	/**
	 * @brief ������ �̺�Ʈ�� �����ϴ� ��ƾ�� �����մϴ�.
	 *
	 * @param WindowEvent ������ ������ �̺�Ʈ�Դϴ�.
	 */
	void HandleWindowEvent(const EWindowEvent& WindowEvent);


private:
	/**
	 * @brief QUIT �޽����� �����Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsQuit_ = false;


	/**
	 * @brief ������ â�� Ȱ��ȭ �Ǿ����� Ȯ���մϴ�.
	 */
	bool bIsActive_ = false;


	/**
	 * @brief ������Ʈ ����(Tick ȣ�� ����)�� Ű���� �����Դϴ�.
	 */
	std::vector<uint8_t> PrevKeyboardState_;


	/**
	 * @brief ������Ʈ ��(Tick ȣ�� ��)�� Ű���� �����Դϴ�.
	 */
	std::vector<uint8_t> CurrKeyboardState_;


	/**
	 * ������ �̺�Ʈ Ű ���� �����ϴ� �̺�Ʈ�Դϴ�.
	 */
	std::unordered_map<EWindowEvent, std::function<void()>> WindowEvents_;
};