//
//  DataCollection_imp.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-11.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef Openbiz_RestModel_DataCollection_imp_h
#define Openbiz_RestModel_DataCollection_imp_h

#include <math.h>
#include <stdexcept>
#include "PlatformMacros.h"
#define OPENBIZ_DEFAULT_COLLECTION_PAGESIZE 10


#pragma mark - Constructor, ensure SQLite table exists
template<typename T>
std::mutex openbiz::data::DataCollection<T>::_mtx;

template<typename T>
openbiz::data::DataCollection<T>::DataCollection(const std::string &cacheName, const bool isOwnPointers):
Object(),
_isOwnPointers(isOwnPointers),
_isCacheEnabled(!cacheName.empty()),
_cacheName(cacheName){
    _pageId =1;
    _pageSize = OPENBIZ_DEFAULT_COLLECTION_PAGESIZE;
    _totalRecords = -1;
    _totalPages = -1;
    //initalize SQLite table if its cache enabled collection
    _collection = new std::map<std::string,T*>;
    if(this->isCacheEnabled())
    {
        openbiz::core::DB::getInstance()->ensureTableExists(_cacheName);
        fetch();
    }
};

#pragma mark - Desctructor , release pointers in collection
template<typename T>
openbiz::data::DataCollection<T>::~DataCollection()
{
    if(_isOwnPointers){
        if(_collection->begin() != _collection->end()){
            for(auto it = _collection->begin(); it!= _collection->end(); it++ ){
                it->second->release();
            }
        }
    }
    delete _collection;
}


#pragma mark - Getter/setting methods
template<typename T>
const unsigned int openbiz::data::DataCollection<T>::getPageSize() const
{
    return _pageSize;
}

template<typename T>
const unsigned int openbiz::data::DataCollection<T>::getCurrentPageId() const
{
    return isCacheEnabled()?_pageId:1;
}

template<typename T>
const unsigned int openbiz::data::DataCollection<T>::getCurrentRecords()
{
    return static_cast<int>(_collection->size());
}


template<typename T>
const unsigned int openbiz::data::DataCollection<T>::getTotalRecords()
{
    if(!isCacheEnabled()) return static_cast<int>(_collection->size());
    
    if(_totalRecords==-1){
        _totalRecords = openbiz::core::DB::getInstance()->countRecords(_cacheName);
    }
    return _totalRecords;
}

template<typename T>
const unsigned int openbiz::data::DataCollection<T>::getTotalPages()
{
    if(!isCacheEnabled())return 0;
    
    if(_totalPages==-1)
    {
        _totalPages =  ceil( getTotalRecords() / _pageSize  );
    }
    return _totalPages;
}


template<typename T>
const bool openbiz::data::DataCollection<T>::isFirstPage() const
{
    return (getCurrentPageId()==0);
}

template<typename T>
const bool openbiz::data::DataCollection<T>::isLastPage() 
{
    return (getCurrentPageId() == getTotalPages());
}

template<typename T>
const bool openbiz::data::DataCollection<T>::isEmpty() const
{
    return (getCurrentRecords()==0);
}

template<typename T>
const bool openbiz::data::DataCollection<T>::isCacheEnabled() const {
    return _isCacheEnabled;
}

#pragma mark - Setters also reset collection internal state
template<typename T>
void openbiz::data::DataCollection<T>::setPageSize(unsigned int pageSize)
{
    if(!isCacheEnabled()) return;
    if(pageSize>0)
    {
        _pageSize = pageSize;
        _pageId = 1;
        _totalPages = -1;
        fetch();
    }
}


#pragma mark - Serilizer / Deserilizer
//dump this object to JSON string
template<typename T>
const std::string openbiz::data::DataCollection<T>::serialize() const
{
    return this->_data.toStyledString();
};

//parse a JSON string to local attribute
template<typename T>
void openbiz::data::DataCollection<T>::parse(const std::string &data) throw (openbiz::exception::DataFormatInvalidException)
{
    parse(_parseStringToJson(data));
};

