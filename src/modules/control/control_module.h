#include "framework/component_interface.h"

#include "src/framework/registerer.h"

class ControlModule : public ComponentInterface {
  public:
    bool Init() override;
    bool Proc() override;

    REGISTER("ControlModule", ComponentInterface);
};
