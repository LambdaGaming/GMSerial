#!/bin/bash
cmake ./ -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_BUILD_TYPE=Release
cmake --build . --clean-first

# Cleanup all the crap
find . -name CMakeCache.txt -delete 
rm -r CMakeFiles
rm *.cmake
rm Makefile
echo "Finished"
