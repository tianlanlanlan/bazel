# NEW
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

# NEW
load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",  # NEW
    "flag_group",  # NEW
    "flag_set",  # NEW
    "tool_path",
)

RISCV_64_TOOLCHAIN_PREFIX = "/opt/riscv/bin/riscv64-unknown-linux-gnu-"

all_link_actions = [
    # NEW
    ACTION_NAMES.cpp_link_executable,
    ACTION_NAMES.cpp_link_dynamic_library,
    ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

all_compile_actions = [
    ACTION_NAMES.assemble,
    ACTION_NAMES.c_compile,
    ACTION_NAMES.clif_match,
    ACTION_NAMES.cpp_compile,
    ACTION_NAMES.cpp_header_parsing,
    ACTION_NAMES.cpp_module_codegen,
    ACTION_NAMES.cpp_module_compile,
    ACTION_NAMES.linkstamp_compile,
    ACTION_NAMES.lto_backend,
    ACTION_NAMES.preprocess_assemble,
]

def _impl(ctx):
    tool_paths = [
        # NEW
        tool_path(
            name = "gcc",
            path = RISCV_64_TOOLCHAIN_PREFIX + "gcc",
        ),
        tool_path(
            name = "ld",
            path = RISCV_64_TOOLCHAIN_PREFIX + "ld",
        ),
        tool_path(
            name = "ar",
            path = RISCV_64_TOOLCHAIN_PREFIX + "ar",
        ),
        tool_path(
            name = "cpp",
            path = RISCV_64_TOOLCHAIN_PREFIX + "g++",
        ),
        tool_path(
            name = "gcov",
            path = RISCV_64_TOOLCHAIN_PREFIX + "gcov",
        ),
        tool_path(
            name = "nm",
            path = RISCV_64_TOOLCHAIN_PREFIX + "nm",
        ),
        tool_path(
            name = "objdump",
            path = RISCV_64_TOOLCHAIN_PREFIX + "objdump",
        ),
        tool_path(
            name = "strip",
            path = RISCV_64_TOOLCHAIN_PREFIX + "strip",
        ),
    ]

    features = [
        feature(name = "supports_dynamic_linker", enabled = True),
        feature(
            name = "default_compiler_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_compile_actions,
                    flag_groups = [
                        flag_group(
                            flags = [
                                "--sysroot=/opt/riscv/sysroot/",
                                "-no-canonical-prefixes",
                                "-fno-canonical-system-headers",
                                "-Wno-builtin-macro-redefined",
                            ],
                        ),
                    ],
                ),
            ],
        ),
        feature(
            name = "default_linker_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_link_actions,
                    flag_groups = ([
                        flag_group(
                            flags = [
                                "--sysroot=/opt/riscv/sysroot/",
                                "-lstdc++",
                            ],
                        ),
                    ]),
                ),
            ],
        ),
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        features = features,  # NEW
        cxx_builtin_include_directories = [
            # NEW
            "/opt/riscv/riscv64-unknown-linux-gnu/include/c++/15.1.0/",
            "/opt/riscv/lib/gcc/riscv64-unknown-linux-gnu/15.1.0/",
            "/opt/riscv/sysroot/usr/include/",
        ],
        toolchain_identifier = "local",
        host_system_name = "local",
        target_system_name = "local",
        target_cpu = "riscv64",
        target_libc = "unknown",
        compiler = "gcc",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,  # NEW
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)
