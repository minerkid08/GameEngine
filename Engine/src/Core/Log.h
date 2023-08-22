#pragma once
#include <windows.h>
#include <iostream>
namespace Engine{
	class Log{
		public:
		static void Info(std::string str){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			std::cout << str << std::endl;	
		}
		static void Warn(std::string str){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			std::cout << str << std::endl;	
		}
		static void Error(std::string str){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			std::cout << str << std::endl;	
		}
	};
}
