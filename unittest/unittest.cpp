#include "test.h"

#ifdef _MSC_VER
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#else
#define TEST_CLASS(T) class T
#define TEST_METHOD(Func) void Func()
namespace Assert {

	void IsTrue(bool result) {
		if (!result) throw std::runtime_error("expected true");
	}

	void IsFalse(bool result) {
		if (result) throw std::runtime_error("expected false");
	}

	template <typename T>
	void AreEqual(const T & a, const T & b) {
		if (a != b) throw std::runtime_error("expected equality");
	}

} // namespace Assert
#endif

namespace unittest
{		
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestParseGenerate)
		{
			Assert::IsTrue(runtest<char>("test1.ini", "test1.output", std::cout));
			Assert::IsTrue(runtest<wchar_t>("test1.ini", "test1.output", std::wcout));
			Assert::IsTrue(runtest<char>("test2.ini", "test2.output", std::cout));
			Assert::IsTrue(runtest<wchar_t>("test2.ini", "test2.output", std::wcout));
		}

		TEST_METHOD(TestExtract)
		{
			std::string       str{ "oops" };
			int16_t           i16{ 0 };
			int32_t           i32{ 0 };
			bool              bool_{ true };
			Assert::IsTrue(extract(std::string(), str));
			Assert::AreEqual(std::string{ }, str);
			Assert::IsTrue(extract(std::string{ "hello" }, str));
			Assert::AreEqual(std::string{ "hello" }, str);
			Assert::IsTrue(extract(std::string{ "hello world" }, str));
			Assert::AreEqual(std::string{ "hello world" }, str);
			Assert::IsTrue(extract(std::string{ "-10" }, i16));
			Assert::AreEqual(int16_t{ -10 }, i16);
			Assert::IsTrue(extract(std::string{ "false" }, bool_));
			Assert::AreEqual(false, bool_);
			Assert::IsTrue(extract(std::string{ "-10" }, i16));
			Assert::AreEqual(int16_t{ -10 }, i16);
			Assert::IsFalse(extract(std::string{ "xxx" }, i16));
			Assert::AreEqual(int16_t{ -10 }, i16);
			Assert::IsFalse(extract(std::string{ "1000000" }, i16));
			Assert::AreEqual(int16_t{ -10 }, i16);
			Assert::IsFalse(extract(std::string{ "-20 xxx" }, i16));
			Assert::AreEqual(int16_t{ -10 }, i16);
			Assert::IsTrue(extract(std::string{ "1000000" }, i32));
			Assert::AreEqual(int32_t{ 1000000 }, i32);
		}
	};
} // namespace unittest

#ifndef _MSC_VER
int main() {
	unittest::UnitTest test;
	test.TestParseGenerate();
	test.TestExtract();
	return 0;
}
#endif
