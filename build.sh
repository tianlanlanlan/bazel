#!/bin/sh
set -e
# set -x

readonly install_dir="$(pwd)/output"

clean() {
    rm -rf $install_dir
}

build() {
    bazel build --config=asan main
    bazel build --config=asan common_math
}

test() {
    bazel test --cxxopt=-std=c++17 --test_output=all //src/common/math:vec2d_test
}

install() {
    bazel run --config=asan install -- $install_dir
}

refresh() {
    bazel run refresh_compile_commands >/dev/null 2>&1 || printf $(
        tput setaf 1
        tput bold
    )'Refresh compile commands failed\n'$(tput sgr0)
}

clean
build
test
install
refresh
# bazel shutdown

printf $(
    tput setaf 2
    tput bold
)'Build success!\n'$(tput sgr0)
