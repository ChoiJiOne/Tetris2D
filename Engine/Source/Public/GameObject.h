#pragma once

#include "Macro.h"
#include "Utils.hpp"

#include <memory>

class Component;


/**
 * @brief 게임 오브젝트 클래스입니다.
 * 
 * @note 게임 내의 모든 오브젝트는 이 클래스를 상속 받아야 합니다.
 */
class GameObject
{
public:
	/**
	 * @brief 게임 오브젝트의 생성자입니다.
	 * 
	 * @param Signature 게임 오브젝트를 구분하기 위한 시그니처 문자열입니다.
	 */
	GameObject(const std::string& Signature);


	/**
	 * @brief 게임 오브젝트의 가상 소멸자입니다.
	 */
	virtual ~GameObject();


	/**
	 * @brief 게임 오브젝트의 복사 생성자 및 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(GameObject);


	/**
	 * @brief 게임 오브젝트를 업데이트합니다.
	 *
	 * @param DeltaSeconds 초단위 델타 시간값입니다.
	 */
	virtual void Tick(float DeltaSeconds) = 0;


	/**
	 * @brief 게임 오브젝트에 컴포넌트를 추가합니다.
	 * 
	 * @note 키 값에 대응하는 컴포넌트가 존재한다면 아무런 동작도 수행하지 않습니다.
	 *
	 * @param Key 추가할 컴포넌트의 키값입니다.
	 * @param Args 컴포넌트에 필요한 가변 인자입니다.
	 * 
	 * @return 추가한 컴포넌트의 포인터 값을 반환합니다.
	 */
	template<typename T, typename... Types>
	T* AddComponent(const std::string& Key, Types... Args)
	{
		if (IsExistComponent(Key)) return nullptr;

		std::unique_ptr<T> NewComponent = std::make_unique<T>(this, Args...);
		Components_.insert({ Key, std::move(NewComponent) });

		return reinterpret_cast<T*>(Components_[Key].get());
	}


	/**
	 * @brief 게임 오브젝트가 소유하고 있는 컴포넌트를 얻습니다.
	 *
	 * @param Key 게임 오브젝트가 소유하고 있는 컴포넌트의 키 값입니다.
	 *
	 * @return 키 값에 대응하는 컴포넌트가 존재하면 주소 값을 반환, 그렇지 않으면 nullptr를 반환합니다.
	 */
	template<typename T>
	T* GetComponent(const std::string& Key)
	{
		if (!IsExistComponent(Key)) return nullptr;

		return reinterpret_cast<T*>(Components_.at(Key).get());
	}


	/**
	 * @brief 게임 오브젝트가 소유하고 있는 컴포넌트를 삭제합니다.
	 * 
	 * @note 키 값에 대응하는 컴포넌트가 존재하지 않는다면, 아무런 동작도 하지 않습니다.
	 *
	 * @param Key 게임 오브젝트가 소유하고 있는 컴포넌트의 키 값입니다.
	 */
	template<typename T>
	void RemoveComponent(const std::string& Key)
	{
		if (IsExistComponent(Key))
		{
			RemoveValue<std::string, std::unique_ptr<Component>>(Key, Components_);
		}
	}


	/**
	 * @brief 키 값에 대응하는 컴포넌트가 존재하는지 검사합니다.
	 *
	 * @param Key 검사를 수행할 키 값입니다.
	 *
	 * @return 키 값에 대응하는 컴포넌트가 존재하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsExistComponent(const std::string& Key)
	{
		return IsExistKey<std::string, std::unique_ptr<Component>>(Key, Components_);
	}


protected:
	/**
	 * @brief 게임 오브젝트의 시그니처입니다.
	 */
	std::string Signature_;


	/**
	 * @brief 게임 오브젝트가 소유하고 있는 컴포넌트입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<Component>> Components_;
};