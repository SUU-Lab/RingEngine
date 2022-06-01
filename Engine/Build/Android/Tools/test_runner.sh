#!/bin/bash

#set -eu -o pipefail
#trap 'echo "ERROR: line no = $LINENO, exit status = $?" >&2; exit 1' ERR

DIRNAME=$(dirname "$0")
CURRENT=$(cd "$DIRNAME" || exit 1;pwd)

pushd "$CURRENT" > log.txt || exit 1

cleanup() {
    rm -rf "TestResult/$TARGET_TEST_FILENAME"
    popd >> log.txt || exit 1
}

if [ ! -d "TestResult" ]; then
    mkdir "TestResult"
fi

TEST_EXECUTABLE_FILE=$1
TARGET_TEST_FILENAME=$(basename "$1")

SUCCEEDED_FILENAME=$TARGET_TEST_FILENAME_SUCCEEDED.txt
DST_DIR=/data/local/tmp/ring/$TARGET_TEST_FILENAME

shift

ARGS=$1
while [ "$1" != "" ]
do
    shift
    ARGS="$ARGS $1"
done

echo "SHELL=$SHELL" >> log.txt
echo "ARGS=$ARGS" >> log.txt

cp "$TEST_EXECUTABLE_FILE" .

{

adb push "$TARGET_TEST_FILENAME" "$DST_DIR/$TARGET_TEST_FILENAME"

adb shell "cd $DST_DIR && chmod 775 ./$TARGET_TEST_FILENAME"

adb shell "cd $DST_DIR && ./$TARGET_TEST_FILENAME $ARGS > output.txt && touch $SUCCEEDED_FILENAME"

adb shell ls "/data/local/tmp/ring"

adb pull "$DST_DIR/" "TestResult"

adb shell rm -rf "$DST_DIR"

} >> log.txt


cat "TestResult/$TARGET_TEST_FILENAME/output.txt"

if [ ! -e "TestResult/$TARGET_TEST_FILENAME/$SUCCEEDED_FILENAME" ]; then
    cleanup && exit 1
else
    cleanup && exit 0
fi
