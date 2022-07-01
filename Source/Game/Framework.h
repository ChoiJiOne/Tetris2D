#pragma once

// 표준 라이브러리와 SDL2를 사용하기 위해서 헤더 파일을 추가합니다.
#include "Header.h"


namespace Game
{
	// 게임 프레임워크 클래스입니다.
	// 게임을 만들고 싶은 경우, 이 클래스를 상속받으면 됩니다.
	class Framework
	{
	public:
		// 생성자입니다.
		Framework() = default;


		// 가상 소멸자입니다.
		virtual ~Framework();


		// 복사 생성자를 사용할 수 없도록 명시적으로 삭제합니다. 
		Framework(Framework&& InInstance) = delete;
		Framework(const Framework& InInstance) = delete;


		// 대입 연산자를 사용할 수 없도록 명시적으로 삭제합니다.
		Framework& operator=(Framework&& InInstance) = delete;
		Framework& operator=(const Framework& InInstance) = delete;


		// 게임 프레임워크를 초기화합니다.
		virtual void Setup();


		// 게임 루프를 실행합니다.
		virtual void Run() = 0;


		// 게임 루프를 업데이트합니다.
		virtual void Update() = 0;


		// 게임을 화면에 그립니다.
		virtual void Draw() = 0;
	};
}