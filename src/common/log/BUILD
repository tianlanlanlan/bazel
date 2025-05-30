package(default_visibility = ["//visibility:public"])

genrule(
    name = "generate_header",
    outs = ["header.h"],
    cmd = "./$(location :header_generator) > $@",
    tools = [":header_generator"],
)

cc_library(
    name = "header",
    hdrs = [":generate_header"],
)
