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
		ACTIVE = 2
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
	std::vector<Tile> CreateTetrominoTile(const Vec2i& TilePosition, const EShape& Shape, const Tile::EColor& Color);


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
	 */
	EState State_ = EState::WAIT;
};