#!/bin/bash

# Compile the copy_files.cpp macro
cd scripts || exit
if [ -d "build" ]; then
    cmake --build build --target clean
fi
cmake -B build
cmake --build build

# Run the executable
cd ..
./scripts/build/copy-files