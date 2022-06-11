#pragma once

// 표준 라이브러리 및 SDL2를 사용하기 위한 헤더 선언을 추가합니다.
#include "GameEngine.h"


// 테트리스 블록의 색상 타입입니다.
enum class EBlockColor : int32_t
{
	BLUE   = 0,
	CYAN   = 1,
	GRAY   = 2,
	GREEN  = 3,
	ORANGE = 4,
	PINK   = 5,
	PURPLE = 6,
	RED    = 7,
	YELLOW = 8
};


// 테트리스 블럭의 상태입니다.
enum class EBlockState : int32_t
{
	FIX   = 0,
	FILL  = 1,
	EMPTY = 2
};


// 블럭 데이터 타입을 정의합니다.
using Block = std::pair<EBlockState, EBlockColor>;