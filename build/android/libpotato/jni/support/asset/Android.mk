LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_PATH := ../../../../../../
CODE_PATH := $(ROOT_PATH)/code/

REAL_ROOT_PATH := $(LOCAL_PATH)/../../../../../../
REAL_CODE_PATH := $(REAL_ROOT_PATH)/code/

LOCAL_MODULE    		:= asset
LOCAL_CFLAGS 			:= -Wall -fPIC -DBUILD_ANDROID -DBUILD_DEBUG -DCXX_GNU -DC4G_API_EXPORT

LOCAL_CPP_FEATURES 		:= rtti exceptions

LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src/engine

LOCAL_SRC_FILES 		:= $(CODE_PATH)/potato/src/support/asset/asset.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/asset/file_png.cpp

LOCAL_LDLIBS    		:= -llog

LOCAL_SHARED_LIBRARIES := libstlport_static
LOCAL_STATIC_LIBRARIES := libpng

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/stlport)

$(call import-module,external/libpng)
