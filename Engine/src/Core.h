#pragma once
#include <memory>

#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

#ifndef UseAPI
	#define API __declspec(dllexport)
#else
	#define API __declspec(dllimport)
#endif
#define IMGUI_API API

#define BindFn(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Engine{
	template<typename T>
	using uniqPtr = std::unique_ptr<T>;
	template<typename T>
	using shdPtr = std::shared_ptr<T>;
}