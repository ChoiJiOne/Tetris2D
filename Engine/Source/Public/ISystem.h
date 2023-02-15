#pragma once


/**
 * @brief 게임 개발에 필요한 핵심 요소(렌더러, 입력 처리 ...) 인터페이스 클래스입니다.
 */
class ISystem
{
public:
	/**
	 * @brief 시스템의 디폴트 생성자입니다.
	 */
	ISystem() = default;


	/**
	 * @brief 시스템의 가상 소멸자입니다.
	 */
	virtual ~ISystem() {}


	/**
	 * @brief 시스템을 초기화합니다.
	 */
	virtual void Setup() = 0;


	/**
	 * @brief 시스템을 해제합니다.
	 */
	virtual void Cleanup() = 0;
};