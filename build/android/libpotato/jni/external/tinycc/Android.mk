LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_PATH := $(LOCAL_PATH)/../../../../../../
CODE_PATH := $(ROOT_PATH)/code/

LOCAL_MODULE    		:= tinycc
LOCAL_CFLAGS 			:= -Wall -fPIC -DBUILD_ANDROID -DTCC_ANDROID -DTCC_ARM_EABI -DTCC_TARGET_ARM -DWITHOUT_LIBTCC

#LOCAL_CPP_FEATURES 		:= rtti exceptions

LOCAL_C_INCLUDES 		+= $(CODE_PATH)/external/tinycc

LOCAL_SRC_FILES                 := $(CODE_PATH)/external/tinycc/libtcc.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/tinycc/tccpp.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/tinycc/tccgen.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/tinycc/tccelf.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/tinycc/tccasm.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/tinycc/tccrun.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/tinycc/tcc.c
#LOCAL_SRC_FILES                 += $(CODE_PATH)/external/tinycc/tcc.h
#LOCAL_SRC_FILES                 += $(CODE_PATH)/external/tinycc/config.h
#LOCAL_SRC_FILES                 += $(CODE_PATH)/external/tinycc/libtcc.h
#LOCAL_SRC_FILES                 += $(CODE_PATH)/external/tinycc/tcctok.h
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/tinycc/arm-gen.c

LOCAL_EXPORT_C_INCLUDES := $(CODE_PATH)/external/tinycc


include $(BUILD_STATIC_LIBRARY)

