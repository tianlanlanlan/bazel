// #include "common/math/vec2d.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>

#include "framework/component_interface.h"

#include "framework/registerer.h"
#include "gperftools/heap-profiler.h"
#include "gperftools/malloc_extension.h"

// 获取当前时间戳
std::string get_current_timestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y%m%d_%H%M%S");
    return ss.str();
}

// 保存字符串到文件
bool save_string_to_file(const std::string &content, const std::string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Failed to open file: " << filename << std::endl;
        return false;
    }

    file << content;
    file.close();
    std::cout << "[INFO] Saved to file: " << filename << " (" << content.size() << " bytes)" << std::endl;
    return true;
}

extern "C" {

void init() {
    HeapProfilerStart("node");
    std::cout << "[INFO] node init() called" << std::endl;

    // apollo::common::math::Vec2d vec(3.0, 4.0);
    // std::cout << "Vec2d length: " << vec.Length() << std::endl;

    // Init component and run
    auto thread1 = std::thread([]() {
        std::string base_filename = "heap_planning_" + get_current_timestamp();
        int count = 10;
        for (int i = 0; i < count; i++) {
            std::string component_name = "PlanningModule";
            std::unique_ptr<ComponentInterface> ptr = factory::Registry<ComponentInterface>::New(component_name);
            if (ptr != nullptr) {
                ptr->Init();
                ptr->Proc();
            } else {
                std::cout << "[ERROR] Cannot create: " << component_name << std::endl;
            }

            // 获取堆样本并保存到文件
            std::string heap_profile;
            MallocExtension::instance()->GetHeapSample(&heap_profile);

            if (!heap_profile.empty()) {
                std::string filename = base_filename + "_" + std::to_string(i) + ".txt";
                save_string_to_file(heap_profile, filename);
            } else {
                std::cout << "[WARN] Empty heap profile at iteration " << i << std::endl;
            }

            // 暂停一下
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    auto thread2 = std::thread([]() {
        std::string component_name = "ControlModule";
        std::unique_ptr<ComponentInterface> ptr = factory::Registry<ComponentInterface>::New(component_name);
        if (ptr != nullptr) {
            ptr->Init();
            ptr->Proc();
        } else {
            std::cout << "[ERROR] Cannot create: " << component_name << std::endl;
        }
    });

    thread1.join();
    thread2.join();
}
}