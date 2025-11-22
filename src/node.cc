// #include "common/math/vec2d.h"
#include <iostream>
#include <memory>

#include "framework/component_interface.h"

#include "framework/registerer.h"

extern "C" {

void init() {
    std::cout << "[INFO] node init() called" << std::endl;

    // apollo::common::math::Vec2d vec(3.0, 4.0);
    // std::cout << "Vec2d length: " << vec.Length() << std::endl;

    // Init component and run
    {
        std::string component_name = "PlanningModule";
        std::unique_ptr<ComponentInterface> ptr = factory::Registry<ComponentInterface>::New(component_name);
        if (ptr != nullptr) {
            ptr->Init();
            ptr->Proc();
        } else {
            std::cout << "[ERROR] Cannot create: " << component_name << std::endl;
        }
    }

    {
        std::string component_name = "ControlModule";
        std::unique_ptr<ComponentInterface> ptr = factory::Registry<ComponentInterface>::New(component_name);
        if (ptr != nullptr) {
            ptr->Init();
            ptr->Proc();
        } else {
            std::cout << "[ERROR] Cannot create: " << component_name << std::endl;
        }
    }
}
}