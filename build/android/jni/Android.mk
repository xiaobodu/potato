MY_LOCAL_PATH := $(call my-dir)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(LOCAL_PATH)/potato/Android.mk

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(LOCAL_PATH)/engine/Android.mk

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(LOCAL_PATH)/support/Android.mk
