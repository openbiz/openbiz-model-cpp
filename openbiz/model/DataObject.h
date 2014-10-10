//
//  model.h
//  libRestModel
//
//  Created by Jixian Wang on 14-10-1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __libRestModel__DataObject__
#define __libRestModel__DataObject__

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <time.h>
#include <sqlite3.h>
#include "DB.h"
#include "Object.h"
#include "exception.h"
#include "json.h"


/*
 SQLite中的数据结构是
 CacheTableName
    id,  timestamp,  serializedData
 
 */
namespace openbiz
{
    namespace data
    {
        class DataObject: public core::Object
        {
        public:
            DataObject(const std::string &cacheName = "");
            ~DataObject() = default;
            
            //dump this object to JSON string
            virtual const std::string serialize() const;

            //parse a JSON string to local attribute
            virtual void parse(const std::string &data) throw (exception::DataFormatInvalidException);
            
            //get local data record ID
            const std::string getId() const throw();
            
            //fetch attributes from local db;
            virtual const bool fetch();
                        
            //save changes to local db
            virtual const bool save();
            
            //delete data from local db
            virtual const bool destroy();
            
            //set value to local data, but not saving
            template<typename T> void set(std::string &key, T value){ _data[key]=value; _changed[key]=value;};
            template<typename T> void set(const char *key, T value){ _data[key]=value; _changed[key]=value;};
            
            //set value to local data, but not saving
            Json::Value get(std::string &key){ return _data[key]; };
            Json::Value get(const char *key){ return _data[key]; };
            
            //unset a local attribute , but not saved
            virtual void unset(std::string &key);
            
            //clear local cache and attributes
            virtual void clear();
            
            //reset local attributes to previousData
            virtual void reset();
            
            //return is the data new or not
            const bool isNew() const throw();
            
            const bool isCacheEnabled() const throw();
            
            //is the record has chagned attribute or not 
            const bool hasChanged() const throw();
            
            //is the data has been cached before
            const bool hasCachedData() const throw();
            
        protected:
            std::string _id;
            Json::Value _data;
            Json::Value _previousData;
            Json::Value _changed;
            time_t _lastUpdate;
            const bool _isCacheEnabled;
            const std::string _cacheName;            
        };
    };
}

#endif /* defined(__libRestModel__DataObject__) */