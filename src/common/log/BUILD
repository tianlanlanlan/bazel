package(default_visibility = ["//visibility:public"])

# A genrule generates one or more files using a user-defined Bash command.
genrule(
    name = "c_hello_world_generator",
    outs = ["hello_world.c"],
    cmd = """
    cat << EOF >> $@
#include <stdio.h>

int main() {
    printf("Hello, World!\\n");
    return 0;
}
EOF
""",
)

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
