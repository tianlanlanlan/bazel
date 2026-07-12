#pragma once

#include <rclcpp/rclcpp.hpp>

class OdNode : public rclcpp::Node {
 public:
  OdNode();
  ~OdNode() override = default;

 private:
  void timer_callback();
  rclcpp::TimerBase::SharedPtr timer_;
};
