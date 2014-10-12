NDK_ROOT=~/Android/android-ndk-r9
OPENBIZ_ROOT=~/Workspace/GAPP_Project/GAPP_Project/openbiz-rest-model
NDK_MODULE_PATH=${OPENBIZ_ROOT}/openbiz:${OPENBIZ_ROOT}/external/curl/prebuilt/android
APP_ANDROID_ROOT=${OPENBIZ_ROOT}/build/proj.android
"$NDK_ROOT"/ndk-build -C ${APP_ANDROID_ROOT} -j8  NDK_MODULE_PATH=${NDK_MODULE_PATH} $1