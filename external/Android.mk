LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := openbiz_external_static

LOCAL_MODULE_FILENAME := libopenbiz_ext_static

LOCAL_SRC_FILES := \
					sqlite3/source/shell.c \
					sqlite3/source/sqlite3.c \
					jsoncpp/source/lib_json/json_reader.cpp \
					jsoncpp/source/lib_json/json_value.cpp \
					jsoncpp/source/lib_json/json_writer.cpp \
					restclient-cpp/source/restclient.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
					$(LOCAL_PATH)/../openbiz \
					$(LOCAL_PATH)/../openbiz/platform \
					$(LOCAL_PATH)/sqlite3/include  \
					$(LOCAL_PATH)/jsoncpp/include  \
					$(LOCAL_PATH)/curl/include/android  \
					$(LOCAL_PATH)/restclient-cpp/include/restclient-cpp  


LOCAL_EXPORT_C_INCLUDES := \
					$(LOCAL_PATH)/sqlite3/include  \
					$(LOCAL_PATH)/jsoncpp/include/json  \
					$(LOCAL_PATH)/curl/include/android  \
					$(LOCAL_PATH)/restclient-cpp/include/restclient-cpp  

LOCAL_WHOLE_STATIC_LIBRARIES := openbiz_internal_static
LOCAL_WHOLE_STATIC_LIBRARIES += openbiz_zlib_static
LOCAL_WHOLE_STATIC_LIBRARIES += openbiz_curl_static

include $(BUILD_STATIC_LIBRARY)

