MY_LOCAL_PATH := $(call my-dir)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(LOCAL_PATH)/potato/Android.mk

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(LOCAL_PATH)/engine/Android.mk

LOCAL_PATH := $(MY_LOCAL_PATH)
include $(LOCAL_PATH)/support/Android.mk


#LOCAL_MODULE    		:= potato
#LOCAL_CFLAGS 			:= -Wall -g -fPIC -DBUILD_ANDROID

#LOCAL_SRC_FILES 		:= potato.cpp

#LOCAL_LDLIBS    		:= -llog -landroid -lEGL -lGLESv1_CM

#LOCAL_C_INCLUDES 		:= 

#LOCAL_SHARED_LIBRARIES := libstlport_static
#LOCAL_STATIC_LIBRARIES := android_native_app_glue

#include $(BUILD_SHARED_LIBRARY)

#$(call import-module,cxx-stl/stlport)
#$(call import-module,android/native_app_glue)
