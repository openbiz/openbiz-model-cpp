//
//  PlatformConfig.h
//  libRestModel
//
//  Created by Jixian Wang on 14-10-1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef libRestModel_PlatformConfig_h
#define libRestModel_PlatformConfig_h

// define supported target platform macro which CC uses.
#define BIZ_PLATFORM_UNKNOWN            0
#define BIZ_PLATFORM_IOS                1
#define BIZ_PLATFORM_ANDROID            2
#define BIZ_PLATFORM_WIN32              3
#define BIZ_PLATFORM_MARMALADE          4
#define BIZ_PLATFORM_LINUX              5
#define BIZ_PLATFORM_BADA               6
#define BIZ_PLATFORM_BLACKBERRY         7
#define BIZ_PLATFORM_MAC                8
#define BIZ_PLATFORM_NACL               9
#define BIZ_PLATFORM_EMSCRIPTEN        10
#define BIZ_PLATFORM_TIZEN             11
#define BIZ_PLATFORM_QT5               12
#define BIZ_PLATFORM_WP8               13
#define BIZ_PLATFORM_WINRT             14


#define BIZ_TARGET_PLATFORM             BIZ_PLATFORM_UNKNOWN


// mac
#if defined(BIZ_TARGET_OS_MAC)
#undef  BIZ_TARGET_PLATFORM
#define BIZ_TARGET_PLATFORM         BIZ_PLATFORM_MAC
#endif

// iphone
#if defined(BIZ_TARGET_OS_IOS)
#undef  BIZ_TARGET_PLATFORM
#define BIZ_TARGET_PLATFORM         BIZ_PLATFORM_IOS
#endif

// android
#if defined(ANDROID)
#undef  BIZ_TARGET_PLATFORM
#define BIZ_TARGET_PLATFORM         BIZ_PLATFORM_ANDROID
#endif

// win32
#if defined(WIN32) && defined(_WINDOWS)
#undef  BIZ_TARGET_PLATFORM
#define BIZ_TARGET_PLATFORM         BIZ_PLATFORM_WIN32
#endif

// linux
#if defined(LINUX)
#undef  BIZ_TARGET_PLATFORM
#define BIZ_TARGET_PLATFORM         BIZ_PLATFORM_LINUX
#endif


#endif
