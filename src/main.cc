#include "common/log/log.h"
#include "common/utils/mem_info_utils.h"
#include "framework/component_interface.h"
#include "framework/registerer.h"

#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

void TestExplicitConstructor() {
    class Foo {
      private:
        int foo_;

      public:
        explicit Foo(int foo) : foo_(foo) {}

        void foo() { AINFO << "foo: " << this->foo_; }
    };

    auto test_func = [](Foo foo) { foo.foo(); };
    test_func(Foo(100));
}

template <typename... Args> void fold_expression_printer(Args &&...args) { (AINFO << ... << args); }
void TestFoldExpression() {
    int a = 10;
    double b = 20.0;
    std::string c = "hello";
    fold_expression_printer(a, b, c);
}

int TestDLOpen(const int argc, char *argv[]) {
    if (argc < 3) {
        AERROR << "Usage: " << argv[0] << " </path/to/libnode.so> <ComponentName>";
        return 1;
    }

    PrintSmapsInfo();

    char *shared_lib_path = argv[1];
    char *component_name = argv[2];

    // 1. 加载动态库
    AINFO << "Start loading library: " << shared_lib_path;
    void *handle = dlopen(shared_lib_path, RTLD_LAZY | RTLD_GLOBAL);

    if (!handle) {
        AERROR << "无法加载库: " << shared_lib_path << "\n错误: " << dlerror();
        return 1;
    }

    // 2. 获取 init 函数指针
    using InitFunction = void (*)(); // 定义函数指针类型
    InitFunction init = reinterpret_cast<InitFunction>(dlsym(handle, "init"));

    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        AERROR << "无法找到 init 函数: " << dlsym_error;
        dlclose(handle);
        return 1;
    }

    // 3. 调用 init 方法
    init();

    // Init component and run
    std::unique_ptr<ComponentInterface> ptr = factory::Registry<ComponentInterface>::New(component_name);
    if (ptr != nullptr) {
        ptr->Init();

        AINFO << "Run ComponentInterface";
        int count = 100 * 100;
        while (count--) {
            ptr->Proc();
        }
    } else {
        AERROR << "Cannot create: '" << component_name << "' with dlopen";
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
    AINFO << "程序执行完成";
    return 0;
}

int main(int argc, char **argv) {
    TestDLOpen(argc, argv);

    TestExplicitConstructor();

    TestFoldExpression();

    return 0;
}