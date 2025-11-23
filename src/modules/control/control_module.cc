#include "control_module.h"

#include "proto/status.pb.h"
#include "spdlog/spdlog.h"
#include <cstdio>
#include <iostream>
#include <vector>

bool ControlModule::Init() {
    spdlog::info("ControlModule::Init() called");

    return true;
}

bool ControlModule::Proc() {
    spdlog::info("ControlModule::Proc() called");

    std::vector<int *> ptrs(100, nullptr);

    Status proto;
    proto.set_name("ControlModule");
    proto.set_id(1);
    spdlog::info("Status {}", proto.ShortDebugString());

    return true;
}