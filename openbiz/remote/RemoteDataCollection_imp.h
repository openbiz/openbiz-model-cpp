//
//  RemoteDataCollection_imp.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-11.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef Openbiz_RestModel_RemoteDataCollection_imp_h
#define Openbiz_RestModel_RemoteDataCollection_imp_h

template<typename T>
openbiz::remote::DataCollection<T>::DataCollection(const std::string &url,const std::string &cacheName):
_baseUrl(url),openbiz::data::DataCollection<T>(cacheName){
    
};

template<typename T>
const std::string openbiz::remote::DataCollection<T>::getUrl() const throw()
{
    return this->_baseUrl.c_str();
};

template<typename T>
openbiz::remote::DataCollection<T>* openbiz::remote::DataCollection<T>::fetch(int offset,int limit)
{
    RestClient::response r = RestClient::get(this->getUrl());
    switch(r.code)
    {
        case -1:
            if(this->isCacheEnabled())
            {
                //try to load cached data
                openbiz::data::DataCollection<T>::fetch(offset,limit);
            }else{
                //if collection has no cache enabled,
                throw openbiz::exception::NetworkConnectionException(r);
            }
            break;
        case 200:
            openbiz::data::DataCollection<T>::parse(r.body);
            openbiz::data::DataCollection<T>::save();
            break;
        case 204:
        default:
            break;
    }
    return this ;
};


template<typename T>
openbiz::remote::DataCollection<T>* openbiz::remote::DataCollection<T>::query(const std::string &keyword,int limit,int offset)
{
    return this;
};
#endif
