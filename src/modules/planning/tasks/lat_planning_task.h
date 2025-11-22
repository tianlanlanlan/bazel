#include "framework/component_interface.h"

#include "src/framework/registerer.h"

class LatPlanningTask : public TaskInterface {
  public:
    bool Init() override;
    bool Proc() override;

    REGISTER("LatPlanningTask", TaskInterface);
};
