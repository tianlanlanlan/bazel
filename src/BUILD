load("@com_github_google_rules_install//installer:def.bzl", "installer")

package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "main",
    srcs = ["main.cc"],
)

installer(
    name = "install_main",
    data = [":main"],
)
