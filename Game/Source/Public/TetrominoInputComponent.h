#pragma once

#include "Tetromino.h"
#include "InputComponent.h"


/**
 * @brief ��Ʈ�ι̳��� �Է� ó�� ������Ʈ�Դϴ�.
 */
class TetrominoInputComponent : public InputComponent
{
public:
	/**
	 * @brief ��Ʈ�ι̳��� �Է� ó�� ������Ʈ �������Դϴ�.
	 * 
	 * @param Object �� ������Ʈ�� �����ϴ� ������Ʈ�� ������ ���Դϴ�.
	 */
	TetrominoInputComponent(GameObject* Object)
		: InputComponent(Object) {}


	/**
	 * @brief ��Ʈ�ι̳��� �Է� ó�� ������Ʈ ���� �Ҹ����Դϴ�.
	 */
	virtual ~TetrominoInputComponent() {}


	/**
	 * @brief ������Ʈ�� ���� ������ �� ���Կ����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(TetrominoInputComponent);


	/**
	 * @brief ��Ʈ�ι̳��� �Է� ó�� ������Ʈ�� ������Ʈ�մϴ�.
	 * 
	 * @param DeltaSecons �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	void Tick(float DeltaSecons);

	
	/**
	 * @brief ������ ���� �ð��� ����ϴ�.
	 * 
	 * @note �ð��� �ʴ��� �Դϴ�.
	 * 
	 * @return ������ ���� �ð��� ��ȯ�մϴ�.
	 */
	float GetAccrueFrameTime() const { return AccrueFrameTime_; }


	/**
	 * @brief ������ ���� �ð��� �ʱ�ȭ�մϴ�.
	 * 
	 * @note ���� �ð����� 0���� ����ϴ�.
	 */
	void ResetAccrueFrameTime() { AccrueFrameTime_ = 0.0f; }

	
	/**
	 * @brief ��Ʈ�ι̳��� �̵� ������ ����ϴ�.
	 * 
	 * @return ��Ʈ�ι̳��� �̵� ������ ��ȯ�մϴ�.
	 */
	Tetromino::EDirection GetDirection() const { return Direction_; }


private:
	/**
	 * @brief ������ ���� �ð��Դϴ�.
	 */
	float AccrueFrameTime_ = 0.0f;


	/**
	 * @brief ��Ʈ�ι̳��� �̵� �����Դϴ�.
	 */
	Tetromino::EDirection Direction_ = Tetromino::EDirection::NONE;
};