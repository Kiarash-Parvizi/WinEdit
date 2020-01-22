/*
	WinEdit | Designed by the GameChanger : https://github.com/Kiarash-Parvizi
*/
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <iostream>
#include<string>
#include <fstream>
#include "DB.h"
namespace Debug {
	void Log(std::string s, SHORT w, SHORT h) {
		SetConsoleCursorPosition(DB::outHandle, { w, h }); std::cout << s;
	}
	void Log(std::string s, SHORT w) {
		SetConsoleCursorPosition(DB::outHandle, { w, 0 }); std::cout << s;
	}
	void Log(const char* s, SHORT w, SHORT h) {
		SetConsoleCursorPosition(DB::outHandle, { w, h }); std::cout << s;
	}
	void Log(const char* s, SHORT w) {
		SetConsoleCursorPosition(DB::outHandle, { w, 0 }); std::cout << s;
	}
}
#include "RenderAttr.h"
#include "Side.h"
#include "CallBack.h"
#include "OP.h"
#include "IO.h"
#include "VK_Processor.h"
#include "Event.h"
#include "State.h"


int main(int argc, char** argv) {
	// Process Args
	if (argc != 1) {
		DB::fileName = argv[1]; IO::LOAD();
	}

	// Call Init
	State::Init();

	// Call Edit
	State::Edit();

}

