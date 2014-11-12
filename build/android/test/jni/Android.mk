LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_PATH := ../../../../
CODE_PATH := $(ROOT_PATH)/code/

REAL_ROOT_PATH := $(LOCAL_PATH)/../../../../
REAL_CODE_PATH := $(REAL_ROOT_PATH)/code/

LOCAL_MODULE    		:= test
LOCAL_CFLAGS    		:= -Wall -DBUILD_ANDROID -DBUILD_DEBUG -DCXX_GNU

LOCAL_CPP_FEATURES 		:= rtti exceptions

LOCAL_SRC_FILES 		+= $(ROOT_PATH)/build/android/libpotato/jni/potato/jni_potato.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/potato.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/utility/sharedlibrary.cpp
LOCAL_SRC_FILES 		+= test.cpp

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
