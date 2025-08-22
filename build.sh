#!/bin/bash
set -e
# set -x

readonly current_script_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
readonly install_dir="$(pwd)/output"

clean() {
        rm -rf $install_dir
}

build() {
        # bazel build main
        # bazel build common
        bazel build //src:node
}

test() {
        bazel test --test_output=all //src/common/math:vec2d_test
        bazel test --test_output=all //test/...
}

install() {
        bazel run install -- $install_dir
}

refresh() {
    if [ $(command -v bazel-compile-commands) ]; then
        bazel-compile-commands //src/... //proto/... --output $current_script_dir/compile_commands.json
    else
        printf $(
            tput setaf 3
            tput bold
        )'bazel-compile-commands not found, please install it first, download it from https://github.com/kiron1/bazel-compile-commands/releases/tag/v0.17.2 \n'$(tput sgr0)
    fi
}

format_bazel() {
        [ $(command -v buildifier-linux-amd64) ] || {
                printf $(
                        tput setaf 3
                        tput bold
                )'buildifier-linux-amd64 not found, please install it first\n'$(tput sgr0)
                return
        }
        find src -type f \( \
                -name "BUILD" \
                -o -name "*.bzl" \
                -o -name "WORKSPACE" \
                -o -name "BUILD.bazel" \
                -o -name "*.BUILD" \
                \) -exec "buildifier-linux-amd64" {} \;
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
        # test
        install
        refresh
        format_bazel
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