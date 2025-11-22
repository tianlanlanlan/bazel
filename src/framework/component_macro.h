#pragma once

#include "component_interface.h"

// 组件注册宏
// 为什么这种做法，在下面场景无法注册成功：
// main 调用 dlopen libnode.so, main 调用 ComFactory::Instance()->Create("PlanningModule")
// libnode.so 强制链接 libplanning_module.so
#define REGISTER_COMPONENT(COMPONENT_CLASS)                                                                            \
    bool COMPONENT_CLASS##_registered_ = []() {                                                                        \
        ComFactory::Instance()->RegisterComponent(#COMPONENT_CLASS,                                                    \
                                                  []() { return std::make_unique<COMPONENT_CLASS>(); });               \
        return true;                                                                                                   \
    }()
