cmake_minimum_required(VERSION 2.6)
project(inipp)
include_directories("inipp/")
add_executable(runtest test/runtest.cpp)
install(FILES inipp/inipp.h DESTINATION include)

enable_testing()
add_test(test1 runtest test/test1.ini test/test1.output)
add_test(test2 runtest test/test2.ini test/test2.output)
