#!/bin/sh
set -e

run_main() {
  # ldd libnode.so
  ldd bazel-bin/src/libnode.so

  # Run
  heaptrack bazel-bin/src/main
}

# Run coverage
coverage() {
  # Run tests with coverage
  bazel coverage --test_output=all \
    --coverage_report_generator="//bazel/coverage_output_generator:coverage_report_generator" \
    //src/...

  # Generate coverage report
  local bazel_output_path=$(bazel info output_path)
  find $bazel_output_path -name "coverage*.dat" -exec cat {} + >"$bazel_output_path/coverage.dat"
  genhtml --branch-coverage --output genhtml "$bazel_output_path/coverage.dat"
}

# coverage

run_main
