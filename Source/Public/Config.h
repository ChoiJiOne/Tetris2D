#pragma once

#include "Macro.h"

#include <unordered_map>


/**
 * @brief ���� ������ �Ľ� �� �����մϴ�.
 */
class Config
{
public:
	/**
	 * @brief ���� ������ �Ľ� �� �����ϴ� Ŭ������ �������Դϴ�.
	 * 
	 * @param ResourcePath ���� ������ ����Դϴ�.
	 * 
	 * @throws
	 * ���� �б⿡ �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 * ���� ���� �Ľ̿� �����ϸ� C++ ǥ�� ���ܸ� �����ϴ�.
	 */
	Config(const std::string& ResourcePath);


	/**
	 * @brief ���� ������ �Ľ� �� �����ϴ� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Config();


	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� ���������� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(Config);


	/**
	 * @brief ���� ������Ʈ�� ���� ����ϴ�.
	 * 
	 * @param Key ���� ������Ʈ ���� �����ϴ� Ű ���Դϴ�.
	 * 
	 * @throws Ű ���� �����ϴ� ���� ������ C++ ǥ�� ���ܸ� �����ϴ�.
	 * 
	 * @return ���� ������Ʈ Ű ���� �����ϴ� ���� ��ȯ�մϴ�.
	 */
	const std::string& GetValue(const std::string& Key);


private:
	/**
	 * @brief Ű ���� �����ϴ��� Ȯ���մϴ�.
	 *
	 * @param Key �浹�ϴ��� Ȯ���� Ű ���Դϴ�.
	 * @param KeyValueResource Ű-�� ���� �ڷᱸ���Դϴ�.
	 *
	 * @return �̹� Ű ���� �����ϴ� ���� �����ϸ� true, �׷��� ������ false�� ��ȯ�մϴ�.
	 */
	template<typename TKey, typename TValue>
	bool IsExistKey(const TKey& Key, const std::unordered_map<TKey, TValue>& KeyValueResource)
	{
		return KeyValueResource.find(Key) != KeyValueResource.end();
	}


	/**
	 * @brief ���� ������ �ε��մϴ�.
	 * 
	 * @param ResourcePath ���� ������ ����Դϴ�.
	 * @param Buffer[out] ���� ���� �����Դϴ�.
	 */
	bool LoadConfigFromFile(const std::string& ResourcePath, std::vector<uint8_t>& Buffer);


	/**
	 * @brief ���� ������ ���۸� �Ľ��մϴ�.
	 * 
	 * @param Buffer ���� ������ �����Դϴ�.
	 * 
	 * @throws
	 * ��
	 * 
	 * @return Ű-�� �� ����� �Ľ� ����� ��ȯ�մϴ�.
	 */
	std::unordered_map<std::string, std::string> ParseConfigFromBuffer(const std::vector<uint8_t>& Buffer);


private:
	/**
	 * @brief Ű-�� ���� ���� ���� ����Դϴ�.
	 */
	std::unordered_map<std::string, std::string> Config_;
};