template<typename T>
void openbiz::data::DataCollection<T>::parse(const Json::Value &records) throw () {
    if(records.empty()) return;
    //clear existing records
    clear();
    parseAndAppend(records);
}

template<typename T>
void openbiz::data::DataCollection<T>::parseAndAppend(const std::string &data) throw (openbiz::exception::DataFormatInvalidException)
{
    parseAndAppend(_parseStringToJson(data));
};

template<typename T>
void openbiz::data::DataCollection<T>::parseAndAppend(const Json::Value &records) throw () {
    if(records.empty()) return;
    _data.append(records);
    
    //创建每一个成员变量去
    for(auto it = records.begin(); it!= records.end(); ++it ){
        if(it->isObject()){
            T* record = new T;
            if(!_cacheName.empty()){
                record->setCacheName(_cacheName);
            }
            record->parse(it->toStyledString());
            if(record->getId().empty())
            {
                std::string message( "trying to insert a record with empty Id, data:" + record->serialize() );
                throw std::runtime_error(message.c_str());
            }
            _collection->insert({record->getId(),record});
        }
    }
}

template<typename T>
Json::Value openbiz::data::DataCollection<T>::_parseStringToJson(const std::string &data) throw (openbiz::exception::DataFormatInvalidException)
{
    Json::Reader reader;
    Json::Value records;
    bool result = reader.parse(data,records);
    
    if(!result){
        throw openbiz::exception::DataFormatInvalidException(data);
    }
    
    return records;
}

#pragma mark - Fetch and Search methods
//fetch all
template<typename T>
void openbiz::data::DataCollection<T>::fetch()
{    
    if(!isCacheEnabled()) return ;
    
    _mtx.lock();
    const std::vector<openbiz::core::DB::Record> *records;
    int offset = ((getCurrentPageId()-1)*getPageSize());
    if(_keyword.empty()){
        records = openbiz::core::DB::getInstance()->fetchRecords(_cacheName,offset,getPageSize());
    }else{
        records = openbiz::core::DB::getInstance()->fetchRecords(_cacheName,_keyword,offset,getPageSize());
    }
    if(records->size()>0){
        for(auto it = records->cbegin(); it!= records->cend(); ++it )
        {
            T* record = new T;
            if(!_cacheName.empty())
                record->setCacheName(_cacheName);
            record->parse((*it).data);
            
            if(record->getId().empty())
            {
                std::string message( "trying to insert a record with empty Id, data:" + record->serialize() );
                throw std::runtime_error(message.c_str());
            }
            _collection->insert({record->getId(),record});
        }
    }
    OPENBIZ_SAFE_DELETE(records);
    _mtx.unlock();
    
    return ;
};


template<typename T>
void openbiz::data::DataCollection<T>::fetchNextPage(){
    if(!isCacheEnabled()) return;
    if(!isLastPage()){
        _pageId++;
        fetch();
    }
}

template<typename T>
void openbiz::data::DataCollection<T>::fetchPreviousPage(){
    if(!isCacheEnabled()) return;
    if(!isFirstPage()){
        _pageId--;
        fetch();
    }
}

template<typename T>
void openbiz::data::DataCollection<T>::fetchByPageId(unsigned int pageId) throw(std::out_of_range){
    if(!isCacheEnabled()) return;
    if(pageId>getTotalPages() || pageId<0 ){
        throw std::out_of_range("Page ID is out of range");
    }
    _pageId = pageId;
    fetch();
}


#pragma mark - Search implemtation
template<typename T>
void openbiz::data::DataCollection<T>::search(const std::string &keyword){
    if(!isCacheEnabled()) {
        //search in records
    }
    if(keyword.empty())
    {
        resetSearch();
    }else{
        _keyword = keyword;
        _pageId = 1;
        _totalPages = -1;
        _totalRecords = -1;
        fetch();
    }
}

template<typename T>
void openbiz::data::DataCollection<T>::resetSearch()
{
    if(!isCacheEnabled()) {
        //search in records
    }
    _keyword.clear();
    _pageId = 1;
    _totalPages = -1;
    _totalRecords = -1;
    fetch();
}

