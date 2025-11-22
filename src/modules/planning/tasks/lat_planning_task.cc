#include "lat_planning_task.h"
#include <cstdio>
#include <vector>

#include <iostream>

#include "spdlog/spdlog.h"

#include "common/math/vec2d.h"

#include "lat_planning_utils.h"

bool LatPlanningTask::Init() {
    spdlog::info("LatPlanningTask Init started.");
    apollo::common::math::Vec2d vec(1.0, 2.0);
    vec.set_x(3.0);
    vec.set_y(4.0);
    printf("Vec2d: %s\n", vec.DebugString().c_str());
    return true;
}

bool LatPlanningTask::Proc() {
    spdlog::info("LatPlanningTask Proc started.");
    LatPlanningTaskUtils();
    return true;
}