LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := openbiz_static

LOCAL_MODULE_FILENAME := libopenbiz_static

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := \
					openbiz.cpp \
					core/DB.cpp \
					core/Object.cpp \
					exception/DataFormatInvalidException.cpp \
					exception/NetworkConnectionException.cpp \
					exception/ServerErrorException.cpp \
					model/DataObject.cpp \
					remote/RemoteDataObject.cpp \
					platform/FileUtils.cpp \
					platform/Android/FileUtils-Android.cpp \
					platform/Android/jni/JniHelper.cpp \
					platform/Android/jni/Java_com_openbiz_lib_OpenbizHelper.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/core \
					$(LOCAL_PATH)/exception \
					$(LOCAL_PATH)/model \
					$(LOCAL_PATH)/remote \
					$(LOCAL_PATH)/platform \
                    $(LOCAL_PATH)/../external/sqlite3/include  \
                    $(LOCAL_PATH)/../external/jsoncpp/include/json  \
                    $(LOCAL_PATH)/../external/curl/include/android  \
                    $(LOCAL_PATH)/../external/restclient-cpp/include/restclient-cpp  

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/core \
					$(LOCAL_PATH)/exception \
					$(LOCAL_PATH)/model \
					$(LOCAL_PATH)/remote \
					$(LOCAL_PATH)/platform \
                    $(LOCAL_PATH)/../external/sqlite3/include  \
                    $(LOCAL_PATH)/../external/jsoncpp/include/json  \
                    $(LOCAL_PATH)/../external/curl/include/android  \
                    $(LOCAL_PATH)/../external/restclient-cpp/include/restclient-cpp  

LOCAL_WHOLE_STATIC_LIBRARIES := openbiz_curl_static
LOCAL_WHOLE_STATIC_LIBRARIES += openbiz_zlib_static
LOCAL_WHOLE_STATIC_LIBRARIES += openbiz_external_static



include $(BUILD_STATIC_LIBRARY)

#==============================================================
$(call import-module,external)

