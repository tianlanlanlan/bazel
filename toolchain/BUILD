load(":cc_toolchain_config.bzl", "cc_toolchain_config")

package(default_visibility = ["//visibility:public"])

cc_toolchain_config(name = "aarch64_toolchain_config")

filegroup(name = "empty")

cc_toolchain(
    name = "aarch64_toolchain",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
    toolchain_config = ":aarch64_toolchain_config",
    toolchain_identifier = "linux_x86_64-toolchain",
)

toolchain(
    name = "cc_toolchain_for_linux_aarch64_rpi3",
    exec_compatible_with = [
        "@platforms//cpu:x86_64",
        "@platforms//os:linux",
    ],
    target_compatible_with = [
        "@platforms//cpu:aarch64",
        "@platforms//os:linux",
    ],
    toolchain = ":aarch64_toolchain",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
)
