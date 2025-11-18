#!/bin/bash
set -ex

rm -rf output build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DSPDLOG_BUILD_SHARED=ON -DCMAKE_INSTALL_PREFIX=$(pwd)/output
cmake --build build --target install -- -j$(nproc)
