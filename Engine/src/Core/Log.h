#pragma once
#include <functional>
#include <windows.h>
#include <iostream>
#include "Core.h"
namespace Engine{
	class API Log{
		public:
		static std::function<void(const char*, int)> callback;
		static void Info(const char* str){
			callback(str, 1);
		}
		static void Warn(const char* str){
			callback(str,2);
		}
		static void Error(const char* str){
			callback(str,3);
		}
		static void Info(const std::string& str){
			callback(str.c_str(), 1);
		}
		static void Warn(const std::string& str){
			callback(str.c_str(),2);
		}
		static void Error(const std::string& str){
			callback(str.c_str(),3);
		}
	};
}
