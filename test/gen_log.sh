#!/bin/bash
set -euo pipefail
set -x

echo "$@"

# 参数解析
while [[ $# -gt 0 ]]; do
  case $1 in
  --header)
    header_out="$2"
    shift 2
    ;;
  --source)
    source_out="$2"
    shift 2
    ;;
  *)
    echo "Unknown option: $1"
    exit 1
    ;;
  esac
done

# 验证参数
[[ -z "$header_out" ]] && {
  echo "Missing header path"
  exit 1
}
[[ -z "$source_out" ]] && {
  echo "Missing source path"
  exit 1
}

# 生成头文件
cat >"$header_out" <<EOF
#pragma once

void log();
EOF

# 生成源文件
cat >"$source_out" <<EOF
#include "log.h"

void log() {
    // 日志实现
}
EOF
