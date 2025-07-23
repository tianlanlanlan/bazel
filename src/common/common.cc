#include "common.h"
#include "status.pb.h"
// #include "perf_info.pb.h"

void common(void) {
  Status status;
  status.set_name("tianlan");
  status.set_id(12345);
  status.set_email("123@.com");
  std::cout << "Debug: " << status.DebugString();
  std::cout << "Debug: " << status.DebugString();
  std::cout << "Debug: " << status.DebugString();
  std::cout << "Debug: " << status.DebugString();
  std::cout << "Debug: " << status.DebugString();

  // PerfInfo proto;
}