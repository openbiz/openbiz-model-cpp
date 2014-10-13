//
//  FileUtils-Apple.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-5.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __CC_FILEUTILS_ANDROID_H__
#define __CC_FILEUTILS_ANDROID_H__
#include "FileUtils.h"

namespace openbiz
{
    namespace ext
    {
        class FileUtilsAndroid : public FileUtils
        {
            friend class FileUtils;
        public:
            FileUtilsAndroid()=default;
            virtual std::string getWritablePath() const;
        };
        
    }
}

#endif    // __CC_FILEUTILS_ANDROID_H__

