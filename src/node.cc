#include "framework/component_interface.h"
#include <memory>
#include <iostream>

extern "C" {
void init() {
  std::cout << "libnode.so init" << std::endl;

  // 创建组件工厂实例
  std::unique_ptr<ComponentInterface> ptr =
      ComFactory::Instance()->Create("PlanningComponent");
  ptr->Init();
}
}