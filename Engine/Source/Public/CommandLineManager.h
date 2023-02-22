#pragma once

#include "Macro.h"

#include <vector>
#include <unordered_map>


/**
 * @brief 커맨드 라인을 파싱하고, 인자를 관리합니다.
 * 
 * @note 이 클래스는 싱글턴으로 헤더만 추가하면 바로 사용할 수 있습니다.
 */
class CommandLineManager
{
public:
	/**
	 * @brief 복사 생성자와 대입 연산자를 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(CommandLineManager);


	/**
	 * @brief CommandLineManager의 인스턴스를 얻습니다.
	 *
	 * @return CommandLineManager의 인스턴스의 참조자를 반환합니다.
	 */
	static CommandLineManager& Get()
	{
		static CommandLineManager Instance;
		return Instance;
	}


	/**
	 * @brief UTF-8 기반의 전체 커맨드 라인을 얻습니다.
	 *
	 * @return UTF-8 기반의 전체 커맨드 라인 문자열을 반환합니다.
	 */
	const std::string& GetFullCommanLineA() { return CommandLineA_; }


	/**
	 * @brief UTF-16 기반의 전체 커맨드 라인을 얻습니다.
	 *
	 * @return UTF-16 기반의 전체 커맨드 라인 문자열을 반환합니다.
	 */
	const std::wstring& GetFullCommanLineW() { return CommandLineW_; }


	/**
	 * @brief UTF-8 기반의 커맨드 라인에 옵션이 존재하는지 확인합니다.
	 *
	 * @param Option 존재하는지 확인할 옵션입니다.
	 *
	 * @return 옵션이 존재하면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool HaveOption(const std::string& Option);



	/**
	 * @brief UTF-16 기반의 커맨드 라인에 옵션이 존재하는지 확인합니다.
	 *
	 * @param Option 존재하는지 확인할 옵션입니다.
	 *
	 * @return 옵션이 존재하면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool HaveOption(const std::wstring& Option);


	/**
	 * @brief UTF-8 기반의 옵션에 해당하는 값을 얻습니다.
	 *
	 * @param Option 옵션입니다.
	 *
	 * @return 옵션에 대응하는 값을 반환합니다. 옵션에 대응하는 값이 존재하지 않는다면, 빈 문자열을 반환합니다.
	 */
	std::string GetValue(const std::string& Option);


	/**
	 * @brief UTF-16 기반의 옵션에 해당하는 값을 얻습니다.
	 *
	 * @param Option 옵션입니다.
	 *
	 * @return 옵션에 대응하는 값을 반환합니다. 옵션에 대응하는 값이 존재하지 않는다면, 빈 문자열을 반환합니다.
	 */
	std::wstring GetValue(const std::wstring& Option);


private:
	/**
	 * @brief 커맨드 라인을 파싱하고, 인자를 관리하는 클래스의 생성자입니다.
	 */
	CommandLineManager();


	/**
	 * @brief 커맨드 라인을 파싱하고, 인자를 관리하는 클래스의 가상 소멸자입니다.
	 */
	virtual ~CommandLineManager() = default;


	/**
	 * @brief UTF-8 기반의 초기화를 수행합니다. 
	 */
	void ParseCommandLineA();


	/**
	 * @brief UTF-16 기반의 초기화를 수행합니다.
	 */
	void ParseCommandLineW();


private:
	/**
	 * @brief 게임 실행 시 전달 받은 UTF-8 커맨드 라인입니다.
	 */
	std::string CommandLineA_;


	/**
	 * @brief 게임 실행 시 전달 받은 UTF-16 커맨드 라인입니다.
	 */
	std::wstring CommandLineW_;


	/**
	 * @brief 게임 실행 시 전달 받은 UTF-8 커맨드 라인 인자입니다.
	 */
	std::vector<std::string> ArgumentsA_;


	/**
	 * @brief 게임 실행 시 전달 받은 UTF-16 커맨드 라인 인자입니다.
	 */
	std::vector<std::wstring> ArgumentsW_;


	/**
	 * @brief 커맨드 라인 입력으로 받은 UTF-8 옵션입니다.
	 */
	std::unordered_map<std::string, std::string> OptionsA_;


	/**
	 * @brief 커맨드 라인 입력으로 받은 UTF-16 옵션입니다.
	 */
	std::unordered_map<std::wstring, std::wstring> OptionsW_;
};