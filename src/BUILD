load("//rules/legacy_macros:miniature.bzl", "miniature")

package(default_visibility = ["//visibility:public"])

miniature(
    name = "logo_miniature",
    src = "image.txt",
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
)
