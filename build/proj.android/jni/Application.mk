APP_STL := gnustl_static
APP_ABI := armeabi-v7a armeabi x86
APP_CPPFLAGS := -frtti -DANDROID -std=c++11 -fsigned-char -fexceptions -fpermissive -Wno-literal-suffix 
NDK_TOOLCHAIN_VERSION=4.8
APP_USE_CPP0X := true