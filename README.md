## Get started
```shell
# Build x86
$ bash build.sh

# Build rpi aarch64
# 1. Download https://github.com/ltekieli/devboards-toolchains/releases/download/v2021.12.01/aarch64-rpi3-linux-gnu.tar.gz
# 2. Extract toolchain into /opt (path hard-coded in toolchain/cc_toolchain_config.bzl)
$ bash build.sh rpi
```