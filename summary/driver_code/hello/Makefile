.PHONY:all clean

KERNEL_DIR:=/home/azhe/work/android/z4dtg_shep_local/kernel/
CROSS_COMPILE:=arm-eabi-
CC:=$(CROSS_COMPILE)gcc
TARGET:=hello.ko
#OBJ:=hello.ko

#all:hello

#$(TARGET):$(wildcard *.c)
#	$(CC) -m $(TARGET) -C $(KERNEL_DIR)


obj-m:=hello.o

modules:
	$(MAKE)  -C $(KERNEL_DIR) M=$(shell pwd) modules

clean:
	rm -rf $(TARGET) *.mod.c *.mod.o *.o *.order *.symvers .*.cmd .tmp_versions/
