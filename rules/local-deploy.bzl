# This extension is a Bazel rule for local deployment of build artifacts.
# Most copyed from https://www.grahambrooks.com/software-development/2021/05/31/bazel-local-install.html
"""
Rule for local *nix deployment of a binary build artifact.

This is useful for local development but is not intended for production deployments.
"""

# tag::_local_deploy_impl[]
def _local_deploy_impl(ctx):
    # print(ctx.files)
    # for s in ctx.attr.srcs:
    #     print("source %s" % s)
    #     print("source path %s" % s.label)

    # for s in ctx.files.srcs:
    #     print("source struct              %s" % s)
    #     print("real path                  %s" % ctx.expand_location("$(realpath \"%s\")" % s.path))
    #     print("Context                    %s" % ctx)
    #     print("workspace name             %s" % ctx.workspace_name)
    #     print("context variables          %s" % ctx.var)
    #     print("attributes                 %s" % ctx.attr)
    #     print("bin_dir                    %s" % ctx.bin_dir.path)
    #     print("genfiles_dir               %s" % ctx.genfiles_dir.path)
    #     print("build file path            %s" % ctx.build_file_path)
    #     print("executable                 %s" % ctx.executable)

    install_dir = ctx.attr.install_dir  # <1>
    shell_commands = ""

    for s in ctx.files.srcs:
        shell_commands += "echo Copying %s to %s\n" % (s.short_path, install_dir)
        shell_commands += "mkdir -p %s\n" % (install_dir)
        shell_commands += "cp %s %s\n" % (s.short_path, install_dir)  # <2>

    ctx.actions.write(
        # <3>
        output = ctx.outputs.executable,
        is_executable = True,
        content = shell_commands,
    )
    runfiles = ctx.runfiles(files = ctx.files.srcs)  # <4>
    return DefaultInfo(
        # <5>
        executable = ctx.outputs.executable,
        runfiles = runfiles,
    )

# end::_local_deploy_impl[]

# tag::local_deploy_rule[]
local_deploy = rule(
    executable = True,  # <1>
    implementation = _local_deploy_impl,  # <2>
    attrs = {
        "srcs": attr.label_list(allow_files = True),  # <3>
        "install_dir": attr.string(default = "/usr/local/bin/", doc = "Deployment target directory"),  # <4>
    },
)
# end::local_deploy_rule[]
