LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../)

LOCAL_MODULE := openbiz_shared

LOCAL_MODULE_FILENAME := libopenbiz

LOCAL_STATIC_LIBRARIES := openbiz_static
LOCAL_SHARED_LIBRARIES := libsqlite

include $(BUILD_SHARED_LIBRARY)
$(call import-module,openbiz)
$(call import-module,external/curl/prebuilt/android)
$(call import-module,external/zlib/prebuilt/android)