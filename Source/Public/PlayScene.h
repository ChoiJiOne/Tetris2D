#pragma once

#include "Vector.hpp"
#include "Scene.h"


/**
 * @brief ���� �÷��� ���Դϴ�.
 */
class PlayScene : public Scene
{
public:
	/**
	 * @brief ���� �÷��� �����Դϴ�.
	 */
	enum class EState : int32_t
	{
		PLAY = 0,
		WAIT = 1,
		DONE = 2,
	};


public:
	/**
	 * @brief ���� �÷��� ���� �⺻ �������Դϴ�.
	 */
	PlayScene() = default;


	/**
	 * @brief ���� �÷��� ���� ���� �Ҹ����Դϴ�
	 */
	virtual ~PlayScene();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(PlayScene);


	/**
	 * @brief ���� �÷��� ���� ������Ʈ�մϴ�.
	 * 
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;


	/**
	 * @brief ���� �÷��� ���� �����մϴ�.
	 */
	void Reset();


	/**
	 * @brief ������ ����Ǿ����� Ȯ���մϴ�.
	 * 
	 * @return ������ ����Ǿ��ٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	EState GetCurrentState() const { return CurrentState_; }


private:
	/**
	 * @brief ���� ���� ���� �����Դϴ�.
	 */
	EState CurrentState_ = EState::WAIT;


	/**
	 * @brief ���� ���� ī�޶� �߽� ��ġ�Դϴ�.
	 */
	Vec2f CameraPosition_;


	/**
	 * @brief ���� ���� Ÿ�� ���� �߽� ��ġ�Դϴ�.
	 */
	Vec2f TileMapPosition_;


	/**
	 * @brief ��Ʈ�ι̳��� ���� ��ġ�Դϴ�.
	 */
	Vec2i StartPosition_;


	/**
	 * @brief ��Ʈ�ι̳��� ��� ��ġ�Դϴ�.
	 */
	Vec2i WaitPosition_;


	/**
	 * @brief ������ ��Ʈ�ι̳� ���Դϴ�.
	 */
	int32_t CountOfTetromino_ = 0;


	/**
	 * @brief ���� ��Ʈ�ι̳��� ��ȣ�Դϴ�.
	 */
	int32_t CurrentTetromino_ = 0;
};