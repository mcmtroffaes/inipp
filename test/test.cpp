#include "..\inipp\inipp.h"
#include <sstream>

#define TEST_EQUAL(x, y) if ((x) != (y)) std::wcout << "test error: " << x << "!=" << y << std::endl;

using namespace inipp;

static auto winput1 = LR"(
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
	std::wistringstream is(winput1);
	wini_reader ini;
	ini.parse(is);
	ini.generate(std::wcout);
	TEST_EQUAL(ini.errors.size(), 0)
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

int main() {
	Test1();
	system("pause");
	return 0;
}
