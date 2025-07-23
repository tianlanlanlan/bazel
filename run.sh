#!/bin/sh
set -e

# Build
bazel build //src:main
bazel build //src:node

# ldd libnode.so
ldd bazel-bin/src/libnode.so

# Run
bazel-bin/src/main
