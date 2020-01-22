
namespace Event {

	VOID ErrorExit(LPSTR lpszMessage) {
		fprintf(stderr, "%s\n", lpszMessage);

		SetConsoleMode(DB::hStdin, DB::fdwOldMode); ExitProcess(0);
	}

	void End() {
		char ans[64];
		SetConsoleCursorInfo(DB::outHandle, &DB::cursorInfo);
		SetConsoleMode(DB::hStdin, DB::fdwOldMode);
		SetWindowLong(DB::window, GWL_STYLE, DB::initWinLong);
		SetConsoleScreenBufferSize(DB::outHandle, { DB::consoleWidth, 10000 });
		OP::CLS();
		// Wanna Save?
		SetConsoleTextAttribute(DB::outHandle, 3);
		std::cout << DB::wannaSave_rawStr; SetConsoleTextAttribute(DB::outHandle, DB::consoleColor);
		scanf("%s", ans);
		if (ans[0] == 'Y' || ans[0] == 'y') {
			// File Name
			if (!DB::fileName.size()) {
				SetConsoleTextAttribute(DB::outHandle, 2);
				std::cout << DB::fileName_rawStr; SetConsoleTextAttribute(DB::outHandle, DB::consoleColor);
				std::cin >> DB::fileName;
			}
			//Save
			IO::SAVE();
		}
		ExitProcess(0);
	}

	CHAR c; /*WORD preKey = 0; char cc = -1;*/
	VOID KeyEventProc(KEY_EVENT_RECORD ker) {
		// *** Uncomment these lines to get better performance but slower editor
		// ***
		//if (!ker.bKeyDown) { cc = -2; }
		//if (ker.wVirtualKeyCode == preKey) {
		//	cc++;
		//	if (cc == 1) {
		//		cc = -1;
		//		return;
		//	}
		//}
		//preKey = ker.wVirtualKeyCode;
		if (ker.bKeyDown)
		{
			if (ker.wVirtualKeyCode == 'C' && GetKeyState(VK_CONTROL) & 0x8000) { Event::End(); }
			// Process
			// Keyboard Input
			if (c = Key::Convert(ker.wVirtualKeyCode)) {
				if (c != 1) {
					OP::INSERT_Single(c);
				}
				OP::PRINT();
			}
		}
	}

}
