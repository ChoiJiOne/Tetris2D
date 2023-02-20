#pragma once

#include "ISystem.h"
#include "Utils.h"

#include <memory>
#include <unordered_map>


/**
 * @brief 게임 내의 시스템 요소를 제공하는 서비스 로케이터입니다.
 * 
 * @note 이 클래스는 정적 클래스로, 헤더만 추가하면 바로 사용할 수 있습니다.
 */
class ServiceLocator
{
public:
	/**
	 * @brief 서비스 로케이터가 제공하는 시스템 타입입니다.
	 */
	enum class EServiceType : int32_t
	{
		INPUT,
		RENDER,
		WORLD,
		CONTENT
	};


public:
	/**
	 * @brief 서비스 로케이터에 시스템을 제공합니다.
	 * 
	 * @param ServiceType 서비스 로케이터가 제공할 시스템 타입입니다.
	 * @param Args 시스템 생성에 필요한 가변 인자입니다.
	 * 
	 * @return 시스템의 포인터 값을 얻습니다.
	 */
	template<typename T, typename... Types>
	static T* ProvideSystem(const EServiceType& ServiceType, Types... Args)
	{
		if (IsExistSystem(ServiceType))
		{
			return nullptr;
		}

		std::unique_ptr<T> System = std::make_unique<T>(Args...);
		LocateSystems_.insert({ ServiceType , std::move(System) });

		return reinterpret_cast<T*>(LocateSystems_[ServiceType].get());
	}


	/**
	 * @brief 서비스 로케이더가 제공하는 시스템을 얻습니다.
	 * 
	 * @param ServiceType 서비스 로케이터가 제공하는 시스템의 타입입니다.
	 * 
	 * @return 서비스 타입에 대응하는 시스템의 포인터 값을 반환합니다.
	 */
	template<typename T>
	static T* GetSystem(const EServiceType& ServiceType)
	{
		if (!IsExistSystem(ServiceType))
		{
			return nullptr;
		}

		return reinterpret_cast<T*>(LocateSystems_[ServiceType].get());
	}


	/**
	 * @brief 서비스 로케이터의 모든 시스템을 정리합니다.
	 */
	static void CleanupSystem();


private:
	/**
	 * @brief 키 값에 대응하는 시스템이 존재 하는지 검사합니다.
	 * 
	 * @param ServiceType 존재하는지 검사할 시스템의 키 값입니다.
	 * 
	 * @return 존재한다면 true, 그렇지 않으면 false를 반환합니다.
	 */
	static bool IsExistSystem(const EServiceType& ServiceType)
	{
		return IsExistKey<EServiceType, std::unique_ptr<ISystem>>(ServiceType, LocateSystems_);
	}


private:
	/**
	 * @brief 서비스 로케이터가 제공하는 시스템입니다.
	 */
	static std::unordered_map<EServiceType, std::unique_ptr<ISystem>> LocateSystems_;
};