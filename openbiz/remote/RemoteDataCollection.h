//
//  RemoteDataCollection.h
//  libRestModel
//
//  Created by Jixian Wang on 14-10-2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __libRestModel__RemoteDataCollection__
#define __libRestModel__RemoteDataCollection__

#include <stdio.h>
#include <iostream>
#include <vector>
#include "DataCollection.h"
#include "RemoteDataObject.h"

#define OPENBIZ_DATA_COLLECTION_PUBLIC_API(Collection,Model) \
    inline Collection fetch(int limit=0,int offset=0) \
        { DataCollection<Model>::fetch(limit,offset); return *this; }\
    inline Collection query(const std::string &keyword = "", int limit=0,int offset=0) \
        { DataCollection<Model>::query(keyword,limit,offset); return *this; }

namespace openbiz
{
    namespace remote
    {
        template<typename T>
        class DataCollection: public openbiz::data::DataCollection<T>
        {
        public:
            DataCollection(const std::string &url,const std::string &cacheName=""):
                _baseUrl(url),
                openbiz::data::DataCollection<T>(cacheName){};
            
            ~DataCollection() = default;
            
            const std::string getUrl() const throw()
            {
                return this->_baseUrl.c_str();
            };            
            
            DataCollection fetch(int limit=0,int offset=0)
            {
                std::cout<<"test test"<<std::endl;
                RestClient::response r = RestClient::get(this->getUrl());
                switch(r.code)
                {
                    case -1:
                        if(this->_isCacheEnabled == true)
                        {
                            //if collection has no cache enabled,
                            throw openbiz::exception::NetworkConnectionException(r);
                        }else{
                            //try to load cached data
                            openbiz::data::DataCollection<T>::fetch(limit,offset);
                        }
                        break;
                        break;
                    case 200:
                        openbiz::data::DataCollection<T>::parse(r.body);
                        openbiz::data::DataCollection<T>::save();
                        break;
                    case 204:
                    default:
                        break;                
                }
                return *this ;
            };
            DataCollection query(const std::string &keyword = "",int limit=0,int offset=0)
            {
                return *this;
            };
            
        protected:
            const std::string _baseUrl;
        };
    };
}

#endif /* defined(__libRestModel__RemoteDataCollection__) */
