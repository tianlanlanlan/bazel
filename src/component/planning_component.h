#include "framework/component_interface.h"
#include "framework/component_macro.h"

class PlanningComponent : public ComponentInterface {
public:
  bool Init() override;
};

// 注册组件到工厂
REGISTER_COMPONENT(PlanningComponent);