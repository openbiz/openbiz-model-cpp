//
//  ThreadUtils.cpp
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/12/16.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "ThreadUtils.h"
#include "PlatformConfig.h"
#include "PlatformMacros.h"

namespace openbiz
{
    namespace ext
    {
        ThreadUtils* ThreadUtils::_instance = nullptr;

        void ThreadUtils::destroyInstance(){
            OPENBIZ_SAFE_DELETE(_instance);
        };
        
        const bool ThreadUtils::isOnMainThread() const
        {
            return false;
        }
    }
}