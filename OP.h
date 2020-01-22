
namespace OP {

	void CLS() {
		static COORD topLeft = { 0, 2 };
		static CONSOLE_SCREEN_BUFFER_INFO screen; static DWORD written;

		GetConsoleScreenBufferInfo(DB::outHandle, &screen);
		FillConsoleOutputCharacterA(
			DB::outHandle, ' ', screen.dwSize.X * DB::consoleHeight, topLeft, &written
		);
		FillConsoleOutputAttribute(
			DB::outHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			screen.dwSize.X * DB::consoleHeight, topLeft, &written
		);
		SetConsoleCursorPosition(DB::outHandle, topLeft);
	}

	bool GetColor(WORD& col) {
		if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &DB::csbi)) return false;
		col = DB::csbi.wAttributes; return true;
	}
	//------------------------------------------------------------
	const char* s1; const char* s2; char c, c1;
	void PRINT() {
		SetConsoleCursorPosition(DB::outHandle, {0, 0});
		std::cout << "E: " << DB::s << ", " << DB::e << ", " << DB::place << " | " << DB::maxHeight << ", " << DB::output.size();
		Debug::Log("h: " + std::to_string(DB::outputHeight), 80);
		CLS();
		s1 = DB::output.c_str() + DB::s;
		s2 = DB::output.c_str() + DB::place;

		c1 = DB::output[DB::e]; DB::output[DB::e] = 0;
		c = DB::output[DB::place]; DB::output[DB::place] = 0;

		//PRINT ONE
		std::cout << s1;

		//PRINT POINTER *
		SetConsoleTextAttribute(DB::outHandle, 19); std::cout << ' ';

		//PRINT TWO
		SetConsoleTextAttribute(DB::outHandle, DB::consoleColor);
		if (DB::place >= DB::e) {
			std::cout << DB::line_rawStr;
			goto Final;
		}
		DB::output[DB::place] = c;
		std::cout << s2 << DB::line_rawStr;

		// FINAL
	Final:
		DB::output[DB::e] = c1;
		//DB::s++;
	}

	void InitialPrint() {
		system("cls"); std::cout << DB::header_rawStr; PRINT();
	}

	//------------------------------------------------------------

	void INSERT_Single_InPlace(char c) {
		DB::output.insert(DB::place, 1, c);
	}

	void INSERT_Single(char c) {
		bool b = false;
		if (DB::place > DB::e) { return; }
		DB::output.insert(DB::place, 1, c);
		if (DB::outputHeight < DB::maxHeight-1 || c != '\n' || DB::place < DB::e) { DB::place++; b=true; }
		if (c == '{' || c == '[') { INSERT_Single_InPlace(c+2); }
		if (c == '(') { INSERT_Single_InPlace(c + 1); }
		//CallBack
		if (!b) CallBack::Insert(DB::output[DB::place]);
		else    CallBack::Insert(DB::output[DB::place - 1]);
	}

	void INSERT_Multiple(char c, UINT count) {
		while (count--) {
			INSERT_Single(c);
		}
	}

	void ERASE_Single() {
		if (DB::place == 0 || DB::place > DB::e) return;
		CallBack::Delete(DB::output[DB::place - 1]);
		DB::output.erase(--DB::place, 1);
	}

	void ERASE_InPlace() {
		CallBack::Delete(DB::output[DB::place]);
		DB::output.erase(DB::place, 1);
	}

	//------------------------------------------------------------

	// UP & DOWN
	void Key_Up() {
		if (DB::place > DB::s && DB::output[DB::place - 1] == '\n') {
			DB::place--; return;
		}
		for (; DB::place > DB::s && DB::output[DB::place - 1] != '\n'; DB::place--) { }
		if (DB::place > DB::s && DB::output[DB::place - 1] == '\n') {
			DB::place--; return;
		}
	}
	void Key_Down() {
		if (DB::place < DB::e && DB::output[DB::place] == '\n') {
			DB::place++;
			for (; DB::place < DB::e && DB::output[DB::place] != '\n'; DB::place++) {}
			return;
		}
		for (; DB::place < DB::e && DB::output[DB::place] != '\n'; DB::place++) {}
		// REDO
		if (DB::place < DB::e) {
			DB::place++;
		}
		for (; DB::place < DB::e && DB::output[DB::place] != '\n'; DB::place++) {}
	}

	// RIGHT & LEFT------------------------------------------
	bool isCKey(int place) {
		if (DB::output[place] == ' ' || DB::output[place] == '\t'||
			DB::output[place] == '\n'|| DB::output[place] == '|' ||
			DB::output[place] == '(' || DB::output[place] == ')' ||
			DB::output[place] == '<' || DB::output[place] == '>' ||
			DB::output[place] == '/' || DB::output[place] == '\\'||
			DB::output[place] == '\"'|| DB::output[place] == '\''||
			DB::output[place] == ';' || DB::output[place] == ':' ||
			DB::output[place] == '#' || DB::output[place] == '@'
			)
			return true;
		return false;
	}

	void Key_CLeft() {
		if (DB::place > DB::s && isCKey(DB::place-1)) { DB::place--; return; }
		for (; DB::place > DB::s && !isCKey(DB::place-1); DB::place--) {}
	}
	void Key_CRight() {
		if (isCKey(DB::place) && DB::place < DB::e) { DB::place++; return; }
		for (; DB::place < DB::e && !isCKey(DB::place); DB::place++) {}
	}
	void Key_Right() {
		if (DB::place < DB::e) DB::place++;
	}
	void Key_Left() {
		if (DB::place > DB::s) DB::place--;
	}

	// C-Delete----------------------------------------------
	unsigned int counter;
	void Key_CDelete() {
		if (!DB::place) return; counter = 0;
		if (DB::output[--DB::place] == ' ' || DB::output[DB::place] == '\t' || DB::output[DB::place] == '\n') {
			ERASE_InPlace(); return;
		}
		DB::place++;
		while (--DB::place != 0 && DB::output[DB::place] != ' ' && DB::output[DB::place] != '\t'
			&& DB::output[DB::place] != '\n')
		{
			counter++;
			CallBack::Delete(DB::output[DB::place]);
		}
		if (DB::place) { DB::place++; }
		else { counter++; CallBack::Delete(DB::output[DB::place]); }
		DB::output.erase(DB::place, counter);
	}

	// Scroll
	void S_Down() {

	}

}

