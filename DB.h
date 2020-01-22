
namespace DB {

	HANDLE hStdin, outHandle;
	DWORD fdwOldMode; SHORT consoleHeight, consoleWidth;
	CONSOLE_SCREEN_BUFFER_INFO	csbi;
	CONSOLE_CURSOR_INFO			cursorInfo;
	HWND window; LONG initWinLong;


	char* header_rawStr = (char*)">> WinEdit\n--------------------------\n";
	char* line_rawStr = (char*)"\n--------------------------";
	char* wannaSave_rawStr = (char*)">> Wanna save? ";
	char* fileName_rawStr  = (char*)">> File Name:  ";

	namespace ErrType {
		char* unknownEventType = (char*)"Unknown event type";
		char* ReadConsoleInput = (char*)"ReadConsoleInput";
		char* SetConsoleMode   = (char*)"SetConsoleMode";
		char* GetConsoleMode   = (char*)"GetConsoleMode";
		char* GetStdHandle     = (char*)"GetStdHandle";
		char* GetColor		   = (char*)"Unable to retrieve the initial console color";
	}

	WORD consoleColor;

	// IMP DATA
	std::string output = ""; UINT outputHeight = 1;
	UINT place = 0, s = 0, e = 0, maxHeight, maxWidth, lastY;
	USHORT cursorY = 1;

	// FILE
	std::string fileName = ""; bool fileExists = false;

	// Attr

	// FUNC
	void Init() {
		hStdin    = GetStdHandle(STD_INPUT_HANDLE);
		outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	}
}

