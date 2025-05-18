load("//rules:local-deploy.bzl", "local_deploy")  # <1>
package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "main",
    srcs = ["main.cc"],
)

local_deploy(
    name = "install",  # <2>
    srcs = [":main"],  # <3>
    install_dir = "/home/tianlan/bazel/output",  # <4>
)
