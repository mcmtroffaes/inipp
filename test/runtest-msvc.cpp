#include "test.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittest
{		
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod)
		{
			Assert::IsTrue(runtest<char>("test1.ini", "test1.output", std::cout));
			Assert::IsTrue(runtest<wchar_t>("test1.ini", "test1.output", std::wcout));
			Assert::IsTrue(runtest<char>("test2.ini", "test2.output", std::cout));
			Assert::IsTrue(runtest<wchar_t>("test2.ini", "test2.output", std::wcout));
		}

	};
}