#include "framework/component_interface.h"

#include "src/framework/registerer.h"

class PlanningComponent : public ComponentInterface {
  public:
    bool Init() override;
    bool Proc() override;

    REGISTER("PlanningComponent", ComponentInterface);
};

#if 0
#include <iostream>
#define REGISTER_COMPONENT(COMPONENT_CLASS)                                                                            \
    bool COMPONENT_CLASS##_registered_ = []() {                                                                        \
        ComFactory::Instance()->RegisterComponent(#COMPONENT_CLASS,                                                    \
                                                  []() { return std::make_unique<COMPONENT_CLASS>(); });               \
        return true;                                                                                                   \
    }()

REGISTER_COMPONENT(PlanningComponent);
#endif