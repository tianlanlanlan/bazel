#include "control_module.h"

#include <cstdio>
#include <vector>

#include "common/log/log.h"
#include "proto/status.pb.h"

bool ControlModule::Init() {
    AINFO << "ControlModule::Init() called";

    return true;
}

bool ControlModule::Proc() {
    AINFO << "ControlModule::Proc() called";

    std::vector<int *> ptrs(100, nullptr);

    Status proto;
    proto.set_name("ControlModule");
    proto.set_id(1);
    AINFO << "Status " << proto.ShortDebugString();

    return true;
}