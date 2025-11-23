## Get started
Tested on: Ubuntu 22.04 x86_64
```shell
# Build thirdparty
$ bash thirdparty/spdlog-1.16.0/build.sh

# Build x86
$ bash build.sh x86

# Build riscv
# First download https://github.com/riscv-collab/riscv-gnu-toolchain/releases/download/2025.11.21/riscv64-glibc-ubuntu-22.04-gcc.tar.xz and unzip to /opt/riscv
$ bash build.sh riscv

# Build rpi aarch64
# 1. Download https://github.com/ltekieli/devboards-toolchains/releases/download/v2021.12.01/aarch64-rpi3-linux-gnu.tar.gz
# 2. Extract toolchain into /opt (path hard-coded in toolchain/cc_toolchain_config.bzl)
$ bash build.sh rpi
```

## How to download latest clang-tidy
refer to https://docs.hightec-rt.com/llvm-clang-tidy/1.0/chapter/getting-clang-tidy.html
Download the latest LLVM Clang release from here: https://github.com/llvm/llvm-project/releases/