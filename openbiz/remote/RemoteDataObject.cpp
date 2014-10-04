//
//  RemoteDataObject.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "RemoteDataObject.h"
#include "restclient-cpp/restclient.h"
#include "json.h"

using namespace std;
namespace openbiz
{
#pragma mark - Metadata 运算符重载 向下兼容
    remote::DataObject::Metadata::operator openbiz::data::DataObject::Metadata *()
    {
        openbiz::data::DataObject::Metadata *meta = new openbiz::data::DataObject::Metadata();
        meta->isCacheEnabled = isCacheEnabled;
        meta->cacheName = cacheName;
        return meta;
    };

#pragma mark - 核心业务逻辑
    const bool remote::DataObject::fetch()
    {
        cout<< std::to_string(this->_isCacheEnabled) << endl;
        return true;
    };
    
    const bool remote::DataObject::save()
    {
        bool result = data::DataObject::save();
        return result;
    };
    
    const bool remote::DataObject::sync()
    {
        return true;
    };
    

}