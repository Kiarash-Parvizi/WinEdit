
namespace RAttr {
	VOID getWindowProps(); VOID setRenderAttr();

	// INIT Func
	VOID Set() {
		getWindowProps();
		setRenderAttr();
	}
	//--------

	VOID getWindowProps() {
		// Set maxHeight & maxWidth
		GetConsoleScreenBufferInfo(DB::outHandle, &DB::csbi);
		DB::consoleHeight = DB::csbi.srWindow.Bottom - DB::csbi.srWindow.Top + 1;
		DB::consoleWidth  = DB::csbi.srWindow.Right - DB::csbi.srWindow.Left + 1;
		DB::maxHeight = DB::consoleHeight - 3;
		DB::maxWidth  = DB::consoleWidth;
		DB::lastY = DB::maxHeight-1;
		SetConsoleScreenBufferSize(DB::outHandle, {DB::consoleWidth, DB::consoleHeight});
	}

	VOID setRenderAttr() {
		if (!DB::output.size()) { return; }
		UINT counter = 1, i = DB::s, lineSize = 0;
		for (; i < DB::output.size() && counter < DB::maxHeight; i++) {
			if (DB::output[i] == '\n') { lineSize = 0; counter++; }
			else {
				lineSize++;
				if (lineSize > DB::maxWidth) { counter++; lineSize = 0; }
			}
		}
		DB::outputHeight = counter;
		if (i != DB::output.size()) {
			DB::e = i - 1; lineSize = 0;
			for (; i < DB::output.size(); i++) {
				if (DB::output[i] == '\n') { lineSize = 0; DB::outputHeight++; }
				else {
					lineSize++;
					if (lineSize > DB::maxWidth) { DB::outputHeight++; lineSize = 0; }
				}
			}
		}
		else {
			DB::e = i;
		}
	}

	//--------------------------------------------------



}
