#!/bin/bash
cmake ./ -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_BUILD_TYPE=Release
cmake --build . --clean-first

# Rename file
mv "gmsv_gmserial_linux64.dll" "gmcl_gmserial_linux64.dll"

# Cleanup all the crap
find . -name CMakeCache.txt -delete 
rm -r CMakeFiles
rm *.cmake
rm Makefile
echo "Finished"
