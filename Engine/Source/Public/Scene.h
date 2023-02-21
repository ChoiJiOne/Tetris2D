#pragma once

#include "Macro.h"
#include "Utils.hpp"

#include <vector>
#include <functional>

class GameObject;


/**
 * @brief 게임 씬을 실행합니다.
 */
class Scene
{
public:
	/**
	 * @brief 게임 씬의 기본 생성자입니다.
	 */
	Scene() = default;


	/**
	 * @brief 게임 씬의 가상 소멸자입니다.
	 */
	virtual ~Scene() = default;


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Scene);


	/**
	 * @brief 게임 씬을 업데이트합니다.
	 * 
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Update(float DeltaSeconds) = 0;

	
	/**
	 * @brief 게임 씬을 리셋합니다.
	 */
	virtual void Reset() = 0;


	/**
	 * @brief 씬 전환이 발생했을 때, 실행할 이벤트를 추가합니다.
	 * 
	 * @note 키 값에 대응하는 이벤트가 존재하면 덮어 써집니다.
	 * 
	 * @param Key 이벤트의 키 값입니다.
	 * @param SwitchEvent 씬 전환이 발생할 시 실행할 이벤트입니다.
	 */
	void AddSwitchEvent(const std::string& Key, const std::function<void()>& SwitchEvent) 
	{ 
		SwitchEvents_.insert({ Key, SwitchEvent });
	}


	/**
	 * @brief 씬 전환이 발생했을 때, 실행할 이벤트를 삭제합니다.
	 * 
	 * @param Key 이벤트의 키 값입니다.
	 */
	void RemoveSwitchEvent(const std::string& Key)
	{
		RemoveValue<std::string, std::function<void()>>(Key, SwitchEvents_);
	}


protected:
	/**
	 * @brief 씬 전환이 발생했을 때, 이벤트를 실행합니다.
	 * 
	 * @param Key 실행할 이벤트의 키 값입니다.
	 */
	void RunSwitchEvent(const std::string& Key)
	{
		if (IsExistKey<std::string, std::function<void()>>(Key, SwitchEvents_))
		{
			SwitchEvents_.at(Key)();
		}
	}


private:
	/**
	 * @brief 씬 전환이 발생했을 때, 실행할 이벤트입니다.
	 */
	std::unordered_map<std::string, std::function<void()>> SwitchEvents_;
};