/*
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Proprietary and Confidential.
 */

ifeq ($(BOARD_HAS_ATH_WLAN_AR6004_DEV),true)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := artagent

LOCAL_C_INCLUDES += $(TARGET_OUT_HEADERS)/libtcmd \

LOCAL_CFLAGS+= 

LOCAL_SRC_FILES:= \ artagent.c

LOCAL_LDLIBS += -lpthread -lrt

LOCAL_MODULE_TAGS := optional eng

LOCAL_SHARED_LIBRARIES += libcutils
LOCAL_STATIC_LIBRARIES += libtcmd

include $(BUILD_EXECUTABLE)

endif
