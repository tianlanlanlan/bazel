#!/bin/sh
set -e
set -x

# Enable spdlog line number printing when "main.cc" is passed
enable_line_numbers=0
if [ $# -ge 1 ] && [ "$1" = "main.cc" ]; then
  enable_line_numbers=1
fi

run_main() {
  # ldd libnode.so

  local entry_lib=bazel-bin/src/libnode.so
  ls -lh $entry_lib
  ldd $entry_lib

  local dep_on_tcmalloc=0
  if readelf -d "$entry_lib" 2>/dev/null | grep -q "libtcmalloc\.so"; then
    dep_on_tcmalloc=1
    local tcmalloc_x86_lib_path=thirdparty/gperftools-2.17.2/output/lib/libtcmalloc.so
    ENV="env LD_PRELOAD=$tcmalloc_x86_lib_path TCMALLOC_SAMPLE_PARAMETER=524288"
    rm -f *.heap
  fi

  # Enable spdlog line number printing
  if [ "$enable_line_numbers" -eq 1 ]; then
    echo "[INFO] Line number printing enabled for logs (spdlog)"
  fi

  # Run
  $ENV bazel-bin/src/main "$entry_lib" "PlanningModule"
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

function run_ros2() {
  # 编译
  bazel build //ros2:example //ros2:main

  # 运行
  export AMENT_PREFIX_PATH=$(realpath thirdparty/ros2_jazzy/ros2-linux)
  export LD_LIBRARY_PATH=$AMENT_PREFIX_PATH/lib

  ./bazel-bin/ros2/example   # PublisherNode + DualThreadedNode
  # ./bazel-bin/ros2/main      # OCCNode + OdNode + SparseOneModelNode
}

# run_main

run_ros2
