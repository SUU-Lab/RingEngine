#!/bin/bash

DIRNAME=$(dirname "$0")
CURRENT=$(cd "$DIRNAME" || exit 1;pwd)

pushd "$CURRENT/../$1" > test_log.txt || exit 1

cleanup() {
    popd >> test_log.txt || exit 1
}

# read cmake_binary_dir.txt
BUILD_DIR=""
while read -r LINE
do
    BUILD_DIR="$BUILD_DIR$LINE"
done < cmake_binary_dir.txt

echo BUILD_DIR="$BUILD_DIR" >> test_log.txt

pushd "$BUILD_DIR" >> test_log.txt || exit 1

shift
ctest "$@"

popd >> test_log.txt || exit 1

cleanup || exit 1

exit 0
