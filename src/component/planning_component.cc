#include "planning_component.h"
#include <cstdio>

#include "perf_info.pb.h"

#include "common/math/vec2d.h"

bool PlanningComponent::Init() {
  printf("PlanningComponent::Init() called\n");

  PerfInfo proto;
  proto.set_duration_ms(100.0);
  printf("%s\n", proto.DebugString().c_str());

  apollo::common::math::Vec2d vec(1.0, 2.0);
  vec.set_x(3.0);
  vec.set_y(4.0);
  printf("Vec2d: %s\n", vec.DebugString().c_str());

  return true;
}
