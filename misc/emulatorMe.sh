#!/bin/bash

ANDROID_IMG_DIR=/home/azhe/work/android/android_original/out/target/product/generic
KERNEL_DIR=/home/azhe/work/android/android_original/goldfish
KERNEL_IMG=$KERNEL_DIR/arch/arm/boot/zImage
set -x
emulator -kernel $KERNEL_IMG        \
        -sysdir $ANDROID_IMG_DIR    \
        -system $ANDROID_IMG_DIR/system.img \
        -data $ANDROID_IMG_DIR/userdata.img \
        -ramdisk $ANDROID_IMG_DIR/ramdisk.img   \
        -partition-size 1024    \
        -memory 1024            \
        -skindir /home/azhe/Downloads/adt-bundle-linux-x86_64-20130219/sdk/platforms/android-17/skins \
        -skin WVGA800


set +x
