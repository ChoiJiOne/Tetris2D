#pragma once

#include "Color.h"
#include "Vector.hpp"
#include "GameObject.h"


/**
 * @brief 게임 타이틀입니다.
 */
class GameTitle : public GameObject
{
public:
	/**
	 * @brief 게임 타이틀의 생성자입니다.
	 * 
	 * @note 타이틀 문자열은 반드시 아스키 코드 범위 내에 있는 문자들로 구성되어야 합니다.
	 *
	 * @param Signature 게임 타이틀의 식별자입니다.
	 * @param Title 게임 타이틀입니다.
	 * @param FontSignature 게임 타이틀 문자열의 폰트 시그니처입니다.
	 * @param Position 화면 상의 게임 타이틀 위치입니다.
	 * @param Color 타이틀의 색상입니다.
	 */
	GameTitle(
		const std::string& Signature, 
		const std::wstring& Title, 
		const std::string& FontSignature,
		const Vec2f& Position, 
		const LinearColor& Color
	);


	/**
	 * @brief 게임 타이틀의 가상 소멸자입니다.
	 */
	virtual ~GameTitle() {}


	/**
	 * @brief 명시적으로 복사 생성자외 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameTitle);


	/**
	 * @brief 게임 타이틀을 업데이트합니다.
	 * 
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;


private:
	/**
	 * @brief 화면에 표시될 게임 타이틀입니다.
	 */
	std::wstring Title_;


	/**
	 * @brief 게임 타이틀 문자열의 폰트 시그니처입니다.
	 */
	std::string FontSignature_;


	/**
	 * @brief 화면에 표시될 게임 타이틀의 중심 위치입니다.
	 */
	Vec2f Position_;


	/**
	 * @brief 화면에 표시될 게임 타이틀의 색상입니다.
	 */
	LinearColor Color_;
};