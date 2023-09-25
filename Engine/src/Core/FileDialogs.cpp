#include "FileDialogs.h"
#include "App.h"
#include <commdlg.h>
#include <glfw/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3native.h>
namespace Engine{
	// std::string FileDialogs::openFile(const char* filter){
	// 	OPENFILENAMEA fnName;
	// 	char szFile[260] = {0};
	// 	ZeroMemory(&fnName, sizeof(OPENFILENAME));
	// 	fnName.lStructSize = sizeof(OPENFILENAME);
	// 	fnName.hwndOwner = glfwGetWin32Window((GLFWwindow*)App::getInstance().getWindow().getWindow());
	// 	fnName.lpstrFile = szFile;
	// 	fnName.nMaxFile = sizeof(szFile);
	// 	fnName.lpstrFilter = filter;
	// 	fnName.nFilterIndex = 1;
	// 	fnName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	// 	if(GetOpenFileNameA(&fnName) == TRUE){
	// 		return fnName.lpstrFile;
	// 	}
	// 	return "";
	// }
	// std::string FileDialogs::openSaveFile(const char* filter){
	// 	OPENFILENAMEA fnName;
	// 	char szFile[260] = {0};
	// 	ZeroMemory(&fnName, sizeof(OPENFILENAME));
	// 	fnName.lStructSize = sizeof(OPENFILENAME);
	// 	fnName.hwndOwner = glfwGetWin32Window((GLFWwindow*)App::getInstance().getWindow().getWindow());
	// 	fnName.lpstrFile = szFile;
	// 	fnName.nMaxFile = sizeof(szFile);
	// 	fnName.lpstrFilter = filter;
	// 	fnName.nFilterIndex = 1;
	// 	fnName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	// 	if(GetSaveFileNameA(&fnName) == TRUE){
	// 		return fnName.lpstrFile;
	// 	}
	// 	return "";
	// }
}