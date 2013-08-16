#!/bin/bash
set -x
CMD_SCREEN_SHOT="screenshot"
TOP=$(pwd)
TARGET_SAVE_DIR="/data/screenShot"
HOST_SAVE_DIR=$TOP/screenShot
num=0
adb shell "mkdir $TARGET_SAVE_DIR" 
while true
do
	echo $((num+=1))
	PNG=screenShot_$(date "+%H%M%S").png
	adb shell "cd $TARGET_SAVE_DIR;$CMD_SCREEN_SHOT $PNG" 
	adb pull $TARGET_SAVE_DIR $HOST_SAVE_DIR
	adb shell "cd $TARGET_SAVE_DIR;rm *"
done
set +x