#pragma mark -

//save collection to local cache
template<typename T>
void openbiz::data::DataCollection<T>::save()
{
    _mtx.lock();
    if(!isCacheEnabled()) return;
    for(auto it = _collection->begin(); it!= _collection->end(); ++it )
    {
        it->second->save();
    }
    _mtx.unlock();
};

//destroy collection to local cache
template<typename T>
void openbiz::data::DataCollection<T>::destroy()
{
    _mtx.lock();
    for(auto it = _collection->begin(); it!= _collection->end(); ++it )
    {
        it->second->destroy();
    }
    _mtx.unlock();
    reset();
    
};

//only clear cache do not trigger remove delete request
template<typename T>
void openbiz::data::DataCollection<T>::clearCache()
{
    if(isCacheEnabled())
    {
        core::DB::getInstance()->removeAllRecords(_cacheName);
    }
    reset();
};

template<typename T>
void openbiz::data::DataCollection<T>::reset()
{
    _pageId =1;
    _pageSize = OPENBIZ_DEFAULT_COLLECTION_PAGESIZE;
    _totalRecords = -1;
    _totalPages = -1;
    clear();
}
#pragma mark -


#pragma mark - overload parent STL method for prevent memry leaks
template<typename T>
void openbiz::data::DataCollection<T>::clear(){
    _mtx.lock();
    if(_isOwnPointers){
        if(_collection->begin() != _collection->end()){
            for(auto it = _collection->begin(); it!= _collection->end(); it++ ){
                it->second->release();
            }
        }
    }
    _pageId =1;
    _pageSize = OPENBIZ_DEFAULT_COLLECTION_PAGESIZE;
    _totalRecords = -1;
    _totalPages = -1;
    _collection->clear();
    _data.clear();
    _mtx.unlock();
}


#pragma mark -

template<typename T>
T* openbiz::data::DataCollection<T>::get(const unsigned int index) 
throw(std::out_of_range,openbiz::exception::DataPermissionException)
{
    if(index >= _collection->size())
    {
        throw std::out_of_range("index is larger than size");
    }
    auto it = _collection->begin();
    
    //this logic is for map type container
    unsigned long realIndex = _collection->size() -1 - index;

    std::advance(it,realIndex);
    return (T*)it->second->retain();
};

template<typename T>
T* openbiz::data::DataCollection<T>::get(const std::string &key) const
throw(std::out_of_range,openbiz::exception::DataPermissionException)
{
    
    auto i = _collection->find(key);
    if (i == _collection->end()){
        throw std::out_of_range("key not found");
    }
//    i->second->retain();
    return i->second->retain();
};

template<typename T>
void openbiz::data::DataCollection<T>::del(const std::string &key)
throw (std::out_of_range,openbiz::exception::DataPermissionException){
    //permission check
    
    auto i = _collection->find(key);
    if (i == _collection->end()){
        throw std::out_of_range("key not found");
    }
    if(_isOwnPointers){
        _collection->find(key)->second->release();
    }
    _collection->erase(key);
};

template<typename T>
const bool openbiz::data::DataCollection<T>::has(const std::string &key) const throw(){
    auto i = _collection->find(key);
    return i != _collection->end();
}

template<typename T>
void openbiz::data::DataCollection<T>::set(const std::string &key, T *item)
throw(openbiz::exception::DataPermissionException){
    
    T* obj = _collection->find(key)->second;
    //release memory if assign a new object to same key
    if(obj != item){
        if(_isOwnPointers){
            delete obj;
        }
        if(has(key)){
            _collection->find(key)->second=item;
        }else{
            _collection->insert({item->getId(),item});
        }

    }
}


template<typename T>
void openbiz::data::DataCollection<T>::add(T *item)
throw(openbiz::exception::DataPermissionException){
    _collection->insert({item->getId(), item});
    
}

template<typename T>
const std::string openbiz::data::DataCollection<T>::getCacheName() const
{
    return  _cacheName;
}

#endif
