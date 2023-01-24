#pragma once

#include "Macro.h"

#include <unordered_map>


/**
 * @brief 설정 파일을 파싱 및 관리합니다.
 */
class Config
{
public:
	/**
	 * @brief 설정 파일을 파싱 및 관리하는 클래스의 생성자입니다.
	 * 
	 * @param ResourcePath 설정 파일의 경로입니다.
	 * 
	 * @throws
	 * 파일 읽기에 실패하면 C++ 표준 예외를 던집니다.
	 * 설정 파일 파싱에 실패하면 C++ 표준 예외를 던집니다.
	 */
	Config(const std::string& ResourcePath);


	/**
	 * @brief 설정 파일을 파싱 및 관리하는 클래스의 가상 소멸장입니다.
	 */
	virtual ~Config();


	/**
	 * @brief 복사 생성자와 대입 연산자를 명시적으로 삭제합니다.
	 */
	DISALLOW_COPY_AND_ASSIGN(Config);


	/**
	 * @brief 설정 오브젝트의 값을 얻습니다.
	 * 
	 * @note 키 값에 대응하는 값이 없으면 빈 문자열을 반환합니다.
	 * 
	 * @param Key 설정 오브젝트 값에 대응하는 키 값입니다.
	 * 
	 * @return 설정 오브젝트 키 값에 대응하는 값을 반환합니다.
	 */
	const std::string& GetValue(const std::string& Key);


private:
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
	 * @brief 설정 파일을 로딩합니다.
	 * 
	 * @param ResourcePath 설정 파일의 경로입니다.
	 * @param Buffer[out] 설정 파일 버퍼입니다.
	 */
	bool LoadConfigFromFile(const std::string& ResourcePath, std::vector<uint8_t>& Buffer);


	/**
	 * @brief 설정 파일의 버퍼를 파싱합니다.
	 * 
	 * @param Buffer 설정 파일의 버퍼입니다.
	 * 
	 * @throws
	 * 파
	 * 
	 * @return 키-값 쌍 기반의 파싱 결과를 반환합니다.
	 */
	std::unordered_map<std::string, std::string> ParseConfigFromBuffer(const std::vector<uint8_t>& Buffer);


private:
	/**
	 * @brief 키-값 쌍의 설정 파일 요소입니다.
	 */
	std::unordered_map<std::string, std::string> Config_;
};