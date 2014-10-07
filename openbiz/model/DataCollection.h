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
        template<typename T>
        class DataCollection: public core::Object
        {
        public:
            DataCollection() = default;
            virtual ~DataCollection() = default;
            
            //dump this object to JSON string
            virtual const std::string serialize() const
            {
                return this->_data.toStyledString();
            };
            
            //parse a JSON string to local attribute
            virtual void parse(const std::string &data) throw (openbiz::exception::DataFormatInvalidException)
            {
                Json::Reader reader;
                bool result = reader.parse(data,this->_data);
                
                if(!result){
                    throw openbiz::exception::DataFormatInvalidException(data);
                }
                
                if(this->_data.empty()) return;
                
                //创建每一个成员变量去
                for(auto it = _data.begin(); it!= _data.end(); ++it ){
                    T *record = new T();
                    if(it->isObject()){
                        record->parse(it->toStyledString());
                    }
                    this->_records.push_back(record);
                }
            };
            
            //fetch all
            virtual const std::vector<T*> fetch(int limit=0,int offset=0)
            {
                return this->_records;
            };
            
            inline  const std::vector<T*> query(int limit){ return query("",limit,0); };
            inline  const std::vector<T*> query(int limit,int offset){ return query("",limit,offset); };
            virtual const std::vector<T*> query(const std::string &keyword = "",int limit=0,int offset=0)
            {
                return this->_records;
            };
            
            

            
        protected:
            std::vector<T*> _records;
            const std::string _baseUrl;
            Json::Value _data;
        };
    }
}

#endif /* defined(__libRestModel__DataCollection__) */