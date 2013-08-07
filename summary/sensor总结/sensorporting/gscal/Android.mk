#
# HTC Corporation Proprietary Rights Acknowledgment
#
# Copyright (C) 2008-2011 HTC Corporation
#
# All Rights Reserved.
#
# The information contained in this work is the exclusive property of HTC Corporation
# ("HTC").  Only the user who is legally authorized by HTC ("Authorized User") has
# right to employ this work within the scope of this statement.  Nevertheless, the
# Authorized User shall not use this work for any purpose other than the purpose
# agreed by HTC.  Any and all addition or modification to this work shall be
# unconditionally granted back to HTC and such addition or modification shall be
# solely owned by HTC.  No right is granted under this statement, including but not
# limited to, distribution, reproduction, and transmission, except as otherwise
# provided in this statement.  Any other usage of this work shall be subject to the
# further written consent of HTC.
#

#ifeq ($(findstring "$(HTC_TARGET_PRODUCT)", "passion" "passionc"),)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ifeq (test,test)
LOCAL_SRC_FILES := main.c \
	FileIO.c \
	IOMessage.c \
	$(NULL)
else
LOCAL_SRC_FILES := lib_test.c
endif

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libcutils \
	libstdc++ \
	libc \
	$(NULL)

LOCAL_MODULE := htcgscal

LOCAL_MODULE_TAGS := $(HTC_TAGS)

LOCAL_MODULE_PATH := $(HTC_SSD_OUT_BIN)

include $(SSD_BUILD_DAEMON)

endif

