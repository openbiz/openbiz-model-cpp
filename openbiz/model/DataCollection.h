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
#include <vector>
#include "Object.h"
#include "DataObject.h"

namespace openbiz
{
    namespace data
    {
        class DataCollection: public core::Object
        {
        public:
            DataCollection() = default;
            virtual ~DataCollection() = default;
            
            //dump this object to JSON string
            virtual const std::string serialize() const;
            
            //parse a JSON string to local attribute
            virtual void parse(const std::string &data) throw (exception::DataFormatInvalidException);
            
            //fetch all
            virtual const std::vector<openbiz::data::DataObject *> fetch(int limit=0,int offset=0);
            template <typename T>
            inline const std::vector<T> fetch(int limit=0,int offset=0){return dynamic_cast<T>(fetch(limit,offset));}
            
            virtual const std::vector<openbiz::data::DataObject *> query(const std::string &keyword = "",int limit=0,int offset=0);
            inline  const std::vector<openbiz::data::DataObject *> query(int limit){ return query("",limit,0); };
            inline  const std::vector<openbiz::data::DataObject *> query(int limit,int offset){ return query("",limit,offset); };
            

            
        protected:
            std::vector<openbiz::data::DataObject *> _records;
            const std::string _baseUrl;
            Json::Value _data;
        };
    }
}

#endif /* defined(__libRestModel__DataCollection__) */