load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")

# For clangd
load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

alias(
    name = "main",
    actual = "//src:main",
    visibility = ["//visibility:public"],
)

alias(
    name = "install",
    actual = "//src:install",
    visibility = ["//visibility:public"],
)

refresh_compile_commands(
    name = "refresh_compile_commands",

    # If you've got a very large project and compile_commands.json is taking a while to generate:
    # Adding exclude_external_sources = True and exclude_headers = "external" can help, with some tradeoffs.
    exclude_external_sources = True,
    exclude_headers = "external",

    # Specify the targets of interest.
    # For example, specify a dict of targets and any flags required to build.
    targets = {
        "//src/...": "",
    },

    # No need to add flags already in .bazelrc. They're automatically picked up.
    # If you don't need flags, a list of targets is also okay, as is a single target string.
    # Wildcard patterns, like //... for everything, *are* allowed here, just like a build.
    # As are additional targets (+) and subtractions (-), like in bazel query https://docs.bazel.build/versions/main/query.html#expressions
    # And if you're working on a header-only library, specify a test or binary target that compiles it.
)

# # project/BUILD

# pkg_tar(
#     name = "release_libs",
#     package_dir = "lib",
#     srcs = [
#         "//src:main",
#     ],
# )

# pkg_tar(
#     name = "release",
#     deps = [
#         ":release_libs",
#     ],
# )
