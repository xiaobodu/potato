LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_PATH := ../../../../../
CODE_PATH := $(ROOT_PATH)/code/

REAL_ROOT_PATH := $(LOCAL_PATH)/../../../../../
REAL_CODE_PATH := $(REAL_ROOT_PATH)/code/

LOCAL_MODULE    		:= display_android_gles
LOCAL_CFLAGS 			:= -Wall -fPIC -DBUILD_ANDROID

LOCAL_SRC_FILES 		:= $(CODE_PATH)/potato/src/support/display_android_gles/display_android_gles.cpp

LOCAL_LDLIBS    		:= -llog -landroid -lEGL

LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src/engine
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/external/rapidjson/include

LOCAL_SHARED_LIBRARIES := libstlport_static
LOCAL_STATIC_LIBRARIES := cpufeatures android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/stlport)
$(call import-module,android/cpufeatures)
$(call import-module,android/native_app_glue)
