//
//  RemoteDataCollection_imp.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-11.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//
#include "openbiz.h"

#ifndef Openbiz_RestModel_RemoteDataCollection_imp_h
#define Openbiz_RestModel_RemoteDataCollection_imp_h

template<typename T>
openbiz::remote::DataCollection<T>::DataCollection(const std::string &url,
                                                   const std::string &cacheName,
                                                   const RemotePaging usingRemotePaging):
_baseUrl(url),
_usingRemotePaging( usingRemotePaging==RemotePaging::Supported?true:false ),
_isUsingCachedData(false),
openbiz::data::DataCollection<T>(cacheName){
    fetch();
};

template<typename T>
openbiz::remote::DataCollection<T>::~DataCollection(){
    
}

template<typename T>
const std::string openbiz::remote::DataCollection<T>::getUrl() const throw()
{
    if(!_usingRemotePaging) return _baseUrl;
    
    std::string formattedURL(this->_baseUrl);
    formattedURL += "?per_page="+ std::to_string(this->_pageSize)+
                    "&page="+std::to_string(this->_pageId);
    if(!this->_keyword.empty())
    {
        formattedURL += "&keyword="+ this->_keyword;
    }
    return formattedURL;
};

template<typename T>
void openbiz::remote::DataCollection<T>::fetch()
{
    RestClient::response r = RestClient::get(getUrl());
    switch(r.code)
    {
        case -1:
            if(this->isCacheEnabled())
            {
                //try to load cached data
                _isUsingCachedData = true;
                openbiz::data::DataCollection<T>::fetch();
            }else{
                //if collection has no cache enabled,
                throw openbiz::exception::NetworkConnectionException(r);
            }
            break;
        case 200:
            if(_isUsingCachedData)
            {
                //if current data is loaded from cache, the destroy cache and rewrite
                openbiz::data::DataCollection<T>::clearCache();
                _isUsingCachedData = false;
            }
            _processFetchedData(r);
            break;
        case 204:
        default:
            break;
    }
    return  ;
};


template<typename T>
void openbiz::remote::DataCollection<T>::refresh()
{
    int originalPageId = this->_pageId;
    this->_pageId = 1;
    
    RestClient::response r = RestClient::get(getUrl());
    switch(r.code)
    {
        case -1:
            if(this->isCacheEnabled())
            {
                //try to load cached data
                _isUsingCachedData = true;
                this->_pageId = originalPageId;
                openbiz::data::DataCollection<T>::fetch();
            }else{
                //if collection has no cache enabled,
                throw openbiz::exception::NetworkConnectionException(r);
            }
            break;
        case 200:
            openbiz::data::DataCollection<T>::reset();
            openbiz::data::DataCollection<T>::clearCache();
            _isUsingCachedData = false;
            _processFetchedData(r);
            break;
        case 204:
        default:
            break;
    }
    return  ;
}

template<typename T>
void openbiz::remote::DataCollection<T>::_processFetchedData(const RestClient::response &r)
{
    if(_usingRemotePaging){
        Json::Reader reader;
        Json::Value data;
        bool result = reader.parse(r.body,data);
        if(!result){
            throw openbiz::exception::DataFormatInvalidException(r.body);
        }
        openbiz::data::DataCollection<T>::_totalRecords = data[0]["total_entries"].asInt();
        openbiz::data::DataCollection<T>::_totalPages   = data[0]["total_pages"].asInt();
        openbiz::data::DataCollection<T>::_pageSize     = data[0]["per_page"].asInt();
        openbiz::data::DataCollection<T>::_pageId       = data[0]["page"].asInt();
        openbiz::data::DataCollection<T>::parseAndAppend(data[1]);
    }else{
        openbiz::data::DataCollection<T>::clearCache();
        openbiz::data::DataCollection<T>::parse(r.body);
    }
    openbiz::data::DataCollection<T>::save();
}

#endif
