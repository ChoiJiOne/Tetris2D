#pragma once

#include "GameObject.h"
#include "Tile.h"


/**
 * @brief ��Ʈ������ ��Ʈ�ι̳��Դϴ�.
 */
class Tetromino : public GameObject
{
public:
	/**
	 * @brief ��Ʈ�ι̳��� ��� Ÿ���Դϴ�.
	 *
	 * @see https://ko.wikipedia.org/wiki/%ED%85%8C%ED%8A%B8%EB%A1%9C%EB%AF%B8%EB%85%B8
	 */
	enum class EShape : int32_t
	{
		NONE = 0,
		I    = 1,
		O    = 2,
		T    = 3,
		J    = 4,
		L    = 5,
		S    = 6,
		Z    = 7
	};


	/**
	 * @brief ��Ʈ�ι̳��� ������ �����Դϴ�.
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


	/**
	 * @brief ��Ʈ�ι̳��� �����Դϴ�.
	 */
	enum class EState : int32_t
	{
		NONE   = 0,
		WAIT   = 1,
		ACTIVE = 2,
		DONE   = 3,
	};


public:
	/**
	 * @brief ������ ��Ʈ�ι̳븦 �����ϴ� �������Դϴ�.
	 * 
	 * @param Signature ��Ʈ�ι̳��� �ñ״�ó ���Դϴ�.
	 * @param TilePosition ��Ʈ�ι̳��� Ÿ�� �� ���� ����� ��ǥ�Դϴ�.
	 * 
	 * @throws ��Ʈ�ι̳� ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	Tetromino(const std::string& Signature, const Vec2i& TilePosition);


	/**
	 * @brief ��Ʈ�ι̳� �������Դϴ�.
	 * 
	 * @param Signature ��Ʈ�ι̳��� �ñ״�ó ���Դϴ�.
	 * @param TilePosition ��Ʈ�ι̳��� Ÿ�� �� ���� ����� ��ǥ�Դϴ�.
	 * @param Shape ��Ʈ�ι̳��� ����Դϴ�.
	 * @param Color ��Ʈ�ι̳� Ÿ���� ���� Ÿ���Դϴ�.
	 * 
	 * @throws ��Ʈ�ι̳� ������ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	Tetromino(const std::string& Signature, const Vec2i& TilePosition, const EShape& Shape, const Tile::EColor& Color);


	/**
	 * @brief ��Ʈ������ ��Ʈ�ι̳� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Tetromino() {}


	/**
	 * @brief ���������� ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Tetromino);


	/**
	 * @brief ��Ʈ������ ��Ʈ�ι̳븦 ������Ʈ�մϴ�.
	 *
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief ��Ʈ�ι̳��� ���¸� ����ϴ�.
	 * 
	 * @return ��Ʈ�ι̳��� ���¸� ��ȯ�մϴ�.
	 */
	EState GetState() const { return State_; }


	/**
	 * @brief ��Ʈ�ι̳��� ���¸� �����մϴ�.
	 * 
	 * @param State ������ ��Ʈ�ι̳��� �����Դϴ�.
	 */
	void SetState(const EState& State) { State_ = State; }


	/**
	 * @brief ��Ʈ�ι̳븦 Ư�� �������� �̵���ŵ�ϴ�.
	 * 
	 * @note �ش� �������� �̵��� �� ���ٸ� �ƹ� ���۵� �������� �ʽ��ϴ�.
	 *
	 * @param Direction ��Ʈ�ι̳븦 �̵� ��ų �����Դϴ�.
	 */
	void Move(const EDirection& Direction);


	/**
	 * @brief ��Ʈ�ι̳븦 Ư�� �������� �̵���ų �� �ִ��� Ȯ���մϴ�.
	 * 
	 * @param Direction �˻縦 ������ �����Դϴ�.
	 * 
	 * @return �̵��� �� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool CanMove(const EDirection& Direction);


	/**
	 * @brief ��Ʈ�ι̳븦 Ư�� ��ġ�� �̵���ŵ�ϴ�.
	 * 
	 * @note �ش� �������� �̵��� �� ���ٸ� �ƹ� ���۵� �������� �ʽ��ϴ�.
	 * 
	 * @param Position ��Ʈ�ι̳븦 �̵� ��ų Ÿ�� �� ���� ��ġ�Դϴ�.
	 */
	void Teleport(const Vec2i& Position);


	/**
	 * @brief ��Ʈ�ι̳븦 Ư�� ��ġ�� �̵���ų �� �ִ��� �˻��մϴ�.
	 * 
	 * @param Position �˻��� ��ġ�Դϴ�.
	 * 
	 * @return �̵���ų �� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	bool CanTeleport(const Vec2i& Position);


	/**
	 * @brief ��Ʈ�ι̳��� �ִ� ���� �ð��� ����ϴ�.
	 *
	 * @return ��Ʈ�ι̳��� �ִ� ���� �ð��� ��ȯ�մϴ�.
	 */
	static float GetMaxAccrueTickTime() { return MaxAccrueTickTime_; }


