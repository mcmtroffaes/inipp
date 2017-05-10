#include "test.h"

using namespace inipp;

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::wcout << "usage: runtest_w <ini-file> <expected-output-file>" << std::endl;
		return -1;
	}
	wini_reader ini;
	auto actual = test(argv[1], ini);
	auto expected = read_all<wchar_t>(argv[2]);
	std::wcout << actual;
	return (actual == expected)?0:-1;
}
