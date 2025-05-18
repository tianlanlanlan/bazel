#!/bin/sh
set -ex

rm -rf output

bazel build main

bazel run install
