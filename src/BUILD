load("//rules:apollo_package.bzl", "apollo_cc_library")
load("//rules/legacy_macros:miniature.bzl", "miniature")

package(default_visibility = ["//visibility:public"])

# -----------------------------------------------------------------------------
# Common target
# -----------------------------------------------------------------------------
# cc_binary(
#     name = "libcommon.so",
#     srcs = [
#         "common/common.cc",
#         "common/common.h",
#     ],
#     linkshared = True,
#     linkstatic = True,
#     tags = [
#         "common",
#         "export_library",
#     ],
#     deps = [
#         "//proto:all_custom_cc_proto",
#         "//src/common/math",
#     ],
# )

# cc_library(
#     name = "common",
#     srcs = [
#         ":libcommon.so",
#     ],
#     hdrs = [
#         "common/common.h",
#     ],
#     strip_include_prefix = "/src",
#     deps = [
#         "//proto:all_custom_cc_proto",
#         "//src/common/math",
#     ],
#     alwayslink = True,
# )

# apollo_cc_library 等同于上面的 cc_binary + cc_library
apollo_cc_library(
    name = "common",
    srcs = [
        "common/common.cc",
    ],
    hdrs = [
        "common/common.h",
    ],
    strip_include_prefix = "/src",
    deps = [
        "//proto:all_custom_cc_proto",
        "//src/common/math",
    ],
)

# -----------------------------------------------------------------------------
# framwork
# -----------------------------------------------------------------------------
apollo_cc_library(
    name = "framework",
    srcs = [
        "framework/component_interface.cc",
    ],
    hdrs = [
        "framework/component_interface.h",
        "framework/component_macro.h",
    ],
    strip_include_prefix = "/src",
)

# -----------------------------------------------------------------------------
# planning_component
# -----------------------------------------------------------------------------
cc_library(
    name = "planning_component",
    srcs = [
        "component/planning_component.cc",
    ],
    hdrs = [
        "component/planning_component.h",
    ],
    strip_include_prefix = "/src",
    deps = [
        "//proto:all_custom_cc_proto",
        "//src:framework",
        "//src/common/math",
    ],
)

# -----------------------------------------------------------------------------
# main
# -----------------------------------------------------------------------------
cc_binary(
    name = "main",
    srcs = ["main.cc"],
    linkopts = ["-ldl"],
)

# -----------------------------------------------------------------------------
# node
# -----------------------------------------------------------------------------
cc_binary(
    name = "node",
    srcs = ["node.cc"],
    linkshared = True,
    linkstatic = False,
    deps = [
        "//src:common",
        "//src:framework",
        "//src:planning_component",
    ],
)
