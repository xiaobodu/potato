LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_PATH := ../../../../../
CODE_PATH := $(ROOT_PATH)/code/

REAL_ROOT_PATH := $(LOCAL_PATH)/../../../../../
REAL_CODE_PATH := $(REAL_ROOT_PATH)/code/

LOCAL_MODULE    := t001
LOCAL_CFLAGS    := -g -Wall
LOCAL_SRC_FILES := ../t001.cpp
LOCAL_LDLIBS    := -llog

LOCAL_C_INCLUDES       += $(REAL_CODE_PATH)/potato/inc

LOCAL_STATIC_LIBRARIES := potato

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/stlport)
