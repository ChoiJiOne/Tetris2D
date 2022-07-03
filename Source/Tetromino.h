#pragma once

// 수학 기능을 사용하기 위해 헤더 선언을 추가합니다.
#include "Game/MathHelper.h"


// 테트리스 보드 내의 테트로미노입니다.
class Tetromino
{
public:
	// 테트로미노 모양입니다.
	enum class EShape : int32_t
	{
		I = 0,
		O = 1,
		T = 2,
		J = 3,
		L = 4,
		S = 5,
		Z = 6,
	};


	// 테트로미노의 회전 방향 입니다.
	enum class ESpin : int32_t
	{
		CCW  = 0,
		CW   = 1,
		None = 2
	};


	// 테트로미노의 이동 방향입니다.
	enum class EMove : int32_t
	{
		Left  = 0,
		Right = 1,
		Down  = 2,
		Up    = 3,
		None  = 4
	};


public:
	// 생성자입니다.
	//
	// @param InPositionInBoard - 테트리스 보드 상의 테트로미노 왼쪽 상단 좌표입니다.
	// @param InShape - 테트로미노의 모양입니다.
	// @param InColor - 테트로미노 블럭의 색상입니다.
	Tetromino(const Vec2i& InPositionInBoard, const EShape& InShape, const LinearColor& InColor);


	// 가상 소멸자입니다.
	virtual ~Tetromino();


	// 복사 생성자입니다.
	Tetromino(Tetromino&& InInstance) noexcept;
	Tetromino(const Tetromino& InInstance) noexcept;


	// 대입 연산자입니다.
	Tetromino& operator=(Tetromino&& InInstance) noexcept;
	Tetromino& operator=(const Tetromino& InInstance) noexcept;


	// 테트로미노를 회전합니다.
	// 
	// @param InSpin - 테트로미노의 회전 방향입니다.
	void Spin(ESpin InSpin);


	// 테트로미노를 이동합니다.
	// 
	// @param InMove - 테트로미노의 이동 방향입니다.
	void Move(EMove InMove);


	// 테트로미노의 블럭 컬러를 반환합니다.
	//
	// @return - 테트로미노의 블럭 컬러를 반환합니다.
	LinearColor GetBlockColor() const noexcept { return BlockColor; }


	// 테트리스 보드 상의 테트로미노 왼쪽 상단 좌표를 반환합니다.
	//
	// @return - 테트리스 보드 상의 테트로미노 왼쪽 상단 좌표를 반환합니다.
	Vec2i GetPositionInBoard() const noexcept { return PositionInBoard; }


	// 테트로미노 블럭들의 위치를 반환합니다.
	//
	// @return - 테트로미노 블럭들의 위치를 반환합니다.
	const std::vector<Vec2i>& GetBlockPositions() const noexcept { return BlockPositions; }


	// 테트로미노를 백 버퍼에 그립니다.
	// 
	// @param InRenderer - SDL 렌더러의 포인터입니다.
	// @param InWindowPosition - 테트로미노를 그릴 윈도우 상의 좌표입니다.
	// @param InBlockSize - 화면에 그려질 테트로미노 블럭의 크기입니다.
	// @param OutlineColor - 테트로미노의 테두리 색상입니다.
	void Draw(SDL_Renderer* InRenderer, const Vec2i& InWindowPosition, int32_t InBlockSize, const LinearColor& InOutlineColor = ColorHelper::Black) const;


	// 임의의 테트로미노를 생성합니다.
	// 
	// @param InPosition - 테트리스 보드 상의 테트로미노 왼쪽 상단 좌표입니다.
	// @return - 생성된 테트로미노의 스마트 포인터를 반환합니다.
	static std::shared_ptr<Tetromino> GenerateRandomTetromino(const Vec2i& InPosition)
	{
		static EShape ShapeTable[] = {
			EShape::I,
			EShape::O,
			EShape::T,
			EShape::J,
			EShape::L,
			EShape::S,
			EShape::Z,
		};

		static LinearColor ColorTable[] = {
			ColorHelper::Red,
			ColorHelper::Green,
			ColorHelper::Blue,
			ColorHelper::Yellow,
			ColorHelper::Magenta,
			ColorHelper::Cyan
		};

		return std::make_shared<Tetromino>(
			InPosition,
			ShapeTable[MathHelper::GenerateRandomInt<int32_t>(0, static_cast<int32_t>(std::size(ShapeTable)) - 1)],
			ColorTable[MathHelper::GenerateRandomInt<int32_t>(0, static_cast<int32_t>(std::size(ColorTable)) - 1)]
		);
	}


	// 테트로미노의 움직이는 방향의 반대 방향을 계산합니다.
	// 
	// @param InMove - 계산할 방향입니다.
	//
	// @return - 입력받은 방향의 반대 방향을 반환합니다.
	static EMove CalculateCountMove(const EMove& InMove)
	{
		EMove OutMove = EMove::None;

		switch (InMove)
		{
		case EMove::Down:
			OutMove = EMove::Up;
			break;

		case EMove::Up:
			OutMove = EMove::Down;
			break;

		case EMove::Left:
			OutMove = EMove::Right;
			break;

		case EMove::Right:
			OutMove = EMove::Left;
			break;

		default:
			break;
		}

		return OutMove;
	}


	// 테트로미노의 회전 방향의 반대 방향을 계산합니다.
	// 
	// @param InSpin - 계산할 방향입니다.
	//
	// @return - 입력받은 방향의 반대 방향을 반환합니다.
	static ESpin CalculateCountMove(const ESpin& InSpin)
	{
		ESpin OutSpin = ESpin::None;

		switch (InSpin)
		{
		case ESpin::CCW:
			OutSpin = ESpin::CW;
			break;

		case ESpin::CW:
			OutSpin = ESpin::CCW;
			break;

		default:
			break;
		}

		return OutSpin;
	}


private:
	// 테트로미노 블럭의 상대 위치를 생성합니다.
	//
	// @param InShape - 테트로미노 블럭의 상대 위치를 생성할 타입입니다.
	void GenerateBlockPositions(const EShape& InShape);


private:
	// 테트로미노의 블럭 색상입니다.
	LinearColor BlockColor;


	// 테트로미노의 영역 크기입니다.
	int32_t BoundSize = 0;


	// 테트리스 보드 상의 테트로미노 왼쪽 상단 좌표입니다.
	Vec2i PositionInBoard;


	// 테트로미노 블럭들의 위치입니다.
	std::vector<Vec2i> BlockPositions;
};