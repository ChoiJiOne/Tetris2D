#pragma once

#include "Scene.h"


/**
 * @brief 테트리스 게임의 타이틀 씬입니다.
 */
class TitleScene : public Scene
{
public:
	/**
	 * @brief 테트리스 게임의 타이틀 씬의 생성자입니다.
	 */
	TitleScene();


	/**
	 * @brief 테트리스 게임의 타이틀 씬의 가상 소멸자입니다.
	 */
	virtual ~TitleScene();


	/**
	 * @brief 복사 생성자와 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(TitleScene);


	/**
	 * @brief 타이틀 씬을 업데이트합니다.
	 * 
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Update(float DeltaSeconds) override;


	/**
	 * @brief 타이틀 씬을 리셋합니다.
	 */
	virtual void Reset() override;


private:
	/**
	 * @brief 씬 내의 게임 오브젝트입니다.
	 */
	std::vector<GameObject*> SceneObjects_;

};