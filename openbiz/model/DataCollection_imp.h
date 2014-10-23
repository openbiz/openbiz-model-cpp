//
//  DataCollection_imp.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-11.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef Openbiz_RestModel_DataCollection_imp_h
#define Openbiz_RestModel_DataCollection_imp_h




template<typename T>
openbiz::data::DataCollection<T>::DataCollection(const std::string &cacheName):
_isCacheEnabled(!cacheName.empty()),
_cacheName(cacheName){
    //initalize SQLite table
    
};

//dump this object to JSON string
template<typename T>
const std::string openbiz::data::DataCollection<T>::serialize() const
{
    return this->_data.toStyledString();
};

//parse a JSON string to local attribute
template<typename T>
const void openbiz::data::DataCollection<T>::parse(const std::string &data) throw (openbiz::exception::DataFormatInvalidException)
{
    Json::Reader reader;
    bool result = reader.parse(data,this->_data);
    
    if(!result){
        throw openbiz::exception::DataFormatInvalidException(data);
    }
    
    if(this->_data.empty()) return;
    
    //clear existing records
    this->clear();
    
    //创建每一个成员变量去
    for(auto it = _data.begin(); it!= _data.end(); ++it ){
        if(it->isObject()){
            std::shared_ptr<T> record( T::template parse<T>(it->toStyledString()) );
            this->insert({record->getId(),record});
        }
    }
};

//fetch all
template<typename T>
openbiz::data::DataCollection<T>* openbiz::data::DataCollection<T>::fetch(int offset,int limit)
{
    if(!this->isCacheEnabled()) return this;
    openbiz::core::DB::getInstance()->ensureTableExists(_cacheName);
    const std::vector<openbiz::core::DB::record*> *records = openbiz::core::DB::getInstance()->fetchRecords(_cacheName,offset,limit);
    if(records->size()>0){
        for(auto it = records->cbegin(); it!= records->cend(); ++it )
        {
            std::shared_ptr<T> record( T::template parse<T>((*it)->data) );
            this->insert({record->getId(),record});
        }
    }
    return this;
};

template<typename T>
openbiz::data::DataCollection<T>* openbiz::data::DataCollection<T>::query(const std::string &keyword,int limit,int offset) const
{
    return this;
};

//save collection to local cache
template<typename T>
void openbiz::data::DataCollection<T>::save()
{
    for(auto it = this->begin(); it!= this->end(); ++it )
    {
        it->second.get()->save();
    }
};

//destroy collection to local cache
template<typename T>
void openbiz::data::DataCollection<T>::destroy()
{
    for(auto it = this->begin(); it!= this->end(); ++it )
    {
        it->second.get()->destroy();
    }
};

template<typename T>
const bool openbiz::data::DataCollection<T>::isCacheEnabled() const throw(){
    return _isCacheEnabled;
};

template<typename T>
const T* openbiz::data::DataCollection<T>::get(const unsigned int index) const throw(std::out_of_range)
{
    if(index >= this->size())
    {
        throw std::out_of_range("index is larger than sizz");
    }
    auto it = this->begin();
    std::advance(it,index);
    return (T*)it->second.get();
};

template<typename T>
const T* openbiz::data::DataCollection<T>::get(const std::string &key) const throw(std::out_of_range)
{
    auto i = this->find(key);
    if (i == this->end()){
        throw std::out_of_range("key not found");
    }
    return i->second.get();
};

template<typename T>
void openbiz::data::DataCollection<T>::del(const std::string &key) throw (std::out_of_range){
    auto i = this->find(key);
    if (i == this->end()){
        throw std::out_of_range("key not found");
    }
    this->erase(i);
};

template<typename T>
const bool openbiz::data::DataCollection<T>::has(const std::string& key) const throw(){
    auto i = this->find(key);
    return i != this->end();
}

template<typename T>
void openbiz::data::DataCollection<T>::set(const std::string& key, T& item) throw(){
    std::shared_ptr<T> record = std::make_shared<T>(item);
    (*(this))[key]=record;
}
#endif
