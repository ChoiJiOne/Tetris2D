#pragma once

#include <cstdint>

namespace Game
{
	class Input;
	class Graphics;
}


/**
 * 테트리스 게임 플레이어 클래스입니다.
 */
class Player
{
public:
	/**
	 * 테트리스 게임의 상태입니다.
	 * 
	 * Start : 게임의 시작 상태입니다. 이때 플레이어의 레벨을 선택할 수 있습니다.
	 * Play : 게임의 플레이 상태입니다. 이때 플레이어는 게임을 진행할 수 있습니다.
	 * Paused : 게임의 중지 상태입니다. 이때 플레이어는 잠시 게임을 중단시킬 수 있습니다.
	 * Over : 게임의 종료 상태입니다. 이때 플레이어는 게임을 플레이할 수 없습니다.
	 */
	enum class EGameState : int32_t
	{
		Start  = 0,
		Play   = 1,
		Paused = 2,
		Over   = 3,
	};


public:
	/**
	 * 테트리스 게임 플레이어 클래스의 생성자입니다.
	 * @note 테트리스 게임 플레이어 클래스를 사용하기 위해서는 반드시 Initialize를 호출해야 합니다.
	 */
	Player() = default;


	/**
	 * 테트리스 게임 플레이어 클래스의 가상 소멸자입니다.
	 */
	virtual ~Player();


	/**
	 * 복사 생성자를 사용할 수 없도록 명시적으로 삭제합니다.
	 */
	Player(Player&& InInstance) = delete;
	Player(const Player& InInstance) = delete;


	/**
	 * 대입 연산자를 사용할 수 없도록 명시적으로 삭제합니다.
	 */
	Player& operator=(Player&& InInstance) = delete;
	Player& operator=(const Player& InInstance) = delete;


	/**
	 * 테트리스 게임 플레이어를 초기화합니다.
	 */
	void Initialize();


	/**
	 * 테트리스 게임의 플레이어를 업데이트합니다.
	 * 
	 * @param InInput - 전체 입력 처리를 관리하는 인스턴스입니다.
	 */
	void Update(const Game::Input& InInput);


	/**
	 * 테트리스 게임의 플레이어를 화면에 그립니다.
	 * 
	 * @param InGraphics - 전체 렌더링 처리를 관리하는 인스턴스입니다.
	 */
	void Draw(const Game::Graphics& InGraphics);


private:
	/**
	 * 플레이어의 레벨입니다.
	 */
	int32_t Level = 1;
};
