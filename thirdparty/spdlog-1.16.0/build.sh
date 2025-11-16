#!/bin/bash
set -ex

rm -rf output build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$(pwd)/output
cmake --build build --config Release --target install -- -j$(nproc)
