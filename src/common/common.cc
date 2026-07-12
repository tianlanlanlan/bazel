#include "common.h"
#include "common/log/log.h"
#include "status.pb.h"
// #include "perf_info.pb.h"

void common(void) {
  Status status;
  status.set_name("tianlan");
  status.set_id(12345);
  status.set_email("123@.com");
  AINFO << "Debug: " << status.DebugString();
  AINFO << "Debug: " << status.DebugString();
  AINFO << "Debug: " << status.DebugString();
  AINFO << "Debug: " << status.DebugString();
  AINFO << "Debug: " << status.DebugString();

  // PerfInfo proto;
}