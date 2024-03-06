#include "Log.h"
#include "Args.h"

int Args::argc = 1;
const char** Args::argv = nullptr;

namespace Engine{
	std::function<void(const char*, int)> Log::callback = [](const char* str, int i){
		switch(i){
			case 1:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				break;
			case 2:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				break;
			case 3:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				break;
		}
		std::cout << str << std::endl;
	};
}