#pragma once

#include "Math.h"


namespace Game
{
	/**
	 * 그래픽스 클래스입니다.
	 */
	class Graphics
	{
	public:
		/**
		 * 그래픽스 클래스 생성자입니다.
		 */
		Graphics() = default;


		/**
		 * 그래픽스 클래스의 가상 소멸자입니다.
		 */
		virtual ~Graphics();


		/**
		 * Graphics 클래스를 초기화합니다.
		 *
		 * @throws 초기화에 실패할 경우, C++ 표준 예외를 던집니다.
		 */
		void Initialize();


		/**
		 * 프레임 렌더링을 시작합니다.
		 *
		 * @param InColor - 벡버퍼를 비울 색상입니다.
		 *
		 * @throws 백버퍼 초기화에 실패할 경우, C++ 표준 예외를 던집니다.
		 */
		void BeginFrame(const LinearColor& InColor);


		/**
		 * 프레임 렌더링을 종료하고, 벡버퍼를 화면에 표시합니다.
		 */
		void EndFrame();
	};
}