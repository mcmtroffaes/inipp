#include "test.h"

using namespace inipp;

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "usage: runtest <ini-file> <expected-output-file>" << std::endl;
		return -1;
	}
	ini_reader ini;
	auto actual = test(argv[1], ini);
	auto expected = read_all<char>(argv[2]);
	std::cout << actual;
	return (actual == expected)?0:-1;
}
