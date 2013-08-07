#BOARD_VENDOR_USE_AKMKD := akm8975src_pydtd  
#ifeq ($(BOARD_VENDOR_USE_AKMD), akm8975src_pydtd)

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

ifeq (test,test)
LOCAL_SRC_FILES:= main.c \
	AccSensorFunction.c \
	DispMessage.c \
	FileIO.c \
	Measure.c \
	IOMessage.c \
	akmd_slider.c \
#	HDOEProc.c \
	$(NULL)
else
LOCAL_SRC_FILES:= lib_test.c
endif

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libcutils \
	libstdc++ \
	libc \
	$(NULL)
LOCAL_MODULE_TAGS := optional

LOCAL_LDFLAGS := $(LOCAL_PATH)/akmlib/libAK8975.a 

LOCAL_MODULE:= akmd

#LOCAL_MODULE_PATH := $(TARGET_ROOT_OUT_SBIN)
LOCAL_UNSTRIPPED_PATH := $(TARGET_ROOT_OUT_SBIN_UNSTRIPPED)

include $(BUILD_EXECUTABLE)

#endif # ifeq ($(BOARD_VENDOR_USE_AKMD), true)
