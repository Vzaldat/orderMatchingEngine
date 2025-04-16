#!/bin/bash
set -e

mkdir build 
cd build

cmake ..

cmake --build .

# make 

./OrderMatchingEngine > latencyOut.text

# ./tests > test_output.txt

gprof ./OrderMatchingEngine gmon.out > profile_report.txt
# less profile_report.txt