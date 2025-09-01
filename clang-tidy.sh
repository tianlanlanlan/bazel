run_clang_tidy() {
  ./clang-tidy -checks=misc-include-cleaner -p . -fix-errors src/node.cc -- -isystem /usr/lib/llvm-19/lib/clang/19/include/
}

run_clang_tidy
