//
//  FileUtils.cpp
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-5.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "FileUtils.h"
#include "PlatformConfig.h"
#include "PlatformMacros.h"

namespace openbiz
{
    namespace ext
    {
        FileUtils* FileUtils::_instance = nullptr;
        FileUtils::~FileUtils(){};
        FileUtils::FileUtils(){};
        
        void FileUtils::destroyInstance(){
            BIZ_SAFE_DELETE(_instance);
        };
    }
}