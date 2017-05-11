cmake_minimum_required(VERSION 2.6)
project(inipp)
include_directories("inipp/")
add_executable(runtest unittest/unittest-cmake.cpp)
install(FILES inipp/inipp.h DESTINATION include)

enable_testing()
add_test(test1 runtest unittest/test1.ini unittest/test1.output)
add_test(test2 runtest unittest/test2.ini unittest/test2.output)
