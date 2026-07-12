#pragma once

#include <rclcpp/rclcpp.hpp>

class OCCNode : public rclcpp::Node {
 public:
  OCCNode();
  ~OCCNode() override = default;

 private:
  void timer_callback();
  rclcpp::TimerBase::SharedPtr timer_;
};
