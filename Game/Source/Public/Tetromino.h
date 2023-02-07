#pragma once

#include <array>

#include "GameObject.h"

class BlockComponent;


/**
 * @brief 테트리스 게임의 테트로미노입니다.
 */
class Tetromino : public GameObject
{
public:
	/**
	 * @brief 테트로미노의 모양 타입입니다.
	 *
	 * @see https://ko.wikipedia.org/wiki/%ED%85%8C%ED%8A%B8%EB%A1%9C%EB%AF%B8%EB%85%B8
	 */
	enum class EShape : int32_t
	{
		NONE = 0,
		I = 1,
		O = 2,
		T = 3,
		J = 4,
		L = 5,
		S = 6,
		Z = 7
	};


	/**
	 * @brief 테트로미노의 움직임 방향입니다.
	 */
	enum class EDirection : int32_t
	{
		NONE  = 0,
		LEFT  = 1,
		RIGHT = 2,
		DOWN  = 3,
		UP    = 4,
		CCW   = 5,
		CW    = 6,
		JUMP  = 7,
	};


public:
	/**
	 * @brief 테트로미노의 생성자입니다.
	 * 
	 * @param Signature 테트로미노의 식별자입니다.
	 */
	Tetromino(const std::string& Signature);


	/**
	 * @brief 테트로미노의 가상 소멸자입니다.
	 */
	virtual ~Tetromino();


	/**
	 * @brief 명시적으로 복사 생성자외 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Tetromino);


	/**
	 * @brief 백그라운드를 업데이트합니다.
	 *
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) override;


private:
	/**
	 * @brief 테트로미노의 블럭 컴포넌트입니다.
	 */
	std::array<BlockComponent*, 4> Blocks_;
};