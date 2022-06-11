#pragma once

// 벡터를 사용하기 위한 헤더 선언을 추가합니다.
#include "MathUtil.h"

// Block을 사용하기 위한 헤더 선언을 추가합니다.
#include "Block.h"


// 테트리스 보드 내의 테트로미노입니다.
class Tetromino
{
public:
	// 테트로미노의 모양입니다.
	enum class EShape : int32_t
	{
		I = 0,
		O = 1,
		T = 2,
		J = 3,
		L = 4,
		S = 5,
		Z = 6
	};


	// 테트로미노의 회전 방향입니다.
	enum class ESpin : int32_t
	{
		CCW = 0,
		CW  = 1
	};


	// 테트로미노의 이동 방향입니다.
	enum class EMove : int32_t
	{
		Left  = 0,
		Right = 1,
		Down  = 2,
		Up    = 3
	};


public:
	// 생성자입니다.
	// 
	// @param InShape - 테트로미노의 모양입니다.
	// @param InPositionInBoard - 테트로미노의 보드 상의 위치입니다.
	Tetromino(const EShape& InShape, const Vec2i& InPositionInBoard);


	// 가상 소멸자입니다.
	virtual ~Tetromino();



private:
	// void GenerateTetromino(const EShape& InShape);


private:
	// 테트로미노의 정사각형 영역의 크기입니다.
	int32_t BoundSize = 0;


	// 테트리스 보드 상의 테트로미노 위치입니다.
	Vec2i PositionInBoard;


	// 테트로미노 블럭들의 상대 위치입니다.
	std::vector<Vec2i> BlockPositions;
};