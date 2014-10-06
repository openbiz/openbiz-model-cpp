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
        class DataCollection: public data::DataCollection
        {
        public:
            DataCollection(const std::string &url):
            _baseUrl(url){};
            
            ~DataCollection() = default;
            
            const std::string getUrl() const throw();
            
            const std::vector<openbiz::data::DataObject *> fetch(int limit=0,int offset=0);
            template <typename T>
            inline const std::vector<T> fetch(int limit=0,int offset=0){return dynamic_cast<std::vector<T>>(fetch(limit,offset));}
            
            const std::vector<openbiz::data::DataObject *> query(const std::string &keyword = "",int limit=0,int offset=0);
            
        protected:
            const std::string _baseUrl;
        };
    };
}

#endif /* defined(__libRestModel__RemoteDataCollection__) */
