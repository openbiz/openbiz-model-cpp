//
//  RemoteDataObject.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "RemoteDataObject.h"
#include "restclient.h"
#include "json.h"

using namespace std;
using namespace openbiz;
using namespace openbiz::remote;
using namespace openbiz::exception;


namespace openbiz
{
#pragma mark - 核心业务逻辑
    /*
     generate URI for this record
     format:
        baseUri + recordID
     */
    const std::string DataObject::getUrl() const throw()
    {
        std::string uri = this->_baseUrl;
        if(!this->_id.empty()){
            uri.append("/"+this->_id);
        }
        return uri.c_str();
    };
    

    /*
     fetch remote data
     then parse data to local cache
     if network connection timeout, then only fetch from local and return
     */
    const bool DataObject::fetch() throw ( NetworkConnectionException,ServerErrorException )
    {
        RestClient::response r = RestClient::get(this->getUrl());
        switch(r.code)
        {
            case -1:
                if(!data::DataObject::fetch())
                {
                    throw NetworkConnectionException(r);
                }
                break;
            case 200:
                data::DataObject::parse(r.body);
                return true;
                break;
            case 500:
                throw ServerErrorException(r);
                break;
            case 204:
            default:
                return false;
                
        }
        return true;
    };
    
    const bool DataObject::save() throw ( NetworkConnectionException,ServerErrorException )
    {
        if( this->isCacheEnabled() &&  !this->hasChanged() )
            data::DataObject::save();
        
        //if there are nothing changed, then nothign to do
        if(!this->hasChanged()) return true;
        
        //prepare to send changes to server
        RestClient::response r;
        
        if(this->isNew()){
            //post to baseURL
            r = RestClient::post(_baseUrl,_data.toStyledString());
            
        }else{
            //put to record URL
            r = RestClient::put(getUrl(),_data.toStyledString());
        }
        
        switch(r.code)
        {
            case -1:
                throw NetworkConnectionException(r);
                break;
            case 200:
            case 201:
                data::DataObject::parse(r.body);
                if(!data::DataObject::save()) return false;
                break;
            case 204:
                if(!data::DataObject::save()) return false;
                break;
            case 500:
                throw ServerErrorException(r);                
                break;
            default:
                return false;
                break;
        }
        _lastSync = time(nullptr);
        return true;
    };
    
    
    /*
     purge remote data
     then delete local cache
     */
    const bool DataObject::destroy() throw ( NetworkConnectionException,ServerErrorException )
    {
        RestClient::response r = RestClient::del(this->getUrl());
        switch(r.code)
        {
            case -1:
                throw NetworkConnectionException(r);
                break;
            case 200:
            case 204:
                if(!data::DataObject::destroy()) return false;
                return true;
                break;
            case 500:
                throw ServerErrorException(r);
            default:
                return false;
                break;
        }
        return true;
    }

}