proto_library(
    name = "all_custom_proto",
    srcs = [
        "perf_info.proto",
        "status.proto",
    ],
    strip_import_prefix = "/proto",
    visibility = ["//visibility:public"],
)

cc_proto_library(
    name = "all_custom_cc_proto",
    visibility = ["//visibility:public"],
    deps = [":all_custom_proto"],
)

cc_shared_library(
    name = "all_custom_shared",
    visibility = ["//visibility:public"],
    deps = [":all_custom_cc_proto"],
)
