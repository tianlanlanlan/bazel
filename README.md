## Get started
```shell
# Build x86
$ bash build.sh

# Build rpi aarch64
# 1. Download https://github.com/ltekieli/devboards-toolchains/releases/download/v2021.12.01/aarch64-rpi3-linux-gnu.tar.gz
# 2. Extract toolchain into /opt (path hard-coded in toolchain/cc_toolchain_config.bzl)
$ bash build.sh rpi
```

## How to download latest clang-tidy
refer to https://docs.hightec-rt.com/llvm-clang-tidy/1.0/chapter/getting-clang-tidy.html
Download the latest LLVM Clang release from here: https://github.com/llvm/llvm-project/releases/