#pragma once

#include <array>

#include "Vector.hpp"
#include "Scene.h"

class Button;


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
		NONE  = 0,
		PLAY  = 1,
		PAUSE = 2,
		DONE  = 3,
	};


public:
	/**
	 * @brief ���� �÷��� ���� �⺻ �������Դϴ�.
	 */
	PlayScene();


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
	EState CurrentState_ = EState::NONE;


	/**
	 * @brief �÷��� �ð��Դϴ�.
	 * 
	 * @note �÷��� �ð��� �ʴ����Դϴ�.
	 */
	float PlayTime_ = 0.0f;


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


	/**
	 * @brief �÷��� ���� ��ư�Դϴ�.
	 */
	std::array<Button*, 11> Buttons_;
};