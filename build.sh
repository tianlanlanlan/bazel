#!/bin/bash
set -e
# set -x

readonly current_script_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
readonly install_dir="$(pwd)/output"

clean() {
    rm -rf $install_dir
}

build() {
    bazel build $build_config main
    bazel build $build_config common_math
}

test() {
    bazel test $build_config --test_output=all //src/common/math:vec2d_test
    bazel test $build_config --test_output=all //test/...
}

install() {
    bazel run $build_config install -- $install_dir
}

refresh() {
    bazel run refresh_compile_commands || printf $(
        tput setaf 1
        tput bold
    )'Refresh compile commands failed\n'$(tput sgr0)
}

cmake_build() {
    rm -rf $current_script_dir/output $current_script_dir/build
    cmake -S $current_script_dir/cmake -B $current_script_dir/build \
        -G Ninja \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_CXX_FLAGS=-fdiagnostics-color=always \
        -DCMAKE_INSTALL_PREFIX=output \
        -DCMAKE_TOOLCHAIN_FILE=rpi3-toolchain.cmake
    # -DENABLE_ASAN=ON
    ninja -C build -j 8
    ninja -C build install
}

bazel_build() {
    clean
    build
    test
    install
    refresh
    # bazel shutdown
}

case $1 in
clean)
    clean
    bazel clean --expunge
    ;;
rpi)
    build_config=(
        --platforms=//:rpi
        # --config asan
    )
    bazel_build
    ;;
x86)
    build_config=(
        # --config asan
    )
    bazel_build
    ;;
*)
    build_config=(
        # --config asan
    )
    bazel_build
    ;;
esac

printf $(
    tput setaf 2
    tput bold
)'Build success!\n'$(tput sgr0)
