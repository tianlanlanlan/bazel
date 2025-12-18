#!/bin/bash
set -ex

readonly current_script_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
readonly install_dir="$(pwd)/output"
readonly build_dir="$(pwd)/output"

rm -rf $install_dir $build_dir

bash autogen.sh
mkdir $build_dir
cd $build_dir
../configure --enable-libunwind=no --enable-frame-pointers=yes --prefix=$install_dir
make -j 8
make install
