#include "ros2/occ_node.h"

OCCNode::OCCNode() : Node("occ_node") {
  RCLCPP_INFO(this->get_logger(), "OCCNode started");
  timer_ = this->create_wall_timer(
      std::chrono::milliseconds(100),
      std::bind(&OCCNode::timer_callback, this));
}

void OCCNode::timer_callback() {
  // Occupancy grid processing logic
}
