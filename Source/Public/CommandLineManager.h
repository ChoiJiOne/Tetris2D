#pragma once

#include "Macro.h"

#include <vector>
#include <unordered_map>


/**
 * @brief Ŀ�ǵ� ������ �Ľ��ϰ�, ���ڸ� �����մϴ�.
 * 
 * @note �� Ŭ������ �̱������� ����� �߰��ϸ� �ٷ� ����� �� �ֽ��ϴ�.
 */
class CommandLineManager
{
public:
	/**
	 * @brief ���� �����ڿ� ���� �����ڸ� �����մϴ�.
	 */
	DISALLOW_COPY_AND_ASSIGN(CommandLineManager);


	/**
	 * @brief CommandLineManager�� �ν��Ͻ��� ����ϴ�.
	 *
	 * @return CommandLineManager�� �ν��Ͻ��� �����ڸ� ��ȯ�մϴ�.
	 */
	static CommandLineManager& Get()
	{
		static CommandLineManager Instance;
		return Instance;
	}


	/**
	 * @brief ��ü Ŀ�ǵ� ������ ����ϴ�.
	 *
	 * @return ��ü Ŀ�ǵ� ���� ���ڿ��� ��ȯ�մϴ�.
	 */
	const std::string& GetCommanLine() { return CommandLine_; }


	/**
	 * @brief Ŀ�ǵ� ���ο� �ɼ��� �����ϴ��� Ȯ���մϴ�.
	 *
	 * @param Option �����ϴ��� Ȯ���� �ɼ��Դϴ�.
	 *
	 * @return �ɼ��� �����ϸ� true, �׷��� �ʴٸ� false�� ��ȯ�մϴ�.
	 */
	bool HaveOption(const std::string& Option);


	/**
	 * @brief �ɼǿ� �ش��ϴ� ���� ����ϴ�.
	 *
	 * @param Option �ɼ��Դϴ�.
	 *
	 * @return �ɼǿ� �����ϴ� ���� ��ȯ�մϴ�. �ɼǿ� �����ϴ� ���� �������� �ʴ´ٸ�, �� ���ڿ��� ��ȯ�մϴ�.
	 */
	std::string GetValue(const std::string& Option);


private:
	/**
	 * @brief Ŀ�ǵ� ������ �Ľ��ϰ�, ���ڸ� �����ϴ� Ŭ������ �������Դϴ�.
	 */
	CommandLineManager();


	/**
	 * @brief Ŀ�ǵ� ������ �Ľ��ϰ�, ���ڸ� �����ϴ� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~CommandLineManager() = default;


private:
	/**
	 * ���� ���� �� ���� ���� ��ü Ŀ�ǵ� �����Դϴ�.
	 */
	std::string CommandLine_;


	/**
	 * ���� ���� �ÿ� ���� ���� Ŀ�ǵ� ������ �����Դϴ�.
	 */
	std::vector<std::string> Arguments_;


	/**
	 * Ŀ�ǵ� ���� �Է����� ���� �ɼ��Դϴ�.
	 */
	std::unordered_map<std::string, std::string> Options_;
};