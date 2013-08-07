KERNEL_DIR = /home/azhe/work/multi-git/protd/gep/kernel/
CMD = $(shell pwd)
ARCH = arm
CROSS_COMPILE = arm-eabi-
AS          	=$(CROSS_COMPILE)as 
LD              = $(CROSS_COMPILE)ld
CC              = $(CROSS_COMPILE)gcc
CPP             = $(CC) -E
AR              = $(CROSS_COMPILE)ar
NM              = $(CROSS_COMPILE)nm
STRIP           = $(CROSS_COMPILE)strip
export CROSS_COMPILE AS LD CC CPP AR NM STRIP ARCH

obj-m = tty_azhe.o
tty_azhe-objs = main.o
default:
	$(MAKE) -C $(KERNEL_DIR) M=$(CMD) modules 

#	echo $(CROSS_COMPILE)
clean:
	rm -rf *.o  .*.cmd *.ko *.mod.c  modules.order  Module.symvers

