LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_PATH := ../../../../
CODE_PATH := $(ROOT_PATH)/code/

REAL_ROOT_PATH := $(LOCAL_PATH)/../../../../
REAL_CODE_PATH := $(REAL_ROOT_PATH)/code/

LOCAL_MODULE    		:= t001
LOCAL_CFLAGS    		:= -Wall -DBUILD_ANDROID -g

LOCAL_CPP_FEATURES 		:= rtti exceptions

LOCAL_SRC_FILES 		+= $(ROOT_PATH)/build/android/jni/potato/jni_potato.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/potato.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/utility/util_dl.cpp
LOCAL_SRC_FILES 		+= t001.cpp

LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/inc
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src/utility
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src/engine
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/external/rapidjson/include

LOCAL_LDLIBS    		:= -ldl -llog -landroid

LOCAL_STATIC_LIBRARIES 	:= android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/stlport)
$(call import-module,android/native_app_glue)
