LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_PATH := ../../../../../
CODE_PATH := $(ROOT_PATH)/code/

REAL_ROOT_PATH := $(LOCAL_PATH)/../../../../../
REAL_CODE_PATH := $(REAL_ROOT_PATH)/code/

LOCAL_MODULE    		:= render_gles
LOCAL_CFLAGS 				:= -Wall -g -DBUILD_ANDROID

LOCAL_SRC_FILES 		:= $(CODE_PATH)/potato/src/support/render_gles/render_gles.cpp

LOCAL_LDLIBS    		:= -lEGL -lGLESv1_CM

LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src/engine

LOCAL_SHARED_LIBRARIES := libstlport_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/stlport)
