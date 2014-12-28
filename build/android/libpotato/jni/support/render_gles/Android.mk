LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_PATH := ../../../../../../
CODE_PATH := $(ROOT_PATH)/code/

REAL_ROOT_PATH := $(LOCAL_PATH)/../../../../../../
REAL_CODE_PATH := $(REAL_ROOT_PATH)/code/

LOCAL_MODULE    		:= render
LOCAL_CPPFLAGS 			+= -fPIC -DC4G_API_EXPORT

LOCAL_CPP_FEATURES 		:= rtti exceptions

LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src/engine
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/external/rapidjson/include

LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/render_gles/render.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/render_gles/canvas.cpp
LOCAL_SRC_FILES         += $(CODE_PATH)/potato/src/support/render_gles/camera.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/render_gles/space.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/render_gles/transform.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/render_gles/blend.cpp

LOCAL_LDLIBS    		:= -llog -lGLESv1_CM

LOCAL_SHARED_LIBRARIES := libstlport_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/stlport)
