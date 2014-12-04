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

#define OPENBIZ_DATA_OBJECT_FRIEND_CLASS(Model) \
friend class openbiz::data::DataObject;\
friend class openbiz::data::DataCollection<Model>;\
friend class openbiz::remote::DataObject;\
friend class openbiz::remote::DataCollection<Model>;

#define OPENBIZ_DATA_OBJECT_MUTABLE_API_WITH_BASE_CLASS(Model,BaseClass) \
OPENBIZ_DATA_OBJECT_FRIEND_CLASS(Model)\
using BaseClass::set; \
using BaseClass::validate;\
using BaseClass::hasChanged; \
using BaseClass::clear; \
using BaseClass::save; \
using BaseClass::parse; \
using BaseClass::destroy;

#define OPENBIZ_DATA_OBJECT_MUTABLE_API(Model) \
OPENBIZ_DATA_OBJECT_MUTABLE_API_WITH_BASE_CLASS(Model,DataObject)

/*
 SQLite中的数据结构是
 CacheTableName
    id,  timestamp,  serializedData
 
 */
namespace openbiz
{
    namespace data
    {
        enum DataPermission {
            Create,
            Write,
            Read,
            Delete
        };
        
        class DataObject: public core::Object
        {
        public:
            explicit DataObject(const std::string &cacheName = "");
            virtual ~DataObject() = default;
            
            virtual void parse(const std::string &json) throw (exception::DataFormatInvalidException);
            virtual void parse(const Json::Value &json);
            
            //dump this object to JSON string
            virtual const std::string serialize() const;

            //get local data record ID
            const std::string getId() const throw();
            
            //fetch attributes from local db;
            virtual const bool fetch();
            
            //validate record before save, put extra custom validation logic here
            virtual const bool validate() throw (openbiz::exception::DataValidationException);
            
            //save changes to local db
            const void save() throw (openbiz::exception::DataValidationException,
                                     openbiz::exception::DataPermissionException);
            
            //delete data from local db
            const void destroy();
            
            //set value to local data, but not saving
            template<typename T> void set(const std::string &key, T value){ _data[key]=value; _changed[key]=value;};
            template<typename T> void set(const char *key, T value){ _data[key]=value; _changed[key]=value;};
            
            //set value to local data, but not saving
            const Json::Value get(const std::string &key) const { return _data[key]; };
            const Json::Value get(const char *key) const { return _data[key]; };
            
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
            
            void setCacheName(std::string &cacheName);
            
        protected:
            virtual const bool _hasPermission(DataPermission permission) const throw();
            std::string _id;
            Json::Value _data;
            Json::Value _previousData;
            Json::Value _changed;
            time_t _lastUpdate;
            const bool _isCacheEnabled;
            std::string _cacheName;            
        };
    };
}

#endif /* defined(__libRestModel__DataObject__) */