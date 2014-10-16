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
#include <map>
#include <memory>
#include "DB.h"
#include "Object.h"
#include "DataObject.h"

namespace openbiz
{
    namespace data
    {
        template<typename T>
        class DataCollection: public std::map<std::string,std::shared_ptr<T>>
        {
            
        public:
            DataCollection(const std::string &cacheName = "");
            virtual ~DataCollection() = default;
            
            //dump this object to JSON string
            virtual const std::string serialize() const;
            
            //parse a JSON string to local attribute
            virtual const void parse(const std::string &data) throw (openbiz::exception::DataFormatInvalidException);
            
            //fetch all
            DataCollection<T>* fetch(int offset=0,int limit=-1);
            inline  DataCollection<T>* query(int limit){ return query("",limit,0); };
            inline  DataCollection<T>* query(int limit,int offset){ return query("",limit,offset); };
            DataCollection<T>* query(const std::string &keyword = "",int limit=0,int offset=0) const;
            
            //save collection to local cache
            virtual void save();
            
            //destroy collection to local cache
            virtual void destroy();
            
            const bool isCacheEnabled() const throw();
            
        protected:
            Json::Value _data;
            const std::string _baseUrl;
            const bool _isCacheEnabled;
            const std::string _cacheName;
        };
    }
}

#include "DataCollection_imp.h"
#endif /* defined(__libRestModel__DataCollection__) */