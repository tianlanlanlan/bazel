load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

INCLUDE_PREFIX = "src/"

def pnc_cc_library(**kwargs):
    copts = ["-I" + INCLUDE_PREFIX] + kwargs.pop("copts", [])
    cc_library(**dict(
        kwargs,
        copts = copts,
        visibility = ["//visibility:public"],
    ))


def pnc_cc_binary(**kwargs):
    copts = ["-I" + INCLUDE_PREFIX] + kwargs.pop("copts", [])
    cc_binary(**dict(
        kwargs,
        copts = copts,
        visibility = ["//visibility:public"],
    ))
