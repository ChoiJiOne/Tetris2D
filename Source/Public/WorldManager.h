#pragma once

#include "Macro.h"

#include <unordered_map>

class GameObject;


/**
 * @brief ���� ������Ʈ�� ��ġ�� 2D �����Դϴ�.
 * 
 * @note �� Ŭ������ �̱������� ����� �߰��ϸ� �ٷ� ����� �� �ֽ��ϴ�.
 */
class WorldManager
{
public:
	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(WorldManager);


	/**
	 * @brief WorldManager�� �̱� �ν��Ͻ��� ����ϴ�.
	 *
	 * @return WorldManager�� �ν��Ͻ��� ��ȯ�մϴ�.
	 */
	static WorldManager& Get()
	{
		static WorldManager Instance;
		return Instance;
	}


	/**
	 * 2D ���忡 ������Ʈ�� ����մϴ�.
	 *
	 * @param Object 2D ���忡 ����� ������Ʈ�Դϴ�.
	 * @param Key 2D ���忡 �߰��� ������Ʈ�� Ű ���Դϴ�.
	 */
	void RegisterOjbect(GameObject* Object, const std::string& Key);


	/**
	 * 2D ���忡 ������Ʈ�� ��ϵǾ����� Ȯ���մϴ�.
	 *
	 * @param Key ��ϵǾ����� Ȯ���� ������Ʈ�� Ű ���Դϴ�.
	 *
	 * @return ���� ���忡 ��� �Ǿ��ٸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool IsRegisterObject(const std::string& Key);


	/**
	 * Ű ���� �����ϴ� 2D ������ ������Ʈ�� ����ϴ�.
	 *
	 * @param Key ���� ���忡 �ִ� ������Ʈ�� Ű ���Դϴ�.
	 *
	 * @return Ű ���� �����ϴ� ���� ������ ������Ʈ�� �����ϸ� ������Ʈ�� ������ ����, �׷��� ������ nullptr�� ��ȯ�մϴ�.
	 */
	GameObject* GetGameObject(const std::string& Key);


	/**
	 * @brief 2D ���忡 ������Ʈ�� ��� �����մϴ�.
	 * 
	 * @note �ش� ������Ʈ�� �������� �ʴ´ٸ� �ƹ� ���۵� ���� �ʽ��ϴ�.
	 *
	 * @param Key ���� ���忡�� ��� ������ ������Ʈ�� Ű ���Դϴ�.
	 */
	void UnregisterObject(const std::string& Key);

	
private:
	/**
	 * ���� ������ �������Դϴ�.
	 */
	WorldManager() = default;


	/**
	 * ���� ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~WorldManager() = default;


private:
	/**
	 * @brief ���� ���� ���� �����ϴ� ���� ������Ʈ�Դϴ�.
	 */
	std::unordered_map<std::string, GameObject*> GameObjects_;
};