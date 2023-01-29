#pragma once

#include "Vector.hpp"
#include "GameObject.h"

#include <functional>


/**
 * @brief 게임 내의 사각형 버튼입니다.
 */
class Button : public GameObject
{
public:
	/**
	 * @brief 게임 내의 텍스트가 포함된 사각형 버튼 클래스의 생성자입니다.
	 * 
	 * @param Signature 사각형 버튼의 시그니처 값입니다.
	 */
	Button(const std::string& Signature);



	/**
	 * @brief 게임 내의 텍스트가 포함되지 않은 사각형 버튼 클래스의 생성자입니다.
	 * 
	 * 
	 */



	/**
	 * @brief 게임 내의 버튼 클래스의 가상 소멸자입니다.
	 */
	virtual ~Button();


	/**
	 * @brief 명시적으로 복사 생성자외 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Button);



private:
	/**
	 * @brief 월드 상의 사각형 버튼 중심 좌표입니다.
	 */
	Vec2f Position_;


	/**
	 * @brief 사각형 버튼의 가로 크기입니다.
	 */
	float Width_ = 0.0f;


	/**
	 * @brief 사각형 버튼의 세로 크기입니다.
	 */
	float Height_ = 0.0f;


	/**
	 * @brief 사각형 버튼의 텍스트입니다.
	 * 
	 * @note 텍스트가 없다면 무시됩니다.
	 */



	/**
	 * @brief 사각형 텍스트의 색상입니다.
	 * 
	 * @note 텍스트가 없다면 무시됩니다.
	 */



	/**
	 * @brief 
	 */
};