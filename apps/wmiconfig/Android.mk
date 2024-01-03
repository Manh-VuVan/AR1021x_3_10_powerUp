#------------------------------------------------------------------------------
# <copyright file="makefile" company="Atheros">
#    Copyright (c) 2005-2010 Atheros Corporation.  All rights reserved.
# $ATH_LICENSE_HOSTSDK0_C$
#------------------------------------------------------------------------------
#==============================================================================
# Author(s): ="Atheros"
#==============================================================================

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../../include \
    $(LOCAL_PATH)/../../os/linux/include \
    $(LOCAL_PATH)/../../../include \
    $(LOCAL_PATH)/../../wlan/include

LOCAL_CFLAGS+=-DUSER_KEYS
LOCAL_SRC_FILES:= wmiconfig.c
LOCAL_MODULE := wmiconfig
LOCAL_MODULE_TAGS := debug eng optional
LOCAL_CFLAGS += -DATH_ANDROID_ENV
include $(BUILD_EXECUTABLE)


