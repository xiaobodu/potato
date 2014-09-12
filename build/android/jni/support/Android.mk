MY_LOCAL_SUPPORT_PATH := $(call my-dir)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_PATH := $(MY_LOCAL_SUPPORT_PATH)
include $(LOCAL_PATH)/display_gles/Android.mk

LOCAL_PATH := $(MY_LOCAL_SUPPORT_PATH)
include $(LOCAL_PATH)/render_gles/Android.mk

LOCAL_PATH := $(MY_LOCAL_SUPPORT_PATH)
include $(LOCAL_PATH)/asset/Android.mk

LOCAL_PATH := $(MY_LOCAL_SUPPORT_PATH)
include $(LOCAL_PATH)/scene/Android.mk

LOCAL_PATH := $(MY_LOCAL_SUPPORT_PATH)
include $(LOCAL_PATH)/script_tcc/Android.mk

LOCAL_PATH := $(MY_LOCAL_SUPPORT_PATH)
