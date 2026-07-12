#include "mem_info_utils.h"

#include <cstdint>
#include <iostream>
#include <mutex>

#include "common/log/log.h"

bool PrintSmapsInfo() {
    static std::once_flag flag;
    std::call_once(flag, []() {
        AINFO << "指标说明:";
        AINFO << "USS - 进程独占内存 (最准确的内存占用)";
        AINFO << "PSS - 按比例计算的共享内存";
        AINFO << "RSS - 实际物理内存 (包含共享库)";
    });

    std::ifstream file("/proc/self/smaps");
    if (!file.is_open()) {
        AERROR << "无法打开 /proc/self/smaps";
        return false;
    }

    std::string line;
    uint64_t private_clean = 0, private_dirty = 0;
    uint64_t shared_clean = 0, shared_dirty = 0;
    uint64_t pss_value = 0;
    uint64_t rss_value = 0;

    while (std::getline(file, line)) {
        // 解析私有干净内存
        if (line.find("Private_Clean:") == 0) {
            private_clean += std::stoul(line.substr(14));
        }
        // 解析私有脏内存
        else if (line.find("Private_Dirty:") == 0) {
            private_dirty += std::stoul(line.substr(14));
        }
        // 解析共享干净内存
        else if (line.find("Shared_Clean:") == 0) {
            shared_clean += std::stoul(line.substr(13));
        }
        // 解析共享脏内存
        else if (line.find("Shared_Dirty:") == 0) {
            shared_dirty += std::stoul(line.substr(13));
        }
        // 解析PSS
        else if (line.find("Pss:") == 0) {
            pss_value += std::stoul(line.substr(4));
        }
        // 解析RSS
        else if (line.find("Rss:") == 0) {
            rss_value += std::stoul(line.substr(4));
        }
    }

    // 计算USS：私有内存总和[citation:8]
    MemoryStats stats;
    stats.uss_kb = private_clean + private_dirty;
    stats.pss_kb = pss_value; // PSS已经按比例计算好了[citation:1]
    stats.rss_kb = rss_value; // RSS是实际物理内存[citation:1]
    (void)shared_clean;
    (void)shared_dirty;

    AINFO << "内存统计 (KB):";
    AINFO << "USS: " << stats.uss_kb << " KB";
    AINFO << "PSS: " << stats.pss_kb << " KB";
    AINFO << "RSS: " << stats.rss_kb << " KB";

    return true;
}