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
#include <vector>
#include "DataCollection.h"
#include "RemoteDataObject.h"

namespace openbiz
{
    namespace remote
    {
        template <typename T>
        class DataCollection:public data::DataCollection<T>
        {
        public:
            DataCollection() = default;
            virtual ~DataCollection() = default;
            //        std::vector<openbiz::RemoteDataObject> fetch() override;
            //        std::vector<openbiz::RemoteDataObject> query(const std::string keyword,int limit,int offset) ;
            //
        protected:
            std::vector<openbiz::remote::DataObject> _records;
            const std::string _baseUri;
        };
    };
}

#endif /* defined(__libRestModel__RemoteDataCollection__) */
