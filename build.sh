#!/bin/bash
set -e
# set -x

readonly current_script_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
readonly install_dir="$(pwd)/output"

function clean() {
  rm -rf $install_dir
}

function run() {
  (
    set -x
    $1
  )
}

function build() {
  local platform="$1"
  local build_cfg="--config=$platform"

  # Build main
  run "bazel build //src:main $build_cfg"

  # Build node
  run "bazel build //src:node $build_cfg"

  echo "=============================="
  # rm -rf *.params
  # cp bazel-out/k8-dbg/bin/src/libnode.so-2.params .
  # cp bazel-out/k8-dbg/bin/src/modules/planning/libplanning_module.lo-2.params .

  ls -lh bazel-bin/src/libnode.so
  [ $platform = "x86" ] && ldd bazel-bin/src/libnode.so
  # readelf -d bazel-bin/src/libnode.so | grep NEEDED
  echo "=============================="

  # Install
  rm -rf $install_dir
  run "bazel run install $build_cfg -- $install_dir"

  # Post build
  post_build
}

function test() {
  bazel test --test_output=all //src/common/math:vec2d_test
  bazel test --test_output=all //test/...
}

function refresh() {
  bazel run refresh_compile_commands
  # if [ $(command -v bazel-compile-commands) ]; then
  #   bazel-compile-commands //src/... //test/... //proto/... --output $current_script_dir/compile_commands.json
  # else
  #   printf $(
  #     tput setaf 3
  #     tput bold
  #   )'bazel-compile-commands not found, please install it first, download it from https://github.com/kiron1/bazel-compile-commands/releases/tag/v0.17.2 \n'$(tput sgr0)
  # fi
}

function format_bazel() {
  local buildifier_cmd="buildifier"
  [ $(command -v $buildifier_cmd) ] || {
    printf $(
      tput setaf 3
      tput bold
    )'${buildifier_cmd} not found, please install it first\n'$(tput sgr0)
    return
  }
  find src -type f \( \
    -name "BUILD" \
    -o -name "*.bzl" \
    -o -name "WORKSPACE" \
    -o -name "BUILD.bazel" \
    -o -name "*.BUILD" \
    \) -exec "$buildifier_cmd" {} \;
}

function cmake_build() {
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

function post_build() {
  refresh
  format_bazel
}

case $1 in
clean)
  clean
  bazel clean --expunge
  ;;
rpi)
  build "rpi"
  ;;
x86)
  build "x86"
  ;;
riscv)
  build "riscv"
  ;;
coverage)
  bazel coverage \
    --combined_report=lcov \
    --strategy=CoverageReport=local //test/...

  genhtml --output genhtml "$(bazel info output_path)/_coverage/_coverage_report.dat"
  ;;
*)
  printf "Usage:\n\t$ bash $0 <x86 | riscv | rpi | clean>\n"
  exit 1
  ;;
esac

printf $(
  tput setaf 2
  tput bold
)'Build success!\n'$(tput sgr0)
