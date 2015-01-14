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

#define OPENBIZ_DATA_COLLECTION_MUTABLE_API \
using DataCollection::save; \
using DataCollection::destroy; \
using DataCollection::set; \
using DataCollection::del;



namespace openbiz
{
    namespace data
    {
        template<typename T>
        class DataCollection: public core::Object
        {
            
        public:
            DataCollection(const std::string &cacheName = "",const bool isOwnPointers=true);
            virtual ~DataCollection() = 0;
            
            //dump this object to JSON string
            const std::string serialize() const;
            
            //parse a JSON string to local attribute
            void parse(const std::string &data) throw (openbiz::exception::DataFormatInvalidException);
            void parseAndAppend(const std::string &data) throw (openbiz::exception::DataFormatInvalidException);
            
            //fetch all
            virtual void fetch();
            void fetchNextPage();
            void fetchPreviousPage();
            
            //search
            void search(const std::string &keyword);
            void resetSearch();
            
            const bool isLastPage();
            const bool isFirstPage() const;
            const bool isEmpty() const;
            
            const unsigned int getPageSize() const;
            void setPageSize(unsigned int pageSize);
            
            const unsigned int getCurrentPageId() const;
            const unsigned int getCurrentRecords();
            const unsigned int getTotalPages();
            const unsigned int getTotalRecords();
            
            //reset the collection to default state
            void reset();
            
            //save collection to local cache
            virtual void save();
            
            //destroy collection to local cache
            void destroy();
            
            void clearCache();
            
            //accessor methods
            T* get(const unsigned int index)  throw(std::out_of_range,openbiz::exception::DataPermissionException);
            T* get(const std::string &key) const throw (std::out_of_range,openbiz::exception::DataPermissionException);
            void add(T *item) throw (openbiz::exception::DataPermissionException);
            void del(const std::string &key) throw (std::out_of_range,openbiz::exception::DataPermissionException);
            void set(const std::string &key, T *item) throw(openbiz::exception::DataPermissionException);
            
            const bool has(const std::string &key) const throw();
            
            //is the collection has cache feature enabled
            const bool isCacheEnabled() const;
            
            const std::string getCacheName() const;
            
        protected:
            void fetchByPageId(unsigned int pageId) throw (std::out_of_range);
            void clear();
            void erase(const std::string &key);
            
            void parse(const Json::Value &records) throw ();
            void parseAndAppend(const Json::Value &records) throw ();
            Json::Value _parseStringToJson(const std::string &data) throw (openbiz::exception::DataFormatInvalidException);
            Json::Value _data;
            const std::string _baseUrl;
            const bool _isCacheEnabled;
            std::string _cacheName;
            int _totalRecords;
            int _totalPages;
            int _pageSize;
            unsigned int _pageId;
            std::string _keyword;
            std::map<std::string,T*> *_collection;
            const bool _isOwnPointers;
            static std::mutex _mtx;
        };
    }
}

#include "DataCollection_imp.h"
#endif /* defined(__libRestModel__DataCollection__) */