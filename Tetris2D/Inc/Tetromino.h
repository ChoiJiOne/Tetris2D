#pragma once

#include <array>

#include "IApp.h"
#include "IEntity2D.h"
#include "GameMath.h"

#include "Block.h"

class Board;
class GameApp;

class Tetromino : public IEntity2D
{
public:
	/** https://en.wikipedia.org/wiki/Tetromino */
	enum class Type
	{
		NONE = 0x00,
		I = 0x01,
		O = 0x02,
		T = 0x03,
		J = 0x04,
		L = 0x05,
		S = 0x06,
		Z = 0x07,
	};

	enum class Status
	{
		WAIT   = 0x00, /** 보드에 배치되기 전 대기 상태 */
		GOTO   = 0x01, /** 보드에 배치되기 위해 움직이는 상태 */
		ACTIVE = 0x02, /** 보드에 배치되어서 플레이어가 컨트롤 할 수 있는 상태 */
		DONE   = 0x03, /** 더 이상 테트로미노를 움직일 수 없는 상태 */
	};

	static const uint32_t NUM_BLOCKS = 4;
	
public:
	Tetromino(const Vec2f& startPos, float blockSize, float stride, const Type& type, const Vec4f& color);
	virtual ~Tetromino();

	DISALLOW_COPY_AND_ASSIGN(Tetromino);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	const Status& GetStatus() const { return status_; }
	const std::array<Block, NUM_BLOCKS>& GetBlocks() const { return blocks_; }

	void GotoPosition(const Vec2f& gotoPos);

	static Tetromino* CreateRandom(const Vec2f& startPos, float blockSize, float stride);
	
private:
	enum class Direction
	{
		LEFT  = 0x00,
		RIGHT = 0x01,
		DOWN  = 0x02,
		UP    = 0x03,
	};

	friend class TetrominoController;

	bool CanMove(const Direction& direction);
	void Move(const Direction& direction);
	bool CanRotate();
	void Rotate();
	bool IsDone();

	/** 로직 업데이트. */
	void UpdateActiveStatus(float deltaSeconds);
	
	/** 전체 블럭들 관련 동작. */
	void CreateBlocks(std::array<Block, NUM_BLOCKS>& outBlocks, Vec2f& outRotatePos, const Vec2f& startPos, float blockSize, const Vec4f& color);
	void MoveBlocks(const Direction& direction, std::array<Block, NUM_BLOCKS>& blocks, Vec2f& rotatePos);
	void RotateBlocks(std::array<Block, NUM_BLOCKS>& blocks, Vec2f& rotatePos);

private:
	Board* board_ = nullptr;

	float stride_ = 0.0f;
	Type type_ = Type::NONE;
	Status status_ = Status::WAIT;
	Vec2f startPos_;
	Vec2f gotoPos_;
	Vec2f rotatePos_;
	std::array<Block, NUM_BLOCKS> blocks_;

	float moveStepTime_ = 0.0f;
	float maxMoveStepTime_ = 0.0f;

	static GameApp* app_;
	static std::map<Key, Direction> keyDirections_;
};