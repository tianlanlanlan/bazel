#include "control_module.h"
#include <cstdio>
#include <vector>

#include <iostream>

#include "spdlog/spdlog.h"

bool ControlModule::Init() {
    printf("ControlModule::Init() called\n");

    spdlog::info("ControlModule started.");

    return true;
}

bool ControlModule::Proc() {
    printf("ControlModule::Proc() called\n");

    std::vector<int *> ptrs(100, nullptr);

    return true;
}