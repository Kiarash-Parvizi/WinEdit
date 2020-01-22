
namespace State {
	void Init() {
		DB::Init(); RAttr::Set();
		//Disable Cursor:
		GetConsoleCursorInfo(DB::outHandle, &DB::cursorInfo); DB::cursorInfo.bVisible = false;
		SetConsoleCursorInfo(DB::outHandle, &DB::cursorInfo); DB::cursorInfo.bVisible = true;
		//--------------
		//Disable Mouse Paste Events:
		GetConsoleCursorInfo(DB::outHandle, &DB::cursorInfo); DB::cursorInfo.bVisible = false;
		SetConsoleCursorInfo(DB::outHandle, &DB::cursorInfo); DB::cursorInfo.bVisible = true;
		//--------------
		Key::keyMap_Init(); DB::output.reserve(1e4);
		if (!OP::GetColor(DB::consoleColor)) { Event::ErrorExit(DB::ErrType::GetColor); }
		OP::InitialPrint();
		//
		if (DB::hStdin == INVALID_HANDLE_VALUE)				Event::ErrorExit(DB::ErrType::GetStdHandle);
		if (!GetConsoleMode(DB::hStdin, &DB::fdwOldMode))	Event::ErrorExit(DB::ErrType::GetConsoleMode);

		DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
		if (!SetConsoleMode(DB::hStdin, fdwMode))			Event::ErrorExit(DB::ErrType::SetConsoleMode);

		// Constant ConsoleWindow Size
		DB::window = GetConsoleWindow();
		DB::initWinLong = GetWindowLong(DB::window, GWL_STYLE);
		SetWindowLong(DB::window, GWL_STYLE, GetWindowLong(DB::window, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

		// Others
		SetConsoleTitle("WinEdit");
	}

	
	void Edit() {
		DWORD cNumRead, i; WORD tWord;
		INPUT_RECORD irInBuf[128];
		while (true)
		{
			// Wait for the events
			if (!ReadConsoleInput(
				DB::hStdin,      // input buffer handle 
				irInBuf,     // buffer to read into 
				128,         // size of read buffer 
				&cNumRead)) // number of records read 
				Event::ErrorExit(DB::ErrType::ReadConsoleInputA);

			for (i = 0; i < cNumRead; i++) {
				tWord = irInBuf[i].EventType;
				if (tWord == KEY_EVENT) {
					Event::KeyEventProc(irInBuf[i].Event.KeyEvent);
				}
				else if (tWord != MOUSE_EVENT && tWord != FOCUS_EVENT
					&& tWord != MENU_EVENT && tWord != WINDOW_BUFFER_SIZE_EVENT) { Event::ErrorExit(DB::ErrType::unknownEventType); }
			}
		}
	}

}

