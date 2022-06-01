#!/bin/bash

DIRNAME=$(dirname "$0")
CURRENT=$(cd "$DIRNAME" || exit 1;pwd)

pushd "$CURRENT/../../" || exit 1

cleanup() {
    popd || exit 1
}

# read cmake_binary_dir.txt
BUILD_DIR=""
while read -r LINE
do
    BUILD_DIR="$BUILD_DIR$LINE"
done < cmake_binary_dir.txt

echo BUILD_DIR="$BUILD_DIR"
pushd "$BUILD_DIR" || exit 1

ctest "$@"

popd || exit 1

cleanup || exit 1
