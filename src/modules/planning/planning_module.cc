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
#if 0
    for (size_t i = 0; i < ptrs.size(); ++i) {
        // std::cout << "[planning] Allocating 1MB block " << i + 1 << std::endl;
        ptrs[i] = static_cast<int *>(malloc(1024 * 1024));
    }

    // free part
    for (size_t i = 0; i < ptrs.size(); ++i) {
        // std::cout << "[planning] Freeing 1MB block " << i + 1 << std::endl;
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