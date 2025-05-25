load("@com_github_google_rules_install//installer:def.bzl", "installer")
load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

alias(
    name = "main",
    actual = "//src:main",
    visibility = ["//visibility:public"],
)

alias(
    name = "common_math",
    actual = "//src/common/math:common_math",
    visibility = ["//visibility:public"],
)

# Target to generate and refresh compile_commands.json.
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

# Target for copy build artifacts to a directory.
installer(
    name = "install",
    data = [
        "//src:main",
        "//src/common/math:common_math",
    ],
)
