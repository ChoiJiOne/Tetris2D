#pragma once

#include "Macro.h"

class Window;


/**
 * @brief 게임 프레임워크입니다.
 * 
 * @note 게임이 구현되는 클래스는 이 프레임워크를 반드시 상속받아야 합니다.
 */
class GameFramework
{
public:
	/**
	 * @brief 게임 프레임워크의 생성자입니다.
	 */
	GameFramework();


	/**
	 * @brief 게임 프레임워크의 가상 소멸자입니다.
	 */
	virtual ~GameFramework();


	/**
	 * @brief 게임 프레임워크를 초기화합니다.
	 *
	 * @note 가상 함수로, 반드시 하위 클래스에서 구현해야 합니다.
	 */
	virtual void Init() = 0;


	/**
	 * @brief 게임 프레임워크를 실행합니다.
	 * 
	 * @note 가상 함수로, 반드시 하위 클래스에서 구현해야 합니다.
	 */
	virtual void Run() = 0;


private:
	/**
	 * @brief 설정 파일로부터 윈도우 창을 생성합니다.
	 * 
	 * @throws 
	 * 설정 파일 로딩 및 파싱에 실패하면 C++ 표준 예외를 던집니다.
	 * 윈도우 창 생성에 실패하면 C++ 표준 예외를 던집니다.
	 */
	void CreateWindowFromConfig();


protected:
	/**
	 * @brief 윈도우 창입니다.
	 */
	std::unique_ptr<Window> Window_ = nullptr;


	/**
	 * @brief 게임 루프를 수행할 지 확인합니다.
	 */
	bool bIsDone_ = false;
};