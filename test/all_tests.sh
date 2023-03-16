#!/bin/bash

# Unit tests
#echo "======================================================"
#echo "     UNIT TESTS"
#echo "======================================================"
#echo ""
# Empty for the moment...

# Memory tests
echo ""
echo "======================================================"
echo "     MEMORY TESTS"
echo "======================================================"
echo ""
./test/profiling.sh memcheck ./build/src/snake-game

# Threading tests
echo ""
echo "======================================================"
echo "     THREADING TESTS"
echo "======================================================"
echo ""
./test/profiling.sh helgrind ./build/src/snake-game
