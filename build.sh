#!/bin/bash
set -e

mkdir build 
cd build

cmake ..

cmake --build .

make 

./OrderMatchingEngine

./tests > test_output.txt