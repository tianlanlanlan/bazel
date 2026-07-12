#include <rclcpp/rclcpp.hpp>

#include <memory>

#include "ros2/occ_node.h"
#include "ros2/od_node.h"
#include "ros2/sparse_one_model_node.h"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);

  auto occ_node = std::make_shared<OCCNode>();
  auto od_node = std::make_shared<OdNode>();
  auto sparse_one_model_node = std::make_shared<SparseOneModelNode>();

  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(occ_node);
  executor.add_node(od_node);
  executor.add_node(sparse_one_model_node);

  executor.spin();

  rclcpp::shutdown();
  return 0;
}
