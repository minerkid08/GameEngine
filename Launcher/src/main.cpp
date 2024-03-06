#include <iostream>
#include <windows.h>
#include <fstream>
#include <json/json.hpp>

HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void cls(){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD topLeft = { 0, 0 };
	std::cout.flush();
	if(!GetConsoleScreenBufferInfo(consoleHandle, &csbi)){
		abort();
	}
	DWORD length = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD written;
	FillConsoleOutputCharacter(consoleHandle, TEXT(' '), length, topLeft, &written);
	FillConsoleOutputAttribute(consoleHandle, csbi.wAttributes, length, topLeft, &written);
	SetConsoleCursorPosition(consoleHandle, topLeft);
}

void gotoxy(short x, short y) { 
    COORD pos = {x, y};
    SetConsoleCursorPosition(consoleHandle, pos);
}

int main(int argc, const char** argv){
	std::ifstream fstream("settings.json");
	std::stringstream ss;
	ss << fstream.rdbuf();
	nlohmann::json j = nlohmann::json::parse(ss);
	std::string path;
	cls();
	std::cout << "projects\n new\n";
	int projectCount = 0;
	for(nlohmann::json p : j["projects"]){
		std::cout << " " << p << "\n";
		projectCount++;
	}
	gotoxy(0, 2);
	std::cout << ">";
	
	bool upDown = false;
	bool downDown = false;

	int i = 0;

	while(GetKeyState(VK_RETURN) & 0x8000);

	bool running = true;

	while(running){
		bool down = GetKeyState(VK_DOWN) & 0x8000;
		if(!downDown && down){
			downDown = true;
			if(i < projectCount - 1){
				gotoxy(0, i + 2);
				std::cout << " ";
				i++;
				gotoxy(0, i + 2);
				std::cout << ">";
			}
		}else if(!down){
			downDown = false;
		}

		bool up = GetKeyState(VK_UP) & 0x8000;
		if(!upDown && up){
			upDown = true;
			if(i >= 0){
				gotoxy(0, i + 2);
				std::cout << " ";
				i--;
				gotoxy(0, i + 2);
				std::cout << ">";
			}
		}else if(!up){
			upDown = false;
		}
		if(GetKeyState(VK_RETURN) & 0x8000){
			running = false;
			break;
		}
	}
	std::string path2 = j["editorPath"];
	if(i == -1){
		std::cout << "     ";
		gotoxy(1, 1);
		std::cin >> path;
		j["projects"][projectCount] = path;
		std::ofstream ofstream("settings.json");
		ofstream << j.dump(4);
		std::filesystem::create_directories(path);
		std::filesystem::create_directory(path + "/scenes");
		std::filesystem::create_directory(path + "/scripts");
		std::filesystem::create_directory(path + "/assets");
		std::filesystem::create_directory(path + "/scripts/.vscode");
		std::ofstream mainStream(path + "/scripts/main.code-workspace");
		mainStream << R"({
			"folders": [
				{
					"path": "."
				}
			]
		})";
		std::ofstream stream(path + "/scripts/.vscode/settings.json");
		stream << R"({
			"editor.tabSize": 4,
			"editor.insertSpaces\": false,
			"editor.detectIndentation\": false,
			"Lua.workspace.library": [)" << path2 << R"(\\luaDef\"]";
		})";
	}else{
		path = j["projects"][i];
	}
	cls();
	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CreateProcess((path2 + "/bin/editor.exe").c_str(),
		(char*)("editor.exe " + path).c_str(),
		NULL, NULL, FALSE, 0, NULL, (char*)path2.c_str(), &si, &pi
	); 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
	return 0;
}