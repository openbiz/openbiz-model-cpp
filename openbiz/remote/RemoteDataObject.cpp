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
using namespace openbiz;
using namespace openbiz::remote;
using namespace openbiz::exception;


namespace openbiz
{
#pragma mark - Metadata 运算符重载 向下兼容
    DataObject::Metadata::operator openbiz::data::DataObject::Metadata *()
    {
        openbiz::data::DataObject::Metadata *meta = new openbiz::data::DataObject::Metadata();
        meta->isCacheEnabled = isCacheEnabled;
        meta->cacheName = cacheName;
        return meta;
    };

#pragma mark - 核心业务逻辑
    const std::string DataObject::getUri() const throw()
    {
        std::string uri = this->_baseUri;
        if(!this->_id.empty()){
            uri.append("/"+this->_id);
        }
        return uri.c_str();
    };
    
    const bool DataObject::sync()
    {
        return true;
    }
    
    const bool DataObject::fetch()
    {
        if(!data::DataObject::fetch()) return false;
        cout<< std::to_string(this->_isCacheEnabled) << endl;
        return true;
    };
    
    const bool DataObject::save()
    {
        if(!data::DataObject::save()) return false;
        return true;
    };
    
    const bool DataObject::destroy() throw ( NetworkConnectionException )
    {
        if(!data::DataObject::destroy()) return false;
        
        RestClient::response r = RestClient::del(this->getUri());
        switch(r.code)
        {
            case -1:
                throw NetworkConnectionException(r);
                break;
                break;
            case 200:
                return true;
                break;
            default:
                return false;
                
        }

        return true;
    }

}