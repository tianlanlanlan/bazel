#pragma once

#include "component_interface.h"

// 组件注册宏
#define REGISTER_COMPONENT(COMPONENT_CLASS)                                    \
  bool COMPONENT_CLASS##_registered_ = []() {                                  \
    ComFactory::Instance()->RegisterComponent(#COMPONENT_CLASS, []() {         \
      return std::make_unique<COMPONENT_CLASS>();                              \
    });                                                                        \
    return true;                                                               \
  }()
