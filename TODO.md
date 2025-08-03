TODO:
1. 多个 BUILD，多个 target 公用一个宏/变量
2. 支持交叉编译/cuda编译 (done)
3. 支持是否strip动态库
4. 支持Release/Debug等类似的编译类型 (done)
5. 支持 bazel install，不要 output 下面出现一堆名字无法控制/bazel编译的三方库（采用预编译库）
6. 继续调用快速生成 compile_commnads.json 的方式，不用 hedron_compile_commands (效率太低),考虑 bear ? (done, 使用 bazel-compile-commands)

vscode用户推荐安装：
1. Bazel 插件
2. Clangd 插件