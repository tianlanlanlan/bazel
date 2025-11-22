# NEW
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

# At this point, Bazel has enough information to attempt building the code,
# but it still does not know what tools to use to complete the required build actions.
# For that, you need the tool_path() constructor
load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",  # NEW
    "flag_group",  # NEW
    "flag_set",  # NEW
    "tool_path",
)

# 在顶部添加路径变量
TOOLCHAIN_ROOT = "/opt/toolchain/rpi3"  # 根据实际路径修改

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
        tool_path(
            name = "ar",
            path = TOOLCHAIN_ROOT + "/bin/aarch64-rpi3-linux-gnu-ar",
        ),
        tool_path(
            name = "cpp",
            path = TOOLCHAIN_ROOT + "/bin/aarch64-rpi3-linux-gnu-cpp",
        ),
        tool_path(
            name = "gcc",
            path = TOOLCHAIN_ROOT + "/bin/aarch64-rpi3-linux-gnu-gcc",
        ),
        tool_path(
            name = "gcov",
            path = TOOLCHAIN_ROOT + "/bin/aarch64-rpi3-linux-gnu-gcov",
        ),
        tool_path(
            name = "ld",
            path = TOOLCHAIN_ROOT + "/bin/aarch64-rpi3-linux-gnu-ld",
        ),
        tool_path(
            name = "nm",
            path = TOOLCHAIN_ROOT + "/bin/aarch64-rpi3-linux-gnu-nm",
        ),
        tool_path(
            name = "objdump",
            path = TOOLCHAIN_ROOT + "/bin/aarch64-rpi3-linux-gnu-objdump",
        ),
        tool_path(
            name = "strip",
            path = TOOLCHAIN_ROOT + "/bin/aarch64-rpi3-linux-gnu-strip",
        ),
    ]

    features = [
        # default_compiler_flags
        feature(
            name = "default_compiler_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_compile_actions,
                    flag_groups = [
                        flag_group(
                            flags = [
                                # "--sysroot=external/aarch64-rpi3-linux-gnu-sysroot",
                                "-no-canonical-prefixes",
                                "-fno-canonical-system-headers",
                                "-Wno-builtin-macro-redefined",
                                "-D__DATE__=\"redacted\"",
                                "-D__TIMESTAMP__=\"redacted\"",
                                "-D__TIME__=\"redacted\"",
                            ],
                        ),
                    ],
                ),
            ],
        ),

        # default_linker_flags
        feature(
            name = "default_linker_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = all_link_actions,
                    flag_groups = ([
                        flag_group(
                            flags = [
                                # "--sysroot=external/aarch64-rpi3-linux-gnu-sysroot",
                                "-lstdc++",
                                "-lm",
                                "-ldl",
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
            TOOLCHAIN_ROOT + "/aarch64-rpi3-linux-gnu/include/c++/10.2.0/",
            TOOLCHAIN_ROOT + "/include",
            TOOLCHAIN_ROOT + "/aarch64-rpi3-linux-gnu/sysroot/usr/include/",
            TOOLCHAIN_ROOT + "/lib/gcc/aarch64-rpi3-linux-gnu/10.2.0/include/",
            TOOLCHAIN_ROOT + "/lib/gcc/aarch64-rpi3-linux-gnu/10.2.0/include-fixed/",
        ],
        toolchain_identifier = "local",
        host_system_name = "local",
        target_system_name = "local",
        target_cpu = "k8",
        target_libc = "unknown",
        compiler = "clang",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,  # NEW
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)
