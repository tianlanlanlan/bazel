#include "planning_module.h"
#include <cstdio>
#include <vector>

#include <iostream>

#include "proto/perf_info.pb.h"
#include "spdlog/spdlog.h"

#include "common/math/vec2d.h"

bool PlanningModule::Init() {
    spdlog::info("PlanningModule::Init() called");

    apollo::common::math::Vec2d vec(1.0, 2.0);
    vec.set_x(3.0);
    vec.set_y(4.0);
    spdlog::info("Vec2d: {}", vec.DebugString().c_str());

    return true;
}

bool PlanningModule::Proc() {
    spdlog::info("PlanningModule::Proc() called");

    spdlog::info("PlanningModule processing started.");

    std::vector<int *> ptrs(100, nullptr);

    // malloc

    constexpr int kSize = 1024;
    for (size_t i = 0; i < ptrs.size(); ++i) {
        ptrs[i] = static_cast<int *>(malloc(sizeof(int) * kSize));
        for (int j = 0; j < kSize; j++) {
            ptrs[i][j] = j;
        }
    }

#if 0
    // free part
    for (size_t i = 0; i < ptrs.size(); ++i) {
        free(ptrs[i]);
    }
#endif

    {
        std::string task_name = "LatPlanningTask";
        std::unique_ptr<TaskInterface> ptr = factory::Registry<TaskInterface>::New(task_name);
        if (ptr != nullptr) {
            ptr->Init();
            ptr->Proc();
        } else {
            std::cout << "[ERROR] Cannot create: " << task_name << std::endl;
        }
    }

    PerfInfo proto;
    proto.set_duration_ms(100.0);
    spdlog::info("PerfInfo {}", proto.ShortDebugString());

    return true;
}