LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../)

LOCAL_MODULE := openbiz_shared

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := openbizJNI.cpp

LOCAL_MODULE_FILENAME := libopenbiz

LOCAL_WHOLE_STATIC_LIBRARIES := openbiz_static
LOCAL_WHOLE_STATIC_LIBRARIES += openbiz_external_static

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)

#==============================================================

$(call import-module,openbiz)
$(call import-module,external/curl/prebuilt/android)
$(call import-module,external/zlib/prebuilt/android)
$(call import-module,external/sqlite3/prebuilt/android)