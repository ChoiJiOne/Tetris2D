#include "Logger.h"

int main(int argc, char* argv[])
{
	Logger::Message("일반 메시지 출력");
	Logger::Warning("경고 메시지 출력");
	Logger::Error("에러 메시지 출력");

	return 0;
}