#!/bin/bash
CODE_DIR=/home/azhe/work/android/android_original/
SYS_OUT_DIR=$CODE_DIR/out/target/product/generic
KERNEL_DIR=$CODE_DIR/goldfish
EMULATOR_DIR=$CODE_DIR/emulator_azhe
DATA_DIR=$EMULATOR_DIR/data
test ! -d $DATA_DIR && mkdir -p $DATA_DIR

emulator-arm -partition-size 2047					\
		-memory 1024								\
		-skin 480x800								\
		-kernel $KERNEL_DIR/arch/arm/boot/zImage	\
		-system $SYS_OUT_DIR/system.img				\
		-sysdir $SYS_OUT_DIR						\
		-data $SYS_OUT_DIR/userdata.img				\
		-datadir $DATA_DIR							\
		-ramdisk $SYS_OUT_DIR/ramdisk.img			\
		-debug-init									\
		-shell-serial stdio	\
		-verbose	\
		-show-kernel
		
	#	-qemu qemu.gles=0 qemu=1 console=/dev/pts/2 \
#			android.qemud=ttyS1 android.checkjni=1 ndns=1
