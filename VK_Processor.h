#include<map>

namespace Key {

	std::map<WORD, char> keyMap; std::map<WORD, char>::iterator it;
	std::map<WORD, char> shiftMap;

	char Convert(WORD k) {
		//CTR Operations
		if (GetKeyState(VK_CONTROL) & 0x8000) {
			switch (k) {
			case 'D':

				break;
			}
		}
		//-----
		if (k >= VK_LEFT && k <= VK_DOWN) {
			if (k == VK_LEFT) {
				if (GetKeyState(VK_CONTROL) & 0x8000) OP::Key_CLeft();
				else OP::Key_Left();
			}
			else if (k == VK_RIGHT) {
				if (GetKeyState(VK_CONTROL) & 0x8000) OP::Key_CRight();
				else OP::Key_Right();
			}
			else if (k == VK_DOWN) {
				OP::Key_Down();
			}
			else if (k == VK_UP) {
				OP::Key_Up();
			}
			return 1;
		}
		if (k == VK_BACK) {
			if (GetKeyState(VK_CONTROL) & 0x8000) OP::Key_CDelete();
			else {
				OP::ERASE_Single();
			}
			return 1;
		}
		if (k == 32) {
			return k;
		}
		//------------------------
		//WORD
		if (k > 64 && k < 91) {
			if (GetKeyState(VK_SHIFT) & 0x8000) {
				return k;
			} else {
				return k + 32;
			}
		}
		//NUM
		if (k > 47 && k < 58) {
			if (GetKeyState(VK_SHIFT) & 0x8000) {
				return keyMap.find(k)->second;
			} else {
				return k;
			}
		}
		//---------
		if (GetKeyState(VK_SHIFT) & 0x8000) {
			it = shiftMap.find(k);
			if (it != shiftMap.end()) {
				return it->second;
			}
		}
		else {
			it = keyMap.find(k);
			if (it != keyMap.end()) {
				return it->second;
			}
		}
		return 0;
	}


	// Initialize KeyMap
	void keyMap_Init() {
		keyMap.insert({VK_RETURN, '\n'});
		keyMap.insert({VK_TAB, '\t'});
		keyMap.insert({'1', '!'});
		keyMap.insert({'2', '@'});
		keyMap.insert({'3', '#'});
		keyMap.insert({'4', '$'});
		keyMap.insert({'5', '%'});
		keyMap.insert({'6', '^'});
		keyMap.insert({'7', '&'});
		keyMap.insert({'8', '*'});
		keyMap.insert({'9', '('});
		keyMap.insert({'0', ')'});
		//-----------------------
		keyMap.insert({ 192, '`' });
		keyMap.insert({ 189, '-' });
		keyMap.insert({ 187, '=' });
		keyMap.insert({ 219, '[' });
		keyMap.insert({ 221, ']' });
		keyMap.insert({ 220, '\\' });
		keyMap.insert({ 186, ';' });
		keyMap.insert({ 222, '\'' });
		keyMap.insert({ 188, ',' });
		keyMap.insert({ 190, '.' });
		keyMap.insert({ 191, '/' });
		//Shift Map
		shiftMap.insert({192, '~'});
		shiftMap.insert({189, '_'});
		shiftMap.insert({187, '+'});
		shiftMap.insert({219, '{'});
		shiftMap.insert({221, '}'});
		shiftMap.insert({220, '|'});
		shiftMap.insert({186, ':'});
		shiftMap.insert({222, '"'});
		shiftMap.insert({188, '<'});
		shiftMap.insert({190, '>'});
		shiftMap.insert({191, '?'});
	}
}
