#include "ros2/sparse_one_model_node.h"

SparseOneModelNode::SparseOneModelNode() : Node("sparse_one_model_node") {
  RCLCPP_INFO(this->get_logger(), "SparseOneModelNode started");
  timer_ = this->create_wall_timer(
      std::chrono::milliseconds(100),
      std::bind(&SparseOneModelNode::timer_callback, this));
}

void SparseOneModelNode::timer_callback() {
  // Sparse model inference logic
}
