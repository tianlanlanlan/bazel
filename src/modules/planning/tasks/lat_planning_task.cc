#include "lat_planning_task.h"

#include "common/math/vec2d.h"
#include "lat_planning_utils.h"
#include "proto/perf_info.pb.h"
#include "spdlog/spdlog.h"

#include <cstdio>
#include <iostream>
#include <vector>

bool LatPlanningTask::Init() {
    spdlog::info("LatPlanningTask Init started.");
    apollo::common::math::Vec2d vec(1.0, 2.0);
    vec.set_x(3.0);
    vec.set_y(4.0);
    spdlog::info("Vec2d: {}", vec.DebugString().c_str());
    return true;
}

bool LatPlanningTask::Proc() {
    spdlog::info("LatPlanningTask Proc started.");
    LatPlanningTaskUtils();

    PerfInfo proto;
    proto.set_duration_ms(100.0);
    spdlog::info("PerfInfo {}", proto.ShortDebugString());

    return true;
}