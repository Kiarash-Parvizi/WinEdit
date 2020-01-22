
namespace Side {

	UINT GET_LastLineTabCount() {
		INT i = DB::place - 2, count = 0; if (i < 0) { return 0; }
		for (; i > 0 && DB::output[i] != '\n'; i--) {} i++;
		//--2
		for (; DB::output[i] == '\t'; i++) { count++; }
		return count;
	}


	bool valid_ascii(WCHAR u) {
		return (u < 127 && u > 30) || u == '\n';
	}
}
