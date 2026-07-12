#include "common/log/log.h"
#include "proto/pnc_point.pb.h"

void LatPlanningTaskUtils() {
    AINFO << "LatPlanningTaskUtils called.";
    AWARN << "LatPlanningTaskUtils called.";

    pnc::common::proto::PathPoint proto;
    proto.set_x(0.1);
    proto.set_y(0.2);
    proto.set_z(0.3);

    AINFO << "PathPoint: " << proto.ShortDebugString();
}