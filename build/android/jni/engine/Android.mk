LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_PATH := ../../../../
CODE_PATH := $(ROOT_PATH)/code/

REAL_ROOT_PATH := $(LOCAL_PATH)/../../../../
REAL_CODE_PATH := $(REAL_ROOT_PATH)/code/

LOCAL_MODULE    		:= engine
LOCAL_CFLAGS 				:= -Wall -g -fPIC -DBUILD_ANDROID

LOCAL_SRC_FILES 		:= $(CODE_PATH)/potato/src/engine/engine.cpp\
                       $(CODE_PATH)//potato/src/utility/thread.cpp\
                       $(CODE_PATH)/potato/src/utility/util_dl.cpp

LOCAL_LDLIBS    		:= -ldl

LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/inc
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src/engine
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/external/rapidjson/include

LOCAL_SHARED_LIBRARIES := libstlport_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/stlport)
