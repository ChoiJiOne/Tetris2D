#pragma once

#include "Macro.h"
#include "Camera2D.h"
#include "GameObject.h"
#include "Utils.hpp"


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
	 * @brief 2D 월드의 게임 오브젝트를 생성합니다.
	 * 
	 * @param Signature 게임 오브젝트를 구분하는 시그니처 값입니다.
	 * @param Args 게임 오브젝트를 생성하기 위한 가변 인자입니다.
	 * 
	 * @thows 게임 오브젝트 생성에 실패하면 C++ 표준 예외를 던집니다.
	 * 
	 * @return 생성된 게임 오브젝트의 포인터를 반환합니다.
	 */
	template <typename Object, typename... Types>
	Object* CreateGameObject(const std::string& Signature, Types... Args)
	{
		CHECK(!IsExistGameObject(Signature), "already exist game object or collision key value");

		std::unique_ptr<Object> NewObject = std::make_unique<Object>(Signature, Args...);
		GameObjects_.insert({ Signature, std::move(NewObject) });

		return reinterpret_cast<Object*>(GameObjects_.at(Signature).get());
	}

	
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
	 * @return 키 값에 대응하는 게임 월드의 오브젝트가 존재하면 주소 값을 반환, 그렇지 않으면 nullptr를 반환합니다.
	 */
	template <typename Object>
	Object* GetGameObject(const std::string& Key)
	{
		if (!IsExistGameObject(Key)) return nullptr;
			 
		return reinterpret_cast<Object*>(GameObjects_.at(Key).get());
	}


	/**
	 * @brief 2D 월드에 오브젝트를 등록 해제합니다.
	 * 
	 * @note 해당 오브젝트가 존재하지 않는다면 아무 동작도 하지 않습니다.
	 *
	 * @param Key 게임 월드에서 등록 해제할 오브젝트의 키 값입니다.
	 */
	void UnregisterObject(const std::string& Key);


	/**
	 * @brief 2D 월드의 메인 카메라를 생성합니다.
	 * 
	 * @param Position 2D World의 카메라 위치입니다.
	 * @param Width 카메라의 가로 크기입니다.
	 * @param Height 카메라의 세로 크기입니다.
	 * @param Rotate 카메라의 이동 방향입니다. 이때 회전각은 라디안 각도 기준입니다.
	 * @param Velocity 카메라의 이동 속력입니다.
	 * 
	 * @return 생성한 2D 월드 카메라의 참조자를 반환합니다.
	 */
	Camera2D& CreateMainCamera(
		const Vec2f& Position,
		const float& Width,
		const float& Height,
		const float& Rotate = 0.0f,
		const float& Velocity = 0.0f
	);


	/**
	 * @brief 2D 월드의 카메라를 얻습니다.
	 * 
	 * @return 2D 월드의 카메라를 반환합니다.
	 */
	Camera2D& GetMainCamera();


	/**
	 * @brief 2D 월드의 카메라를 파괴합니다.
	 */
	void DestroyMainCamera();

	
private:
	/**
	 * @brief 게임 월드의 생성자입니다.
	 */
	WorldManager() = default;


	/**
	 * @brief 게임 월드의 가상 소멸자입니다.
	 */
	virtual ~WorldManager();


	/**
	 * @brief 게임 월드가 관리하는 게임 오브젝트가 존재하는지 검사합니다.
	 * 
	 * @param Key 검사를 수행할 키 값입니다.
	 * 
	 * @return 키 값에 대응하는 게임 오브젝트가 존재하면 true, 그렇지 않으면 false를 반환합니다.
	 */
	bool IsExistGameObject(const std::string& Key)
	{
		return IsExistKey<std::string, std::unique_ptr<GameObject>>(Key, GameObjects_);
	}


	/**
	 * @brief 게임 월드가 관리하는 게임 오브젝트를 삭제합니다.
	 * 
	 * @note 키 값에 대응하는 게임 오브젝트가 존재하지 않는다면, 아무런 동작도 하지 않습니다.
	 * 
	 * @param Key 게임 오브젝트가 소유하고 있는 컴포넌트의 키 값입니다.
	 */
	void RemoveGameObject(const std::string& Key)
	{
		if (IsExistGameObject(Key))
		{
			RemoveValue<std::string, std::unique_ptr<GameObject>>(Key, GameObjects_);
		}
	}


private:
	/**
	 * @brief 게임 월드 상의 카메라입니다.
	 */
	std::unique_ptr<Camera2D> MainCamera_ = nullptr;
	

	/**
	 * @brief 게임 월드 내에 존재하는 게임 오브젝트입니다.
	 */
	std::unordered_map<std::string, std::unique_ptr<GameObject>> GameObjects_;
};