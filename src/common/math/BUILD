package(default_visibility = ["//visibility:public"])

cc_library(
    name = "common_math",
    srcs = ["vec2d.cc"],
    hdrs = ["vec2d.h"],
    strip_include_prefix = "/src",
)

cc_test(
    name = "vec2d_test",
    size = "small",
    srcs = ["vec2d_test.cc"],
    deps = [
        ":common_math",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
