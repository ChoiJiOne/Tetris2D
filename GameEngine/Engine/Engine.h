#pragma once

namespace Game
{
	/**
	 * 게임 엔진 클래스입니다.
	 */
	class Engine
	{
	public:
		/**
		 * 게임 엔진 클래스 생성자입니다.
		 * 
		 * @note 게임 엔진 클래스에서 제공하는 기능들을 사용하기 위해서는 반드시 Setup 메서드를 호출해야 합니다.
		 */
		Engine() = default;


		/**
		 * 게임 엔진 클래스 가상 소멸자입니다.
		 * 
		 * @note 게임 엔진 클래스를 상속받는 클래스의 소멸자 또한 virtual 키워드를 추가해야 합니다.
		 * 
		 * @see https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
		 */
		virtual ~Engine();


		/**
		 * 게임 엔진을 초기화합니다.
		 * 
		 * @warning 이 메서드는 반드시 상속받은 클래스의 초기화를 수행하기 전에 호출되어야 합니다.
		 */
		virtual void Initialize();


		/**
		 * 게임 입력 처리를 수행합니다.
		 * 
		 * @note 이 메서드는 반드시 상속 받은 클래스에서 정의하고 구현해야 합니다.
		 */
		virtual void Input() = 0;


		/**
		 * 게임 루프를 업데이트 합니다.
		 * 
		 * @note 이 메서드는 반드시 상속 받은 클래스에서 정의하고 구현해야 합니다.
		 */
		virtual void Update() = 0;


		/**
		 * 전체 게임을 렌더링합니다.
		 * 
		 * @note 이 메서드는 반드시 상속 받은 클래스에서 정의하고 구현해야 합니다.
		 */
		virtual void Render() = 0;


		/**
		 * 게임 루프를 실행합니다.
		 * 
		 * @note 이 메서드는 반드시 상속 받은 클래스에서 정의하고 구현해야 합니다.
		 */
		virtual void Run() = 0;
	};
}