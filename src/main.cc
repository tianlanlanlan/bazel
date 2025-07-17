#include <dlfcn.h>
#include <iostream>
#include <string>

int main() {
  // 1. 加载动态库
  const char *lib_path = "bazel-bin/src/libnode.so";
  void *handle = dlopen(lib_path, RTLD_LAZY);

  if (!handle) {
    std::cerr << "无法加载库: " << lib_path << "\n错误: " << dlerror()
              << std::endl;
    return 1;
  }

  // 2. 获取 init 函数指针
  using InitFunction = void (*)(); // 定义函数指针类型
  InitFunction init_func =
      reinterpret_cast<InitFunction>(dlsym(handle, "init"));

  const char *dlsym_error = dlerror();
  if (dlsym_error) {
    std::cerr << "无法找到 init 函数: " << dlsym_error << std::endl;
    dlclose(handle);
    return 1;
  }

  // 3. 调用 init 方法
  std::cout << "成功加载 libnode.so，调用 init 方法..." << std::endl;
  init_func();

  // 4. 清理资源
  dlclose(handle);
  std::cout << "程序执行完成" << std::endl;
  return 0;
}