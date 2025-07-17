load("//rules/legacy_macros:miniature.bzl", "miniature")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "common_base",
    srcs = [
        "common/common.cc",
    ],
    hdrs = [
        "common/common.h",
    ],
    strip_include_prefix = "/src",
    deps = [
        "//proto:all_custom_cc_proto",
    ],
)

cc_shared_library(
    name = "common",
    exports_filter = [
        "@@//proto:all_custom_proto",  # 傻逼 Bazel
        "@@protobuf+//src/google/protobuf:protobuf",
        "@@protobuf+//src/google/protobuf:protobuf_lite",
        "@@protobuf+//src/google/protobuf/io:gzip_stream",
        "@@zlib+//:z",
        "@@protobuf+//src/google/protobuf/io:printer",
        "@@protobuf+//src/google/protobuf/io:zero_copy_sink",
        "@@protobuf+//src/google/protobuf/io:tokenizer",
        "@@protobuf+//src/google/protobuf/io:io",
        "@@protobuf+//src/google/protobuf/io:io_win32",
        "@@protobuf+//src/google/protobuf:arena",
        "@@protobuf+//src/google/protobuf:arena_align",
        "@@protobuf+//src/google/protobuf/stubs:lite",
        "@@protobuf+//src/google/protobuf:port",
        "@@protobuf+//third_party/utf8_range:utf8_validity",
        "@@protobuf+//third_party/utf8_range:utf8_range",
        "@@abseil-cpp+//absl/container:raw_hash_set",
        "@@abseil-cpp+//absl/container:hashtablez_sampler",
        "@@abseil-cpp+//absl/log/internal:check_op",
        "@@abseil-cpp+//absl/log/internal:conditions",
        "@@abseil-cpp+//absl/log/internal:log_message",
        "@@abseil-cpp+//absl/log/internal:format",
        "@@abseil-cpp+//absl/log/internal:nullguard",
        "@@abseil-cpp+//absl/log/internal:structured_proto",
        "@@abseil-cpp+//absl/log/internal:proto",
        "@@abseil-cpp+//absl/debugging:examine_stack",
        "@@abseil-cpp+//absl/log/internal:log_sink_set",
        "@@abseil-cpp+//absl/log/internal:globals",
        "@@abseil-cpp+//absl/log:globals",
        "@@abseil-cpp+//absl/hash:hash",
        "@@abseil-cpp+//absl/hash:city",
        "@@abseil-cpp+//absl/hash:low_level_hash",
        "@@abseil-cpp+//absl/log:log_sink",
        "@@abseil-cpp+//absl/log:log_entry",
        "@@abseil-cpp+//absl/log/internal:vlog_config",
        "@@abseil-cpp+//absl/log/internal:fnmatch",
        "@@abseil-cpp+//absl/status:statusor",
        "@@abseil-cpp+//absl/status:status",
        "@@abseil-cpp+//absl/base:strerror",
        "@@abseil-cpp+//absl/debugging:leak_check",
        "@@abseil-cpp+//absl/strings:cord",
        "@@abseil-cpp+//absl/strings:cordz_info",
        "@@abseil-cpp+//absl/strings:cord_internal",
        "@@abseil-cpp+//absl/strings:cordz_functions",
        "@@abseil-cpp+//absl/profiling:exponential_biased",
        "@@abseil-cpp+//absl/strings:cordz_handle",
        "@@abseil-cpp+//absl/crc:crc_cord_state",
        "@@abseil-cpp+//absl/crc:crc32c",
        "@@abseil-cpp+//absl/crc:crc_internal",
        "@@abseil-cpp+//absl/crc:cpu_detect",
        "@@abseil-cpp+//absl/strings:str_format_internal",
        "@@abseil-cpp+//absl/synchronization:synchronization",
        "@@abseil-cpp+//absl/synchronization:graphcycles_internal",
        "@@abseil-cpp+//absl/synchronization:kernel_timeout_internal",
        "@@abseil-cpp+//absl/base:tracing_internal",
        "@@abseil-cpp+//absl/debugging:stacktrace",
        "@@abseil-cpp+//absl/debugging:symbolize",
        "@@abseil-cpp+//absl/debugging:debugging_internal",
        "@@abseil-cpp+//absl/debugging:demangle_internal",
        "@@abseil-cpp+//absl/debugging:demangle_rust",
        "@@abseil-cpp+//absl/debugging:decode_rust_punycode",
        "@@abseil-cpp+//absl/debugging:utf8_for_code_point",
        "@@abseil-cpp+//absl/base:malloc_internal",
        "@@abseil-cpp+//absl/time:time",
        "@@abseil-cpp+//absl/strings:strings",
        "@@abseil-cpp+//absl/strings:internal",
        "@@abseil-cpp+//absl/strings:string_view",
        "@@abseil-cpp+//absl/base:base",
        "@@abseil-cpp+//absl/base:spinlock_wait",
        "@@abseil-cpp+//absl/numeric:int128",
        "@@abseil-cpp+//absl/time/internal/cctz:time_zone",
        "@@abseil-cpp+//absl/time/internal/cctz:civil_time",
        "@@abseil-cpp+//absl/types:bad_optional_access",
        "@@abseil-cpp+//absl/base:throw_delegate",
        "@@abseil-cpp+//absl/types:bad_variant_access",
        "@@abseil-cpp+//absl/base:raw_logging_internal",
        "@@abseil-cpp+//absl/base:log_severity",
    ],
    deps = [
        ":common_base",
    ],
)

cc_library(
    name = "framework_base",
    srcs = [
        "framework/component_interface.cc",
    ],
    hdrs = [
        "framework/component_interface.h",
        "framework/component_macro.h",
    ],
    strip_include_prefix = "/src",
)

cc_shared_library(
    name = "framework",
    deps = [
        ":framework_base",
    ],
)

cc_library(
    name = "planning_component_base",
    srcs = [
        "component/planning_component.cc",
    ],
    hdrs = [
        "component/planning_component.h",
    ],
    strip_include_prefix = "/src",
    deps = [
        "//proto:all_custom_cc_proto",
        "//src:framework_base",
    ],
)

cc_shared_library(
    name = "planning_component",
    dynamic_deps = [
        "//src:common",
        "//src:framework",
    ],
    deps = [
        ":planning_component_base",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
)

cc_binary(
    name = "node",
    srcs = ["node.cc"],
    dynamic_deps = [
        "//src:planning_component",
        "//src:common",
        "//src:framework",
    ],
    linkshared = True,
    deps = [
        "//src:common_base",
        "//src:framework_base",
        "//src:planning_component_base",
    ],
)
