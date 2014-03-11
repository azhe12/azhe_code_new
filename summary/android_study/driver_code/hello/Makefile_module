.PHONY:all clean

#KERNEL_DIR:=/home/azhe/work/android/z4dtg_shep_local/kernel/
KERNEL_DIR:=/home/azhe/work/android/android_original/goldfish
CROSS_COMPILE:=arm-eabi-
CC:=$(CROSS_COMPILE)gcc
TARGET:=hello.ko

obj-m:=hello.o

modules:
	$(MAKE)  -C $(KERNEL_DIR) M=$(shell pwd) modules

clean:
	rm -rf $(TARGET) *.mod.c *.mod.o *.o *.order *.symvers .*.cmd .*.mod.o.d .tmp_versions/
