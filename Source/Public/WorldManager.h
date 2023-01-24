#pragma once

#include "Macro.h"

#include <unordered_map>

class GameObject;


/**
 * @brief 게임 오브젝트가 위치할 2D 월드입니다.
 * 
 * @note 이 클래스는 싱글턴으로 헤더만 추가하면 바로 사용할 수 있습니다.
 */
class WorldManager
{
public:
	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(WorldManager);


	/**
	 * @brief WorldManager의 싱글 인스턴스를 얻습니다.
	 *
	 * @return WorldManager의 인스턴스를 반환합니다.
	 */
	static WorldManager& Get()
	{
		static WorldManager Instance;
		return Instance;
	}


	/**
	 * 2D 월드에 오브젝트를 등록합니다.
	 *
	 * @param Object 2D 월드에 등록할 오브젝트입니다.
	 * @param Key 2D 월드에 추가할 오브젝트의 키 값입니다.
	 */
	void RegisterOjbect(GameObject* Object, const std::string& Key);


	/**
	 * 2D 월드에 오브젝트가 등록되었는지 확인합니다.
	 *
	 * @param Key 등록되었는지 확인할 오브젝트의 키 값입니다.
	 *
	 * @return 게임 월드에 등록 되었다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsRegisterObject(const std::string& Key);


	/**
	 * 키 값에 대응하는 2D 월드의 오브젝트를 얻습니다.
	 *
	 * @param Key 게임 월드에 있는 오브젝트의 키 값입니다.
	 *
	 * @return 키 값에 대응하는 게임 월드의 오브젝트가 존재하면 오브젝트의 포인터 값을, 그렇지 않으면 nullptr를 반환합니다.
	 */
	GameObject* GetObject(const std::string& Key);


	/**
	 * @brief 2D 월드에 오브젝트를 등록 해제합니다.
	 * 
	 * @note 해당 오브젝트가 존재하지 않는다면 아무 동작도 하지 않습니다.
	 *
	 * @param Key 게임 월드에서 등록 해제할 오브젝트의 키 값입니다.
	 */
	void UnregisterObject(const std::string& Key);

	
private:
	/**
	 * 게임 월드의 생성자입니다.
	 */
	WorldManager() = default;


	/**
	 * 게임 월드의 가상 소멸자입니다.
	 */
	virtual ~WorldManager() = default;


	/**
	 * @brief 키 값이 존재하는지 확인합니다.
	 *
	 * @param Key 충돌하는지 확인할 키 값입니다.
	 * @param KeyValueResource 키-값 쌍의 자료구조입니다.
	 *
	 * @return 이미 키 값에 대응하는 값이 존재하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	template<typename TKey, typename TValue>
	bool IsExistKey(const TKey& Key, const std::unordered_map<TKey, TValue>& KeyValueResource)
	{
		return KeyValueResource.find(Key) != KeyValueResource.end();
	}


	/**
	 * @brief 키 값에 대응하는 값을 삭제합니다.
	 *
	 * @note 키 값에 대응하는 값이 존재하지 않는다면 아무 동작도 수행하지 않습니다.
	 *
	 * @param Key 삭제할 데이터의 키 값입니다.
	 * @param KeyValueResource 삭제할 키-값 쌍의 자료구조입니다.
	 */
	template <typename TKey, typename TValue>
	void Remove(const TKey& Key, std::unordered_map<TKey, TValue>& KeyValueResourc)
	{
		if (IsExistKey<TKey, TValue>(Key, KeyValueResourc))
		{
			KeyValueResourc.erase(Key);
		}
	}


private:
	/**
	 * @brief 게임 월드 내에 존재하는 게임 오브젝트입니다.
	 */
	std::unordered_map<std::string, GameObject*> GameObjects_;
};