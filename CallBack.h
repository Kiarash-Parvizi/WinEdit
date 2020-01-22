// Final CallBack
namespace OP { void INSERT_Multiple(char, UINT); }

namespace CallBack {
	//----------- Delete

	void Delete(char c) {
		Debug::Log("outH: " + std::to_string(DB::outputHeight), 60);
		switch (c)
		{
		case '\n':
			if (DB::outputHeight < DB::maxHeight) {
				DB::e--;
				//Debug::Log("FALSE", 60, 0);
			}
			else {
				if (DB::output[DB::e] == '\n') { DB::e++; }
				for (; DB::output[DB::e] != '\n' && DB::e < DB::output.size(); DB::e++) {} DB::e--;
			}
			DB::outputHeight--;
			break;
		default:
			DB::e--;
			break;
		}
	}

	
	//----------- Call After Insert
	UINT lastLineTabCount;

	void Insert(char c) {
		switch (c)
		{
		//case '\t':
		//	break;
		case '\n':
			lastLineTabCount = Side::GET_LastLineTabCount();
			OP::INSERT_Multiple('\t', lastLineTabCount);
			DB::outputHeight++;
			if (DB::outputHeight < DB::maxHeight) {
				DB::e += lastLineTabCount+1;
			}
			else {
				//DB::e--;
				int ccc = 0;

				for (; DB::output[DB::e] != '\n'; DB::e--) { ccc++; }
				//if (DB::place > DB::e) { DB::place = 0;/*DB::e;*/ }
				Debug::Log("ccc>>>" + std::to_string(ccc) + ", " + std::to_string(DB::output[DB::e]), 40);
			}
			break;
		default:
			DB::e++;
		}
	}

	//----------- I


}

