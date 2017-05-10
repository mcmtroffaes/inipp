cmake_minimum_required(VERSION 2.6)
project(inipp)
include_directories("inipp/")
add_executable(runtest test/runtest_w.cpp)
install(FILES inipp.h DESTINATION include)

include(CTest)
add_test(test1 runtest)
