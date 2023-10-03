#!/bin/bash

cmake_version=$(cmake --version | grep -oE '[0-9]+\.[0-9]+')
if [ "$(printf '%s\n' "3.20" "$cmake_version" | sort -V | head -n 1)" == "3.20" ]; then
    echo "cmake version is correct."
else
    wget https://cmake.org/files/v3.20/cmake-3.20.0.tar.gz
    tar -xzvf cmake-3.20.0.tar.gz
    cd cmake-3.20.0
    ./bootstrap -- -DCMAKE_BUILD_TYPE=Release
    make -j$(nproc)
    make install
    cmake --version
    cd ..
    rm -rf cmake-3.20.0.tar.gz* cmake-3.20.0
fi