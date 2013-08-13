#!/bin/bash
SYSTRACE_PATH=/home/azhe/Downloads/adt-bundle-linux-x86_64-20130219/sdk/tools/systrace
TIME=$1
OUT_FILE=$2
set -x
python $SYSTRACE_PATH/systrace.py --set-tags gfx,view,wm
#echo "python $SYSTRACE_PATH/systrace.py --set-tags gfx,view,wm"
#python $SYSTRACE_PATH/systrace.py --set-tags wm
adb shell stop
sleep 2
adb shell start
echo "Enter any key to continue..."
read i
#echo "python /$SYSTRACE_PATH/systrace.py --disk --time=$TIME -o $OUT_FILE"
python /$SYSTRACE_PATH/systrace.py --disk --time=$TIME -o $OUT_FILE
set +x
