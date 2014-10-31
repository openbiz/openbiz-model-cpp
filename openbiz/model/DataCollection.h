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

#define OPENBIZ_DATA_COLLECTION_MUTABLE_API(Model) \
void save();\
void destroy();\
void del(const std::string &key) throw (std::out_of_range);\
void set(const std::string& key, Model& item) throw();\

#define OPENBIZ_DATA_COLLECTION_PUBLIC_API(Collection,Model) \


namespace openbiz
{
    namespace data
    {
        template<typename T>
        class DataCollection: protected std::map<std::string,T* >
        {
            
        public:
            DataCollection(const std::string &cacheName = "");
            virtual ~DataCollection();
            
            //dump this object to JSON string
            const std::string serialize() const;
            
            //parse a JSON string to local attribute
            const void parse(const std::string &data) throw (openbiz::exception::DataFormatInvalidException);
            
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
            
            
            //save collection to local cache
            void save();
            
            //destroy collection to local cache
            void destroy();
            
            //accessor methods
            const T* get(const unsigned int index) const throw(std::out_of_range);
            const T* get(const std::string &key) const throw (std::out_of_range);
            void del(const std::string &key) throw (std::out_of_range);
            const bool has(const std::string& key) const throw();
            void set(const std::string& key, T& item) throw();
            
            //is the collection has cache feature enabled
            const bool isCacheEnabled() const;
            
            using std::map<std::string,T* >::begin;
            using std::map<std::string,T* >::end;
            
        protected:
            const void parse(const Json::Value& records) throw ();
            Json::Value _data;
            const std::string _baseUrl;
            const bool _isCacheEnabled;
            const std::string _cacheName;
            int _totalRecords;
            int _totalPages;
            int _pageSize;
            unsigned int _pageId;
            std::string _keyword;
        };
    }
}

#include "DataCollection_imp.h"
#endif /* defined(__libRestModel__DataCollection__) */