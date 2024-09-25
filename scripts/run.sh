#!/bin/sh

initial_dir=$(pwd)
script_dir="$(dirname "$0")"
cd "$script_dir/.."

mkdir -p build
mkdir -p dist

cd build

emcmake cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXE_LINKER_FLAGS="--emrun" ..
cmake --build .

cd "$initial_dir"

emrun "$script_dir/../dist/index.html"
