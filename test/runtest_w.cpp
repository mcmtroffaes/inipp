#include "inipp.h"

#include <fstream>
#include <sstream>

using namespace inipp;

std::wstring read_all(char *filename) {
	std::wifstream is(filename);
	std::wstringstream sstr;
	sstr << is.rdbuf();
	return sstr.str();
}

wini_reader parse(char *filename) {
	wini_reader ini;
	std::wifstream is(filename);
	ini.parse(is);
	return ini;
}

void errors(std::wostream & os, const wini_reader & ini) {
	for (auto err = ini.errors.cbegin(); err != ini.errors.cend(); err++) {
		os << *err << std::endl;
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::wcout << "usage: runtest_w <ini-file> <expected-output-file>" << std::endl;
		return -1;
	}
	std::wostringstream os;
	wini_reader ini = parse(argv[1]);
	os << ">>> ERRORS <<<" << std::endl;
	errors(os, ini);
	os << ">>> GENERATE <<<" << std::endl;
	ini.generate(os);
	os << ">>> INTERPOLATE <<<" << std::endl;
	ini.interpolate();
	ini.generate(os);
	std::wcout << os.str();
	return (os.str() == read_all(argv[2]))?0:-1;
}
