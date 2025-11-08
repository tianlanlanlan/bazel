#include "common/math/vec2d.h"
#include "framework/component_interface.h"
#include <iostream>
#include <memory>

extern "C" {
void init() {
  std::cout << "libnode.so init" << std::endl;

  // 创建组件工厂实例
  std::unique_ptr<ComponentInterface> ptr =
      ComFactory::Instance()->Create("PlanningComponent");
  ptr->Init();
  ptr->Proc();

  apollo::common::math::Vec2d vec(3.0, 4.0);
  std::cout << "Vec2d length: " << vec.Length() << std::endl;
}
}