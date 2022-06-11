#pragma once

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
	// @param InBlockColor - 테트로미노 블럭 색상입니다.
	// @param InPositionInBoard - 테트로미노의 보드 상의 위치입니다.
	Tetromino(const EShape& InShape, const EBlockColor& InBlockColor, const Vec2i& InPositionInBoard);


	// 가상 소멸자입니다.
	virtual ~Tetromino();


	// 복사 생성자입니다.
	Tetromino(const Tetromino& InInstance) noexcept;
	Tetromino& operator=(const Tetromino& InInstance) noexcept;


	// 대입 연산자입니다.
	Tetromino(Tetromino&& InInstance) noexcept;
	Tetromino& operator=(Tetromino&& InInstance) noexcept;


	// 렌덤하게 테트로미노를 생성합니다.
	static std::shared_ptr<Tetromino> GenerateRandomTetromino(const Vec2i& InPositionInBoard);


	// 테트로미노를 회전합니다.
	//
	// @param InSpin - 테트로미노의 회전 방향입니다.
	void Spin(ESpin InSpin);


	// 테트로미노를 움직입니다.
	//
	// @param InMove - 테트로미노의 이동 방향입니다.
	void Move(EMove InMove);


	// 테트로미노의 정사각형 영역의 크기를 반환합니다.
	//
	// @return - 테트로미노의 정사각형 영역의 크기를 반환합니다.
	int32_t GetBoundSize() const { return BoundSize; }


	// 테트리스 보드 상의 위치를 반환합니다.
	//
	// @return - 테트리스 보드 상의 위치를 반환합니다.
	Vec2i GetPositionInBoard()  noexcept { return PositionInBoard; }
	
	
	// 테트로미노 블록의 위치들을 반환합니다. 
	//
	// @return - 테트로미노 블럭의 위치를 포함한 Vec2i 벡터를 반환합니다.
	const std::vector<Vec2i>& GetBlockPositions() noexcept { return BlockPositions; }


	// 테트로미노 블록의 색상을 반환합니다.
	//
	// @return - 테트로미노 블록의 색상을 반환합니다.
	EBlockColor GetBlockColor() const { return BlockColor; }


	// 테트로미노를 화면에 그립니다.
	//
	// @param InPosition - 윈도우 좌표계를 기준으로 테트로미노 정사각형 영역의 왼쪽 상단점입니다.
	// @param InScale - 렌더링 할 텍스처의 Scale 값입니다.
	void DrawTetromino(const Vec2i& InPosition, float InScale);


private:
	// 테트로미노 블럭의 점을 생성합니다.
	//
	// @param InShape - 테트로미노의 타입입니다.
	void GenerateBlockPositions(const EShape& InShape);


private:
	// 테트로미노의 정사각형 영역의 크기입니다.
	int32_t BoundSize = 0;


	// 테트리스 보드 상의 테트로미노 위치입니다.
	Vec2i PositionInBoard;


	// 테트로미노 블럭들의 상대 위치입니다.
	std::vector<Vec2i> BlockPositions;


	// 테트로미노 전체 블럭의 색상입니다.
	EBlockColor BlockColor;


	// 테트로미노의 텍스처입니다.
	GameTexture2D TetrominoTexture;
};