#pragma once
#include <functional>
#include <windows.h>
#include <iostream>
#include "Core.h"
namespace Engine{
	class API Log{
		public:
		static std::function<void(const std::string&, int)> callback;
		static void Info(const std::string& str){
			callback(str, 1);
		}
		static void Warn(const std::string& str){
			callback(str,2);
		}
		static void Error(const std::string& str){
			callback(str,3);
		}
	};
}
