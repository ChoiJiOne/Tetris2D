#pragma once

#include "GameObject.h"


/**
 * @brief ��׶����Դϴ�.
 */
class Background : public GameObject
{
public:
	/**
	 * @brief ��׶����� �������Դϴ�.
	 * 
	 * @param Signature ��׶����� �ĺ����Դϴ�.
	 */
	Background(const std::string& Signature);


	/**
	 * @brief ��׶����� ���� �Ҹ����Դϴ�.
	 */
	virtual ~Background() {}


	/**
	 * @brief ���������� ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Background);


	/**
	 * @brief ��׶��带 ������Ʈ�մϴ�.
	 *
	 * @param DeltaSeconds �ʴ��� ��Ÿ �ð����Դϴ�.
	 */
	virtual void Tick(float DeltaSeconds) override;
};