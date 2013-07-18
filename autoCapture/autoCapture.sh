#!/bin/bash
CMD_OPENTOUCH=$1
CMD_OPENTOUCH_DECIMAL=${1}.decimal
CMD_CAPTURE_DOWN=$2
CMD_CAPTURE_UP=$3
TOUCHDEVICE="/dev/input/event4"
#set -x
send_cmd()
{
	while read cmd
	do
		adb shell "sendevent ${TOUCHDEVICE} $cmd"
	done < $1
}
hexToDecimal()
{
dos2unix $1
	while read line
	do
		for data in $line
		do
			echo -n -e $((0x$data))  "\t" >>$1.decimal
		done
		echo >> $1.decimal
	done < $1
}
fastCapture()
{
	send_cmd $1
	sleep 5
	send_cmd $2
}
hexToDecimal $CMD_OPENTOUCH
hexToDecimal $CMD_CAPTURE_DOWN
hexToDecimal $CMD_CAPTURE_UP

#open camera
send_cmd $CMD_OPENTOUCH.decimal
sleep 5
rm $CMD_OPENTOUCH.decimal
#start capture
n=0
i=0
while true;do
	echo "fastCapture count:$n"
	fastCapture $CMD_CAPTURE_DOWN.decimal $CMD_CAPTURE_UP.decimal
	((n+=1))
	((i+=1))
	if [ $i -gt 5 ];then
		i=0
		adb shell "rm -r /storage/sdcard0/DCIM"
		echo "rm -r /storage/sdcard0/DCIM"
	fi
	sleep 10
done
rm *.decimal
#set +x
