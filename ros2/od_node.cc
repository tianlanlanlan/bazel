#include "ros2/od_node.h"

OdNode::OdNode() : Node("od_node") {
  RCLCPP_INFO(this->get_logger(), "OdNode started");
  timer_ = this->create_wall_timer(
      std::chrono::milliseconds(100),
      std::bind(&OdNode::timer_callback, this));
}

void OdNode::timer_callback() {
  // Odometry processing logic
}
