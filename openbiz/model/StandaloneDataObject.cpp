//
//  StandaloneDataObject.cpp
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/12/4.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "StandaloneDataObject.h"
using namespace openbiz::data;
StandaloneDataObject::StandaloneDataObject(const std::string &cacheName)
:DataObject(cacheName)
{
    if(_isCacheEnabled){
        _id = "DEFAULT";
    }
}

StandaloneDataObject::~StandaloneDataObject()
{
    
}