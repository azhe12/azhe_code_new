CROSS_COMPILE = arm-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)g++

#CC=$(HOME)/opt/arm-eabi-4.4.0/bin/arm-eabi-g++
#LD=$(HOME)/opt/arm-eabi-4.4.0/bin/arm-eabi-g++
CFLAGS= -Wall -O2 -march=armv5te -D__ARM_ARCH_5__ -omit-frame-pointer -fstrict-aliasing

INC_DIR = /home/azhe/other/arm_app/app_s8/include
LIB_DIR = /home/azhe/other/arm_app/app_s8/lib
#INC_DIR=../app_s8/include
#LIB_DIR=../app_s8/lib
STD_INCLUDE= -I $(INC_DIR) -I$(INC_DIR)/kernel -I $(INC_DIR)/kernel/common -I $(INC_DIR)/kernel/arch-arm

TARGET1 = receive
OBJ1 = receive.o
TARGET2 = send
OBJ2 = send.o
CRT-BEGIN = $(LIB_DIR)/crtbegin_dynamic.o
CRT-END = $(LIB_DIR)/crtend_android.o

all: $(TARGET1) $(TARGET2)

clean:
	rm -rf $(OBJ1) $(TARGET1) $(OBJ2) $(TARGET2)
	
$(TARGET1): $(OBJ1)
	$(LD) -g -L$(LIB_DIR) -lc -ldl -Bstatic -Wl,-dynamic-linker,/system/bin/linker -nostdlib -Wl-z,nocopyreloc -Wl,-T$(LIB_DIR)/armelf.x -Wl,--gc-sections $(CRT-BEGIN) $^ $(CRT-END) -o $@
		
$(TARGET2): $(OBJ2)
	$(LD) -g -L$(LIB_DIR) -lc -ldl -Bstatic -Wl,-dynamic-linker,/system/bin/linker -nostdlib -Wl-z,nocopyreloc -Wl,-T$(LIB_DIR)/armelf.x -Wl,--gc-sections $(CRT-BEGIN) $^ $(CRT-END) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -g -c $(STD_INCLUDE) $< -o $@
