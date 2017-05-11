#include "test.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "usage: runtest <ini-file> <expected-output-file>" << std::endl;
		return -1;
	}
	auto result1 = runtest<char>(argv[1], argv[2], std::cout);
	auto result2 = runtest<wchar_t>(argv[1], argv[2], std::wcout);
	return (result1 && result2) ? 0 : -1;
}
