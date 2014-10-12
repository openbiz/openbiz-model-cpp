LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := openbiz_zlib_static
LOCAL_MODULE_FILENAME := z
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libz.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include/android
include $(PREBUILT_STATIC_LIBRARY)
