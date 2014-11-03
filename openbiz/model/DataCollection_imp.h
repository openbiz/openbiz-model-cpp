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
#define OPENBIZ_DEFAULT_COLLECTION_PAGESIZE 10


#pragma mark - Constructor, ensure SQLite table exists
template<typename T>
openbiz::data::DataCollection<T>::DataCollection(const std::string &cacheName):
_isCacheEnabled(!cacheName.empty()),
_cacheName(cacheName){
    _pageId =0;
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
    if(_collection->begin() != _collection->end()){
        for(auto it = _collection->begin(); it!= _collection->end(); it++ ){
            delete it->second;
        }
    }
    delete _collection;
}


#pragma mark - Getter/setting methods
template<typename T>
const unsigned int openbiz::data::DataCollection<T>::getPageSize() const
{
    return isCacheEnabled()?static_cast<int>(_collection->size()):_pageSize;
}

template<typename T>
const unsigned int openbiz::data::DataCollection<T>::getCurrentPageId() const
{
    return isCacheEnabled()?_pageId:0;
}

template<typename T>
const unsigned int openbiz::data::DataCollection<T>::getCurrentRecords()
{
    return static_cast<int>(_collection->size());
}


template<typename T>
const unsigned int openbiz::data::DataCollection<T>::getTotalRecords()
{
    if(!isCacheEnabled()) return _collection->size();
    
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
const bool openbiz::data::DataCollection<T>::isLastPage() const
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
        _pageId = 0;
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
    Json::Reader reader;
    Json::Value records;
    bool result = reader.parse(data,records);
    
    if(!result){
        throw openbiz::exception::DataFormatInvalidException(data);
    }
    
    parse(records);
    
};

template<typename T>
const void openbiz::data::DataCollection<T>::parse(const Json::Value &records) throw () {
    if(records.empty()) return;
    _data = records;
    
    //clear existing records
    clear();
    
    //创建每一个成员变量去
    for(auto it = records.begin(); it!= records.end(); ++it ){
        if(it->isObject()){
            T* record = T::template parse<T>(it->toStyledString()) ;
            _collection->insert({record->getId(),record});
        }
    }
}

#pragma mark - Fetch and Search methods
//fetch all
template<typename T>
void openbiz::data::DataCollection<T>::fetch()
{
    if(!_hasPermission(DataPermission::Read)) throw openbiz::exception::DataPermissionException("Fetch");
    
    if(!this->isCacheEnabled()) return ;
    const std::vector<openbiz::core::DB::record*> *records;
    int offset = (getCurrentPageId()*getPageSize());
    if(_keyword.empty()){
        records = openbiz::core::DB::getInstance()->fetchRecords(_cacheName,offset,getPageSize());
    }else{
        records = openbiz::core::DB::getInstance()->fetchRecords(_cacheName,_keyword,offset,getPageSize());
    }
    if(records->size()>0){
        for(auto it = records->cbegin(); it!= records->cend(); ++it )
        {
            T* record = T::template parse<T>((*it)->data);
            _collection->insert({record->getId(),record});
        }
    }
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
        _pageId = 0;
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
    _pageId = 0;
    _totalPages = -1;
    _totalRecords = -1;
    fetch();
}

#pragma mark -

//save collection to local cache
template<typename T>
void openbiz::data::DataCollection<T>::save()
{
    if(!_hasPermission(DataPermission::Write)) throw openbiz::exception::DataPermissionException("Write");
    if(!isCacheEnabled()) return;
    for(auto it = _collection->begin(); it!= _collection->end(); ++it )
    {
        it->second->save();
    }
};

//destroy collection to local cache
template<typename T>
void openbiz::data::DataCollection<T>::destroy()
{
    if(!_hasPermission(DataPermission::Delete)) throw openbiz::exception::DataPermissionException("Delete");
    for(auto it = _collection->begin(); it!= _collection->end(); ++it )
    {
        it->second->destroy();
    }
    reset();
};

template<typename T>
void openbiz::data::DataCollection<T>::reset()
{
    _pageId =0;
    _pageSize = OPENBIZ_DEFAULT_COLLECTION_PAGESIZE;
    _totalRecords = -1;
    _totalPages = -1;
    clear();
}
#pragma mark -


#pragma mark - overload parent STL method for prevent memry leaks
template<typename T>
void openbiz::data::DataCollection<T>::clear(){
    if(_collection->begin() != _collection->end()){
        for(auto it = _collection->begin(); it!= _collection->end(); it++ ){
            delete it->second;
        }
    }
    _collection->clear();
}


#pragma mark -

template<typename T>
const T* openbiz::data::DataCollection<T>::get(const unsigned int index) const
throw(std::out_of_range,openbiz::exception::DataPermissionException)
{
    if(!_hasPermission(DataPermission::Read)) throw openbiz::exception::DataPermissionException("Fetch");
    if(index >= _collection->size())
    {
        throw std::out_of_range("index is larger than sizz");
    }
    auto it = _collection->begin();
    std::advance(it,index);
    return (T*)it->second;
};

template<typename T>
const T* openbiz::data::DataCollection<T>::get(const std::string &key) const
throw(std::out_of_range,openbiz::exception::DataPermissionException)
{
    if(!_hasPermission(DataPermission::Read)) throw openbiz::exception::DataPermissionException("Fetch");
    
    auto i = _collection->find(key);
    if (i == _collection->end()){
        throw std::out_of_range("key not found");
    }
    return i->second;
};

template<typename T>
void openbiz::data::DataCollection<T>::del(const std::string &key)
throw (std::out_of_range,openbiz::exception::DataPermissionException){
    //permission check
    if(!_hasPermission(DataPermission::Delete)) throw openbiz::exception::DataPermissionException("Delete");
    
    auto i = _collection->find(key);
    if (i == _collection->end()){
        throw std::out_of_range("key not found");
    }
    delete _collection->find(key)->second;
    _collection->erase(key);
};

template<typename T>
const bool openbiz::data::DataCollection<T>::has(const std::string &key) const throw(){
    auto i = _collection->find(key);
    return i != _collection->end();
}

template<typename T>
void openbiz::data::DataCollection<T>::set(const std::string &key, const T *item)
throw(openbiz::exception::DataPermissionException){
    if(!_hasPermission(DataPermission::Write)) throw openbiz::exception::DataPermissionException("Write");
    
    T* obj = _collection->find(key)->second;
    //release memory if assign a new object to same key
    if(obj != item){
        delete obj;
        _collection->find(key)=item;
    }
}


template<typename T>
void openbiz::data::DataCollection<T>::add(const T *item)
throw(openbiz::exception::DataPermissionException){
    if(!_hasPermission(DataPermission::Write)) throw openbiz::exception::DataPermissionException("Write");

    _collection->insert({item->getId(), item});
    
}

template<typename T>
const bool openbiz::data::DataCollection<T>::_hasPermission(DataPermission permission) const throw(){
    return true;
};

#endif
