#!/bin/bash -eu

mkdir build
cd build
cmake ../
make

# Copy all fuzzer executable to $OUT/
$CXX $CFLAGS $LIB_FUZZING_ENGINE \
  $SRC/inipp/.clusterfuzzlite/parse_fuzzer.cpp \
  -o $OUT/parse_fuzzer \
  -I$SRC/inipp/inipp