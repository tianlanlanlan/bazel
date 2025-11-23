#!/bin/bash
set -ex

readonly current_script_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

cmake_build_x86() {
    local install_dir=$current_script_dir/output_x86
    rm -rf $install_dir build
    cmake -S $current_script_dir -B build -DCMAKE_BUILD_TYPE=Release -DSPDLOG_BUILD_SHARED=ON -DCMAKE_INSTALL_PREFIX=$install_dir
    cmake --build build --target install -- -j$(nproc)
}

cmake_build_riscv64() {
    local install_dir=$current_script_dir/output_riscv
    rm -rf $install_dir build
    export CC=/opt/riscv/bin/riscv64-unknown-linux-gnu-gcc
    export CXX=/opt/riscv/bin/riscv64-unknown-linux-gnu-g++
    cmake -S $current_script_dir -B build -DCMAKE_BUILD_TYPE=Release -DSPDLOG_BUILD_SHARED=ON -DCMAKE_INSTALL_PREFIX=$install_dir
    cmake --build build --target install -- -j$(nproc)
}

cmake_build_x86
cmake_build_riscv64
