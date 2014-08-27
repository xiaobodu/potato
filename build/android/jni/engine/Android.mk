LOCAL_PATH := $(call my-dir)

ROOT_PATH := $(LOCAL_PATH)/../../../../
CODE_PATH := $(ROOT_PATH)/code/

LOCAL_MODULE    		:= engine
LOCAL_CFLAGS 				+= -Wall

LOCAL_SRC_FILES 		:= $(CODE_PATH)/potato/src/engine/engine.cpp\
                       $(CODE_PATH)//potato/src/utility/thread.cpp\
                       $(CODE_PATH)/potato/src/utility/util_dl.cpp

LOCAL_LDLIBS    		:= -ldl

LOCAL_C_INCLUDES 		+= $(CODE_PATH)/potato/inc
LOCAL_C_INCLUDES 		+= $(CODE_PATH)/potato/src
LOCAL_C_INCLUDES 		+= $(CODE_PATH)/potato/src/engine
LOCAL_C_INCLUDES 		+= $(CODE_PATH)/external/rapidjson/include

LOCAL_SHARED_LIBRARIES := libstlport_static
#LOCAL_SHARED_LIBRARIES := libstlport_shared

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/stlport)
