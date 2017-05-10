#include "test.h"

using namespace inipp;

template <class CharT>
static inline auto runtest(char *inifile, char *expectedfile, std::basic_ostream<CharT> & os) {
	basic_ini_reader<CharT> ini;
	auto actual = test(inifile, ini);
	auto expected = read_all<CharT>(expectedfile);
	os << actual;
	return (actual == expected);
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "usage: runtest <ini-file> <expected-output-file>" << std::endl;
		return -1;
	}
	auto result1 = runtest<char>(argv[1], argv[2], std::cout);
	auto result2 = runtest<wchar_t>(argv[1], argv[2], std::wcout);
	return (result1 && result2) ? 0 : -1;
}
