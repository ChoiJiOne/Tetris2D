#pragma once

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
	 * @brief ��Ʈ�ι̳��� �Է� ó�� ������Ʈ�� ������Ʈ�մϴ�.
	 * 
	 * @param DeltaSecons �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	void Tick(float DeltaSecons);


private:
	/**
	 * @brief ������ ���� �ð��Դϴ�.
	 */
	float AccrueFrameTime_ = 0.0f;
};