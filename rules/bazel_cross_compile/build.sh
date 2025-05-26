# cd 03_toolchain
# bazel build \
#     --crosstool_top=//bazel/toolchain/aarch64-rpi3-linux-gnu:gcc_toolchain \
#     --cpu=aarch64 \
#     //:hello

cd 04_platforms
bazel build \
    --incompatible_enable_cc_toolchain_resolution \
    --platforms=//bazel/platforms:rpi \
    //:hello
