#------------------------------------------------------------------------------
# <copyright file="makefile" company="Atheros">
#    Copyright (c) 2005-2008 Atheros Corporation.  All rights reserved.
# $ATH_LICENSE_HOSTSDK0_C$
#------------------------------------------------------------------------------
#==============================================================================
# Author(s): ="Atheros"
#==============================================================================
CC :=$(ATH_CROSS_COMPILE_TYPE)gcc
KERNEL_SRC :=$(ATH_LINUXPATH)
USERF_FLAGS=
PAL_OBJ=
PAL_INTF_LIB=
INCLUDE_THREAD=
APP=wmiconfig

ifeq ($(KF_MEMORY_NEW_ARCH),1)
USERF_FLAGS += -DAR6006_MEMORY_NEW_ARCH
endif

all:
	$(CC) -Wall $(USERF_FLAGS) -DUSER_KEYS -g -I$(KERNEL_SRC)/include -I../../include -I../../../include -I../../wlan/include -I../../os/linux/include wmiconfig.c $(PAL_INTF_LIB)  -o $(APP) $(INCLUDE_THREAD)

clean:
	$(RM) $(APP)
