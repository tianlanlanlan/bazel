#include "spdlog/spdlog.h"

#include "proto/pnc_point.pb.h"

void LatPlanningTaskUtils() {
    spdlog::info("LatPlanningTaskUtils called.");
    spdlog::warn("LatPlanningTaskUtils called.");

    pnc::common::proto::PathPoint proto;
    proto.set_x(0.1);
    proto.set_y(0.2);
    proto.set_z(0.3);

    spdlog::info("PathPoint: {}", proto.ShortDebugString());
}