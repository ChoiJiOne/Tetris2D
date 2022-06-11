#pragma once

// 컴파일러 경고를 무시합니다.
#pragma warning(disable: 26812)
#pragma warning(disable: 26451)
#pragma warning(disable: 4819)


// 프로젝트 내에서 공통으로 사용할 표준 헤더을 추가합니다.
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <cstdio>
#include <locale>
#include <codecvt>
#include <sstream>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <queue>
#include <chrono>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>


// SDL 헤더 파일을 추가합니다.
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>


 // Windows Platform 인 경우 아래의 블록을 수행합니다.
#if (defined(_WIN32)) || (defined(WIN32)) || (defined(_WIN64)) || (defined(WIN64))
// Windows.h 헤더 선언 추가
#include <Windows.h>


// Visual Compiler 메모리 누수 체크 라이브러리 추가
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


// Windows 에서 덤프 파일 생성을 위한 헤더 파일 추가
#include <Dbghelp.h>


// Windows.h 내에 정의된 매크로 함수 삭제
#undef CreateWindow
#undef min
#undef max
#undef SetConsoleTitle
#undef DrawText
#endif