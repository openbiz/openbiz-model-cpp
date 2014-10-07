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
#include <memory>
#include "Object.h"
#include "DataObject.h"

namespace openbiz
{
    namespace data
    {
        template<typename T>
        class DataCollection: public std::vector<std::shared_ptr<T>>
        {
            
        public:
            DataCollection(const std::string &cacheName = ""):
                _isCacheEnabled(!cacheName.empty()),
                _cacheName(cacheName){
                //initalize SQLite table
                
                };
            virtual ~DataCollection() = default;
            
            //dump this object to JSON string
            virtual const std::string serialize() const
            {
                return this->_data.toStyledString();
            };
            
            //parse a JSON string to local attribute
            virtual const void parse(const std::string &data) throw (openbiz::exception::DataFormatInvalidException)
            {
                Json::Reader reader;
                bool result = reader.parse(data,this->_data);
                
                if(!result){
                    throw openbiz::exception::DataFormatInvalidException(data);
                }
                
                if(this->_data.empty()) return;
                
                //创建每一个成员变量去
                for(auto it = _data.begin(); it!= _data.end(); ++it ){
                    std::shared_ptr<T> record = std::make_shared<T>();
                    if(it->isObject()){
                        record->parse(it->toStyledString());
                    }
                    this->push_back(record);
                }
            };
            
            //fetch all
            virtual const DataCollection<T> fetch(int limit=0,int offset=0) const
            {
                return *this;
            };
            
            inline  DataCollection<T> query(int limit){ return query("",limit,0); };
            inline  DataCollection<T> query(int limit,int offset){ return query("",limit,offset); };
            virtual DataCollection<T> query(const std::string &keyword = "",int limit=0,int offset=0) const
            {
                return *this;
            };
            
            //save collection to local cache
            virtual void save()
            {
                for(auto it = this->begin(); it!= this->end(); ++it )
                {
                    it->get()->save();
                }
            };
            
        protected:
            Json::Value _data;
            const std::string _baseUrl;
            const bool _isCacheEnabled;
            const std::string _cacheName;
        };
    }
}

#endif /* defined(__libRestModel__DataCollection__) */