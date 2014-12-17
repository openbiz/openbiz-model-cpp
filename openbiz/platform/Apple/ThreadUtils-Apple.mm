//
//  ThreadUtils-Apple.m
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/12/16.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//
#import <Foundation/Foundation.h>
#include "ThreadUtils-Apple.h"
#include "ThreadUtils.h"


openbiz::ext::ThreadUtils* openbiz::ext::ThreadUtils::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new (std::nothrow) openbiz::ext::ThreadUtilsApple();
    }
    return _instance;
}

const bool openbiz::ext::ThreadUtilsApple::isOnMainThread() const
{
    bool result =  [NSThread isMainThread];
    return result;
}