load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

def _select2dict(select_str):
    result = dict()
    cxt_str = select_str[:-2].replace("select({", "")
    for kv_str in cxt_str.split("],"):
        k_str, v_str = kv_str.strip().split(": [")
        if "" == v_str.strip() or "]" == v_str.strip():
            result[k_str.strip()[1:-1]] = []
        else:
            v_list = []
            v_cxt = v_str.strip()
            if v_cxt[-1] == "]":
                v_cxt = v_str.strip()[:-1]
            for v_v in v_cxt.split(","):
                v_list.append(v_v.strip()[1:-1])
            result[k_str.strip()[1:-1]] = v_list

    return result

def _list_str2list(list_str):
    result = []
    cxt = list_str[1:-1]
    for l_str in cxt.strip().split(","):
        result.append(l_str.strip()[1:-1])
    return result

def apollo_cc_library(**kwargs):
    merge_src = []
    bin_kwargs = {}
    for i in kwargs:
        if i == "hdrs":
            continue
        elif i.endswith("include_prefix"):
            continue
        bin_kwargs[i] = kwargs[i]
    if "srcs" in kwargs:
        merge_src += kwargs["srcs"]
    if "hdrs" in kwargs:
        merge_src += kwargs["hdrs"]
    temp = {}

    select_dict_list = []
    if type(merge_src) == "select":
        merge_src_list = []
        for group_str in str(merge_src).strip().split(" + "):
            if "select({" in group_str.strip():
                select_dict_list.append(_select2dict(group_str))
            elif group_str.strip() == "[]":
                continue
            else:
                merge_src_list += _list_str2list(group_str.strip())
        merge_src = merge_src_list

    for s in merge_src:
        temp[s] = s
    merge_src = [s for s in temp]

    if len(select_dict_list) != 0:
        for i in select_dict_list:
            merge_src += select(i)

    includr_prefix_copts = ["-Isrc/"] + kwargs.pop("copts", [])
    cc_binary(**dict(
        bin_kwargs,
        name = "lib{}.so".format(bin_kwargs["name"]),
        linkshared = True,
        linkstatic = True,
        copts = includr_prefix_copts,
        srcs = merge_src,
        visibility = ["//visibility:public"],
        tags = ["export_library", kwargs["name"]],
    ))
    cc_library(**dict(
        kwargs,
        copts = includr_prefix_copts,
        srcs = [":lib{}.so".format(kwargs["name"])],
        alwayslink = True,
        visibility = ["//visibility:public"],
    ))
