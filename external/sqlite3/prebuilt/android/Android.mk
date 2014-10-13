LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := openbiz_sqlite_static
LOCAL_MODULE_FILENAME := sqlite
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libsqlite.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include/android
include $(PREBUILT_STATIC_LIBRARY)
