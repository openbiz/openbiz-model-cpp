//
//  Object.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "Object.h"
#include "config.h"

using namespace std;
using namespace openbiz::core;

Object::Object()
{
    _refCount = 1;
}

Object::~Object()
{
    _refCount = 0;
}


Object* Object::retain()
{
    _refCount ++;
    return this;
}

unsigned int Object::release() const
{
    if ( 0 == _refCount -1 ) {
        //delete this;
        return 0;
    }
    return _refCount -1 ;
}

unsigned int Object::release()
{
    _refCount --;
    if ( 0 == _refCount ) {
        //delete this;
        return 0;
    }
    return _refCount;
}

const std::string Object::serialize()
{
    return "";
}

void Object::parse(const std::string &data)
{
    
}