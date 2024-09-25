#!/bin/sh

initial_dir=$(pwd)
script_dir="$(dirname "$0")"
cd "$script_dir/.."

mkdir -p build
mkdir -p dist

cd build

emcmake cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .

cd "$initial_dir"
