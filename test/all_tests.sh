#!/bin/bash

# Unit tests
echo ""
echo "======================================================"
echo "     UNIT TESTS"
echo "======================================================"
echo ""
./build/test/unit_tests/key-manager_unit_tests

# Memory tests
echo ""
echo "======================================================"
echo "     MEMORY TESTS"
echo "======================================================"
echo ""
./test/profiling.sh memcheck ./build/src/key-manager

# Threading tests
echo ""
echo "======================================================"
echo "     THREADING TESTS"
echo "======================================================"
echo ""
./test/profiling.sh helgrind ./build/src/key-manager