	/**
	 * @brief ��Ʈ�ι̳��� �ִ� ���� �ð��� �����մϴ�.
	 * 
	 * @note �ð��� �ʴ��� �Դϴ�.
	 * 
	 * @param MaxAccrueTickTime ������ �ִ� ���� �ð��Դϴ�.
	 */
	static void SetMaxAccrueTickTime(const float& MaxAccrueTickTime);


private:
	/**
	 * @brief ��Ʈ�ι̳� Ÿ���� �����մϴ�.
	 * 
	 * @param TilePosition Ÿ�� ���� ��Ʈ�ι̳� ���� ��� ��ġ�Դϴ�.
	 * @param Shape ��Ʈ�ι̳��� ����Դϴ�.
	 * @param Color Ÿ���� �����Դϴ�.
	 * 
	 * @return ������ ��Ʈ�ι̳� Ÿ���� ���͸� ��ȯ�մϴ�.
	 */
	static std::vector<Tile> CreateTetrominoTile(const Vec2i& TilePosition, const EShape& Shape, const Tile::EColor& Color);


	/**
	 * @brief ��Ʈ�ι̳븦 Ư�� �������� �����Դϴ�.
	 * 
	 * @param TilePosition Ÿ�� �� ���� ������ ��Ʈ�ι̳��� ���� ��� ��ǥ�Դϴ�.
	 * @param Tiles ��Ʈ�ι̳��� Ÿ���Դϴ�.
	 * @param Shape ��Ʈ�ι̳��� ����Դϴ�.
	 * @param Direction ��Ʈ�ι̳밡 ������ �����Դϴ�.
	 */
	static void Move(Vec2i& TilePosition, std::vector<Tile>& Tiles, const EShape& Shape, const EDirection& Direction);


	/**
	 * @brief ��Ʈ�ι̳븦 Ư�� �������� ������ �� �ִ��� Ȯ���մϴ�.
	 * 
	 * @param TilePosition Ÿ�� �� ���� ������ ��Ʈ�ι̳��� ���� ��� ��ǥ�Դϴ�.
	 * @param Tiles ��Ʈ�ι̳��� Ÿ���Դϴ�.
	 * @param Shape ��Ʈ�ι̳��� ����Դϴ�.
	 * @param Direction ��Ʈ�ι̳밡 ������ �����Դϴ�.
	 * 
	 * @return ��Ʈ�ι̳븦 ������ �� �ִٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	static bool CanMove(Vec2i& TilePosition, std::vector<Tile>& Tiles, const EShape& Shape, const EDirection& Direction);


	/**
	 * @brief ��Ʈ�ι̳븦 Ư�� ��ġ�� �̵���ŵ�ϴ�.
	 * 
	 * @note �ش� �������� �̵��� �� ���ٸ� �ƹ� ���۵� �������� �ʽ��ϴ�.
	 * 
	 * @param TilePosition Ÿ�� �� ���� ������ ��Ʈ�ι̳��� ���� ��� ��ǥ�Դϴ�.
	 * @param Tiles ��Ʈ�ι̳��� Ÿ���Դϴ�.
	 * @param Position ��Ʈ�ι̳밡 �̵��� ��ġ�Դϴ�.
	 * 
	 * @param Position ��Ʈ�ι̳븦 �̵� ��ų Ÿ�� �� ���� ��ġ�Դϴ�.
	 */
	static void Teleport(Vec2i& TilePosition, std::vector<Tile>& Tiles, const Vec2i& Position);


	/**
	 * @brief ��Ʈ�ι̳븦 Ư�� ��ġ�� �̵���ų �� �ִ��� �˻��մϴ�.
	 *
	 * @param TilePosition Ÿ�� �� ���� ������ ��Ʈ�ι̳��� ���� ��� ��ǥ�Դϴ�.
	 * @param Tiles ��Ʈ�ι̳��� Ÿ���Դϴ�.
	 * @param Position �˻��� ��ġ�Դϴ�.
	 *
	 * @return �̵���ų �� �ִٸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	static bool CanTeleport(Vec2i& TilePosition, std::vector<Tile>& Tiles, const Vec2i& Position);


	/**
	 * @brief ��Ʈ�ι̳� ��翡 ���� ������ ũ�⸦ ����ϴ�.
	 * 
	 * @param Shape ��Ʈ�ι̳� ����Դϴ�.
	 * 
	 * @return ��Ʈ�ι̳��� ���� ũ�⸦ ��ȯ�մϴ�.
	 */
	static int32_t GetBoundSize(const EShape& Shape);


	/**
	 * ��Ʈ�ι̳� �������� �ݴ� ������ ����ϴ�.
	 *
	 * @param Direction �ݴ� ������ �˰� ���� �������Դϴ�.
	 *
	 * @return �������� �ݴ� ������ ��ȯ�մϴ�.
	 */
	static EDirection GetCountDirection(const EDirection& Direction);


private:
	/**
	 * @brief Ÿ�ϸ� ���� ��Ʈ�ι̳� ���� ����� ��ǥ�Դϴ�.
	 */
	Vec2i TilePosition_;


	/**
	 * @brief ��Ʈ�ι̳��� ����Դϴ�.
	 */
	EShape Shape_ = EShape::NONE;


	/**
	 * @brief ��Ʈ�ι̳��� Ÿ���Դϴ�.
	 */
	std::vector<Tile> Tiles_;


	/**
	 * @brief ��Ʈ�ι̳��� �����Դϴ�.
	 * 
	 * @note �⺻ ���´� ������� �����Դϴ�.
	 */
	EState State_ = EState::WAIT;


	/**
	 * @brief ��Ʈ�ι̳��� ������Ʈ ���� �ð��Դϴ�. 
	 */
	float AccrueTickTime_ = 0.0f;


	/**
	 * @brief ��Ʈ�ι̳��� �ִ� ������Ʈ ���� �ð��Դϴ�.
	 */
	static float MaxAccrueTickTime_;
};