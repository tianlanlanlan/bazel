#!/bin/sh
set -ex

rm -rf output

bazel build main

bazel run install

bazel run :refresh_compile_commands

# bazel shutdown
