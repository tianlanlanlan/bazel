#!/bin/bash
set -ex

test_build() {

    g++ src/main.cc -o main -fsanitize=address -g \
        -fuse-ld=gold \
        -B/usr/bin \
        -Wl,-no-as-needed \
        -Wl,-z,relro,-z,now \
        -pass-exit-codes \
        -fsanitize=address \
        -lasan \
        -Wl,--push-state,-as-needed \
        -lstdc++ \
        -Wl,--pop-state \
        -Wl,--push-state,-as-needed \
        -lm \
        -Wl,--pop-state
}

test_log() {
    printf $(
        tput setaf 2
        tput bold
    )'color show\n\n'$(tput sgr0)

    for ((i = 0; i <= 7; i++)); do
        echo $(tput setaf $i)"show me the money"$(tput sgr0)
    done

    printf '\n'$(
        tput setaf 2
        tput setab 0
        tput bold
    )'background color show'$(tput sgr0)'\n\n'

    for ((i = 0, j = 7; i <= 7; i++, j--)); do
        echo $(
            tput setaf $i
            tput setab $j
            tput bold
        )"show me the money"$(tput sgr0)
    done
}

cross_build() {
    bazel build main --platforms=:rpi
    bazel run --platforms=:rpi install -- "$(pwd)/output"
}

gen_log() {
    #!/bin/bash
    set -euo pipefail

    # 获取项目根目录
    PROJECT_ROOT=$(dirname "$(readlink -f "$0")")

    # 构建日志生成目标
    echo "构建日志生成目标..."
    bazel build //test:gen_log

    # 获取Bazel输出目录
    BAZEL_BIN=$(bazel info bazel-bin)

    # 拷贝生成的文件到项目根目录
    src_dir="${BAZEL_BIN}/test"
    dst_dir="${PROJECT_ROOT}/test"
    cp -f "${src_dir}/log.h" "${dst_dir}/log.h"
    cp -f "${src_dir}/log.cc" "${dst_dir}/log.cc"

}

gen_log
