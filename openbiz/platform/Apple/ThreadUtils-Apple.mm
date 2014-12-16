//
//  ThreadUtils-Apple.m
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/12/16.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//
#import <Foundation/Foundation.h>
#include "ThreadUtils-Apple.h"

namespace openbiz
{
    namespace ext
    {
        ThreadUtils* ThreadUtils::getInstance()
        {
            if (_instance == nullptr)
            {
                _instance = new (std::nothrow) ThreadUtilsApple();
            }
            return _instance;
        }
        
        const bool ThreadUtils::isOnMainThread() const
        {
            // save to document folder
            return [NSThread isMainThread];
        }
    }
}
