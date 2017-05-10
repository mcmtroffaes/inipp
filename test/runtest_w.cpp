#include "inipp.h"

#include <fstream>
#include <sstream>

#define TEST_EQUAL(x, y) if ((x) != (y)) std::wcout << "test error: " << x << "!=" << y << std::endl

using namespace inipp;

static auto input1 = LR"(
[section]
variable=value
)";

static auto input2 = LR"(
; comment
     ; comment

[section1]
var1=val1
var2 = val2
var3= val3
var4 =val4
     var5  =  val5     

   [section2]
x = %(test)
 y = %(var1)
z = %(x) + %(y) + %(a) + %(b)
b = monkey

     [DEFAULT]   
test = %(a) %(b)
a = hello
b = world
)";

void Test1() {
	std::wistringstream is(input1);
	wini_reader ini;
	ini.parse(is);
	ini.generate(std::wcout);
	TEST_EQUAL(ini.errors.size(), 0);
	TEST_EQUAL(ini.sections.at(L"section").at(L"variable"), L"value");
	ini.interpolate();
	ini.generate(std::wcout);
	TEST_EQUAL(ini.sections.at(L"section").at(L"variable"), L"value");
}

void Test2() {
	std::wistringstream is(input2);
	wini_reader ini;
	ini.parse(is);
	ini.generate(std::wcout);
	TEST_EQUAL(ini.errors.size(), 0);
	TEST_EQUAL(ini.sections.at(L"section1").at(L"var1"), L"val1");
	TEST_EQUAL(ini.sections.at(L"section1").at(L"var2"), L"val2");
	TEST_EQUAL(ini.sections.at(L"section1").at(L"var3"), L"val3");
	TEST_EQUAL(ini.sections.at(L"section1").at(L"var4"), L"val4");
	TEST_EQUAL(ini.sections.at(L"section1").at(L"var5"), L"val5");
	TEST_EQUAL(ini.sections.at(L"section2").at(L"x"), L"%(test)");
	TEST_EQUAL(ini.sections.at(L"section2").at(L"y"), L"%(var1)");
	TEST_EQUAL(ini.sections.at(L"section2").at(L"z"), L"%(x) + %(y) + %(a)");
	TEST_EQUAL(ini.sections.at(L"DEFAULT").at(L"test"), L"%(a) %(b)");
	TEST_EQUAL(ini.sections.at(L"DEFAULT").at(L"a"), L"hello");
	TEST_EQUAL(ini.sections.at(L"DEFAULT").at(L"b"), L"world");
	ini.interpolate();
	ini.generate(std::wcout);
	TEST_EQUAL(ini.sections.at(L"section1").at(L"var1"), L"val1");
	TEST_EQUAL(ini.sections.at(L"section1").at(L"var2"), L"val2");
	TEST_EQUAL(ini.sections.at(L"section1").at(L"var3"), L"val3");
	TEST_EQUAL(ini.sections.at(L"section1").at(L"var4"), L"val4");
	TEST_EQUAL(ini.sections.at(L"section1").at(L"var5"), L"val5");
	TEST_EQUAL(ini.sections.at(L"section2").at(L"x"), L"hello world");
	TEST_EQUAL(ini.sections.at(L"section2").at(L"y"), L"%(var1)");
	TEST_EQUAL(ini.sections.at(L"section2").at(L"z"), L"hello world + %(var1) + hello + monkey");
	TEST_EQUAL(ini.sections.at(L"DEFAULT").at(L"test"), L"hello world");
	TEST_EQUAL(ini.sections.at(L"DEFAULT").at(L"a"), L"hello");
	TEST_EQUAL(ini.sections.at(L"DEFAULT").at(L"b"), L"world");
}

void errors(const wini_reader & ini) {
	for (auto err = ini.errors.cbegin(); err != ini.errors.cend(); err++) {
		std::wcout << *err << std::endl;
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::wcout << "usage: runtest_w <filename>.ini" << std::endl;
		return -1;
	}
	std::wifstream is(argv[1]);
	wini_reader ini;
	ini.parse(is);
	std::wcout << ">>> ERRORS <<<" << std::endl;
	errors(ini);
	std::wcout << ">>> GENERATE <<<" << std::endl;
	ini.generate(std::wcout);
	std::wcout << ">>> INTERPOLATE <<<" << std::endl;
	ini.interpolate();
	ini.generate(std::wcout);
	return 0;
}
