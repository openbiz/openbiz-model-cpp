//
//  DataCollection.h
//  libRestModel
//
//  Created by Jixian Wang on 14-10-1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//
#ifndef __libRestModel__DataCollection__
#define __libRestModel__DataCollection__

#include <stdio.h>
#include <list>
#include "Object.h"
#include "DataObject.h"

namespace openbiz
{
    namespace data
    {
        template<typename T>
        class DataCollection:public core::Object
        {
        public:
            DataCollection() = default;
            virtual ~DataCollection() = default;
            virtual std::list<T> fetch();
            //        std::vector<openbiz::DataObject> query(int limit){ return query("",limit,0); };
            //        std::vector<openbiz::DataObject> query(int limit,int offset){ return query("",limit,offset); };
            //        virtual std::vector<openbiz::DataObject> query(const std::string keyword,int limit,int offset);
            
        protected:
            std::list<T> _records;
            const std::string _baseUri;
        };
    }
}

#endif /* defined(__libRestModel__DataCollection__) */