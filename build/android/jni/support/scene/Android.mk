LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_PATH := ../../../../../
CODE_PATH := $(ROOT_PATH)/code/

REAL_ROOT_PATH := $(LOCAL_PATH)/../../../../../
REAL_CODE_PATH := $(REAL_ROOT_PATH)/code/

LOCAL_MODULE    		:= scene
LOCAL_CFLAGS 			:= -Wall -fPIC -DBUILD_ANDROID -DBUILD_DEBUG

LOCAL_CPP_FEATURES 		:= rtti exceptions

LOCAL_C_INCLUDES 		:= $(REAL_CODE_PATH)/potato/src
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/potato/src/engine
LOCAL_C_INCLUDES 		+= $(REAL_CODE_PATH)/external/rapidjson/include

LOCAL_SRC_FILES 		:= $(CODE_PATH)/potato/src/support/scene/scene.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/scene/math.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/scene/builder.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/scene/layout.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/scene/widget.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/scene/panel.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/scene/image.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/support/scene/effect.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/engine/input.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/engine/sensor.cpp
LOCAL_SRC_FILES 		+= $(CODE_PATH)/potato/src/utility/sharedlibrary.cpp

LOCAL_LDLIBS    		:= -ldl -llog

LOCAL_SHARED_LIBRARIES := libstlport_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cxx-stl/stlport)
