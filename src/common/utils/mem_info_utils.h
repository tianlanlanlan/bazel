#pragma once

#include <cstdint>
#include <fstream>

struct MemoryStats {
    uint64_t uss_kb = 0; // 私有脏内存 + 私有干净内存
    uint64_t pss_kb = 0; // 比例分配共享内存
    uint64_t rss_kb = 0; // 全部驻留内存
};

bool PrintSmapsInfo();
