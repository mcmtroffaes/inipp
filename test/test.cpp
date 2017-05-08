#include "..\inipp\inipp.h"

#include <fstream>

void Test1() {
	std::wifstream is(L"test.ini");
	wini_reader ini;
	ini.parse(is);
	auto val = ini.interpolate(ini.sections.at(L"section").at(L"variable"));
}

void Test2() {
	std::ifstream is("test.ini");
	ini_reader ini;
	ini.parse(is);
	auto val = ini.interpolate(ini.sections.at("section").at("variable"));
}

int main() {
	Test1();
	Test2();
}
