#include "Log.h"

namespace Engine{
	std::function<void(const std::string&, int)> Log::callback = [](const std::string& str, int i){
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