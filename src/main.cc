#include "common/utils/mem_info_utils.h"
#include "framework/component_interface.h"
#include "framework/registerer.h"

#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " </path/to/libnode.so> <ComponentName>" << std::endl;
        return 1;
    }

    PrintSmapsInfo();

    char *shared_lib_path = argv[1];
    char *component_name = argv[2];

    // 1. 加载动态库
    std::cout << "[INFO] Start loading library: " << shared_lib_path << std::endl;
    void *handle = dlopen(shared_lib_path, RTLD_LAZY | RTLD_GLOBAL);

    if (!handle) {
        std::cerr << "[ERROR] 无法加载库: " << shared_lib_path << "\n错误: " << dlerror() << std::endl;
        return 1;
    }

    // 2. 获取 init 函数指针
    using InitFunction = void (*)(); // 定义函数指针类型
    InitFunction init = reinterpret_cast<InitFunction>(dlsym(handle, "init"));

    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "[ERROR] 无法找到 init 函数: " << dlsym_error << std::endl;
        dlclose(handle);
        return 1;
    }

    // 3. 调用 init 方法
    init();

    // Init component and run
    std::unique_ptr<ComponentInterface> ptr = factory::Registry<ComponentInterface>::New(component_name);
    if (ptr != nullptr) {
        ptr->Init();
        ptr->Proc();
    } else {
        std::cout << "[ERROR] Cannot create: '" << component_name << "' with dlopen" << std::endl;
    }

#if 0
    // Init component and run
    std::unique_ptr<ComponentInterface> ptr = ComFactory::Instance()->Create(component_name);
    if (ptr != nullptr) {
        ptr->Init();
        ptr->Proc();
    } else {
        std::cout << "[ERROR] Cannot create: " << component_name << std::endl;
    }
#endif

    PrintSmapsInfo();

    // 4. 清理资源
    dlclose(handle);
    std::cout << "程序执行完成" << std::endl;
    return 0;
}