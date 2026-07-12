#include "lat_planning_task.h"

#include <cstdio>
#include <vector>

#include "common/log/log.h"
#include "common/math/vec2d.h"
#include "lat_planning_utils.h"
#include "proto/perf_info.pb.h"

bool LatPlanningTask::Init() {
    AINFO << "LatPlanningTask Init started.";
    apollo::common::math::Vec2d vec(1.0, 2.0);
    vec.set_x(3.0);
    vec.set_y(4.0);
    AINFO << "Vec2d: " << vec.DebugString();
    return true;
}

bool LatPlanningTask::Proc() {
    AINFO << "LatPlanningTask Proc started.";
    LatPlanningTaskUtils();

    PerfInfo proto;
    proto.set_duration_ms(100.0);
    AINFO << "PerfInfo " << proto.ShortDebugString();

    return true;
}