MY_LOCAL_EXTERNAL_PATH := $(call my-dir)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_PATH := $(MY_LOCAL_EXTERNAL_PATH)
include $(LOCAL_PATH)/libpng/Android.mk

