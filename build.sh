#!/bin/sh
set -ex

rm -rf output

bazel build --config=asan --subcommands main

declare -r tmpdir="$(pwd)/output"
bazel run --config=asan //src:install_main -- "${tmpdir}"

bazel run refresh_compile_commands

# bazel shutdown
