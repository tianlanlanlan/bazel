// #include "common/math/vec2d.h"
#include <iostream>
#include <memory>

#include "framework/component_interface.h"

extern "C" {
void init() {
    std::cout << "node init() called" << std::endl;

    // apollo::common::math::Vec2d vec(3.0, 4.0);
    // std::cout << "Vec2d length: " << vec.Length() << std::endl;

    // Init component and run
    // std::unique_ptr<ComponentInterface> ptr = ComFactory::Instance()->Create("PlanningComponent");
    // if (ptr != nullptr) {
    //     ptr->Init();
    //     ptr->Proc();
    // } else {
    //     std::cout << "[Error] Cannot create: " << "PlanningComponent" << std::endl;
    // }
}
}