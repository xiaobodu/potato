LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_PATH := ../../../../../
CODE_PATH := $(ROOT_PATH)/code/

REAL_ROOT_PATH := $(LOCAL_PATH)/../../../../../
REAL_CODE_PATH := $(REAL_ROOT_PATH)/code/

LOCAL_MODULE    		:= script
LOCAL_CFLAGS 			:= -Wall -fPIC -DBUILD_ANDROID -DBUILD_DEBUG

LOCAL_CPP_FEATURES 		:= rtti exceptions

LOCAL_C_INCLUDES 		:= $(REAL_CODE_PATH)/potato/src
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src/engine
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/external/tinycc

LOCAL_SRC_FILES 		:= $(CODE_PATH)/potato/src/support/script_tcc/script.cpp

LOCAL_LDLIBS    		:= -ldl -llog

LOCAL_SHARED_LIBRARIES := libstlport_static
LOCAL_STATIC_LIBRARIES := libtinycc

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/stlport)
$(call import-module,external/tinycc)
