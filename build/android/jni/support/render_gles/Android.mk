LOCAL_PATH := $(call my-dir)

ROOT_PATH := $(LOCAL_PATH)/../../../../../
CODE_PATH := $(ROOT_PATH)/code/

LOCAL_MODULE    		:= render_gles
LOCAL_CFLAGS 				+= -Wall

LOCAL_SRC_FILES 		:= $(CODE_PATH)/potato/src/support/render_gles/render_gles.cpp

LOCAL_LDLIBS    		:= -lEGL -lGLESv1_CM

LOCAL_C_INCLUDES 		+= $(CODE_PATH)/potato/src
LOCAL_C_INCLUDES 		+= $(CODE_PATH)/potato/src/engine

LOCAL_SHARED_LIBRARIES := libstlport_static
#LOCAL_SHARED_LIBRARIES := libstlport_shared

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/stlport)
