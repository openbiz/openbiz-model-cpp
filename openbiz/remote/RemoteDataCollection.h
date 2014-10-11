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
    inline Collection fetch(int offset=0,int limit=-1) \
        { DataCollection<Model>::fetch(offset,limit); return *this; }\
    inline Collection query(const std::string &keyword = "", int offset=0,int limit=-1) \
        { DataCollection<Model>::query(keyword,offset,limit); return *this; }

namespace openbiz
{
    namespace remote
    {
        template<typename T>
        class DataCollection: public openbiz::data::DataCollection<T>
        {
        public:
            DataCollection(const std::string &url,const std::string &cacheName="");
            ~DataCollection() = default;
            
            const std::string getUrl() const throw();
            
            DataCollection<T> fetch(int offset=0,int limit=-1);
            DataCollection query(const std::string &keyword = "",int limit=0,int offset=0);
            
        protected:
            const std::string _baseUrl;
        };
    };
}

#include "RemoteDataCollection_imp.h"
#endif /* defined(__libRestModel__RemoteDataCollection__) */
