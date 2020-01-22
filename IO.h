
namespace IO {

	VOID LOAD() {
		std::ifstream reader = std::ifstream(DB::fileName.c_str());
		if (reader) {
			std::string data((std::istreambuf_iterator<char>(reader)), std::istreambuf_iterator<char>());
			DB::output = data; DB::fileExists = true;
		}
		reader.close();
	}

	VOID SAVE() {
		std::ofstream f(DB::fileName.c_str());
		f << DB::output; f.close();
	}

}

