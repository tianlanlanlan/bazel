#pragma once

#include <rclcpp/rclcpp.hpp>

class SparseOneModelNode : public rclcpp::Node {
 public:
  SparseOneModelNode();
  ~SparseOneModelNode() override = default;

 private:
  void timer_callback();
  rclcpp::TimerBase::SharedPtr timer_;
};
