LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_PATH := ../../../../../
CODE_PATH := $(ROOT_PATH)/code/

REAL_ROOT_PATH := $(LOCAL_PATH)/../../../../../
REAL_CODE_PATH := $(REAL_ROOT_PATH)/code/

LOCAL_MODULE    		:= render_gles
LOCAL_CFLAGS 			:= -Wall -fPIC -DBUILD_ANDROID -DBUILD_DEBUG

LOCAL_CPP_FEATURES 		:= rtti exceptions

LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src/engine
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/external/rapidjson/include

LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/render_gles/render_gles.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/render_gles/canvas_gles.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/render_gles/transform_gles.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/render_gles/blend_gles.cpp

LOCAL_LDLIBS    		:= -llog -lGLESv1_CM

LOCAL_SHARED_LIBRARIES := libstlport_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/stlport)
