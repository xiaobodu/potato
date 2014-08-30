LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := t001
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := t001.cpp
LOCAL_LDLIBS    := -llog

LOCAL_SHARED_LIBRARIES := libstlport_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/stlport)
