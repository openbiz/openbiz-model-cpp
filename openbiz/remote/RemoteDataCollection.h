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

namespace openbiz
{
    namespace remote
    {
        template<typename T>
        class DataCollection: public openbiz::data::DataCollection<T>
        {
        public:
            DataCollection(const std::string &url):
            _baseUrl(url){};
            
            ~DataCollection() = default;
            
            const std::string getUrl() const throw()
            {
                return this->_baseUrl.c_str();
            };
            
            const std::vector<T*> fetch(int limit=0,int offset=0)
            {
                std::cout<<"test test"<<std::endl;
                RestClient::response r = RestClient::get(this->getUrl());
                switch(r.code)
                {
                    case -1:
                        throw openbiz::exception::NetworkConnectionException(r);
                        break;
                        break;
                    case 200:
                        openbiz::data::DataCollection<T>::parse(r.body);
                        break;
                    case 204:
                    default:
                        break;                
                }
                return data::DataCollection<T>::_records;
            };
            const std::vector<T*> query(const std::string &keyword = "",int limit=0,int offset=0)
            {
                return data::DataCollection<T>::_records;
            };
            
        protected:
            const std::string _baseUrl;
        };
    };
}

#endif /* defined(__libRestModel__RemoteDataCollection__) */
