cmake_minimum_required(VERSION 2.6)
project(inipp)
include_directories("inipp/")
add_executable(unittest test/unittest-cmake.cpp)
install(FILES inipp/inipp.h DESTINATION include)

enable_testing()
add_test(test1 unittest test/test1.ini test/test1.output)
add_test(test2 unittest test/test2.ini test/test2.output)
