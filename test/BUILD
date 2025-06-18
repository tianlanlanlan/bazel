cc_test(
    name = "log_test",
    size = "small",
    srcs = ["log_test.cc"],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "@spdlog",
    ],
)

genrule(
    name = "gen_log",
    outs = [
        "log.h",
        "log.cc",
    ],
    cmd = """
        bash $(location gen_log.sh) \
            --header $(location log.h) \
            --source $(location log.cc)
    """,
    tools = ["gen_log.sh"],
)
