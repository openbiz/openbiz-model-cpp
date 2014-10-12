APP_STL := gnustl_static
APP_ABI := armeabi armeabi-v7a x86
APP_CPPFLAGS := -frtti -DANDROID -std=c++11 -fsigned-char -fexceptions -Wno-literal-suffix
NDK_TOOLCHAIN_VERSION=4.8
APP_USE_CPP0X := true