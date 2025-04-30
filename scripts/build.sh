#!/bin/sh

# Parse command-line arguments
BUILD_TYPE="debug"

while [[ "$1" != "" ]]; do
    case $1 in
        --debug )   BUILD_TYPE="debug"
                    ;;
        --release ) BUILD_TYPE="release"
                    ;;
        * )         echo "Usage: $0 [--debug | --release]"
                    exit 1
    esac
    shift
done

echo "Building in $BUILD_TYPE mode..."

INITIAL_DIR=$(pwd)
SCRIPT_DIR="$(dirname "$0")"
cd "$SCRIPT_DIR/.."

mkdir -p build
mkdir -p dist

cd build

if [ "$BUILD_TYPE" == "debug" ]; then
    emcmake cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_EXE_LINKER_FLAGS="--emrun --preload-file ../assets --use-preload-plugins" ..
else
    emcmake cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_EXE_LINKER_FLAGS="--preload-file ../assets --use-preload-plugins" ..
fi

[ -L ../compile_commands.json ] || ln -s compile_commands.json ../compile_commands.json
cmake --build .

cd "$INITIAL_DIR"
