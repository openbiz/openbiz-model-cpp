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
            DataCollection(const std::string &cacheName = "");
            virtual ~DataCollection() = 0;
            
            //dump this object to JSON string
            const std::string serialize() const;
            
            //parse a JSON string to local attribute
            void parse(const std::string &data) throw (openbiz::exception::DataFormatInvalidException);
            
            //fetch all
            virtual void fetch();
            void fetchByPageId(unsigned int pageId) throw (std::out_of_range);
            void fetchNextPage();
            void fetchPreviousPage();
            
            //search
            void search(const std::string &keyword);
            void resetSearch();
            
            const bool isLastPage() const;
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
            
            //accessor methods
            const T* get(const unsigned int index) const throw(std::out_of_range,openbiz::exception::DataPermissionException);
            const T* get(const std::string &key) const throw (std::out_of_range,openbiz::exception::DataPermissionException);
            void add(const T *item) throw (openbiz::exception::DataPermissionException);
            void del(const std::string &key) throw (std::out_of_range,openbiz::exception::DataPermissionException);
            void set(const std::string &key, const T *item) throw(openbiz::exception::DataPermissionException);
            
            const bool has(const std::string &key) const throw();
            
            //is the collection has cache feature enabled
            const bool isCacheEnabled() const;
            
            
            
        protected:
            void clear();
            void erase(const std::string &key);
            
            virtual const bool _hasPermission(DataPermission permission) const throw();
            const void parse(const Json::Value &records) throw ();
            Json::Value _data;
            const std::string _baseUrl;
            const bool _isCacheEnabled;
            const std::string _cacheName;
            int _totalRecords;
            int _totalPages;
            int _pageSize;
            unsigned int _pageId;
            std::string _keyword;
            std::map<std::string,T*> *_collection;
        };
    }
}

#include "DataCollection_imp.h"
#endif /* defined(__libRestModel__DataCollection__) */