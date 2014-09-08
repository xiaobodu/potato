LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

ROOT_PATH := $(LOCAL_PATH)/../../../../../
CODE_PATH := $(ROOT_PATH)/code/

LOCAL_MODULE    		:= png
LOCAL_CFLAGS 			:= -Wall -fPIC -DBUILD_ANDROID -DPNG_CONFIGURE_LIBPNG -DLIBPNG_NO_MMX -DPNG_NO_MMX_CODE -DZLIB_DLL -DPNG_NO_FLOATING_POINT_SUPPORTED

#LOCAL_CPP_FEATURES 		:= rtti exceptions

LOCAL_C_INCLUDES 		+= $(CODE_PATH)/external/libpng

LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/png.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngerror.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngget.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngmem.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngpread.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngread.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngrio.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngrtran.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngrutil.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngset.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngtrans.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngwio.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngwrite.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngwtran.c
LOCAL_SRC_FILES                 += $(CODE_PATH)/external/libpng/pngwutil.c

#LOCAL_LDLIBS := -lz

LOCAL_EXPORT_C_INCLUDES := $(CODE_PATH)/external/libpng
LOCAL_EXPORT_LDLIBS     := -lz


include $(BUILD_STATIC_LIBRARY)

