//
//  DataArray_imp.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/11/12.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef Openbiz_RestModel_DataArray_imp_h
#define Openbiz_RestModel_DataArray_imp_h
#include <stdexcept>
#include "PlatformMacros.h"

template<typename T>
const std::string openbiz::data::DataArray<T>::serialize() const
{
    std::string dataString;
    if(_vector->cbegin()!=_vector->cend()){
        for(auto it=_vector->cbegin();it!=_vector->cend();it++){
            dataString += (std::string)(*it)+"\n";
        }
    }
    return dataString;
}

template<typename T>
void openbiz::data::DataArray<T>::parse(const std::string &data)
throw (openbiz::exception::DataFormatInvalidException)
{
    
}

#pragma mark - Constructor, ensure SQLite table exists
template<typename T>
openbiz::data::DataArray<T>::DataArray(const std::string &cacheName):
Object(),
_cacheName(cacheName),
_isCacheEnabled(!cacheName.empty())
{
    _vector = new std::vector<T>;
    if(_isCacheEnabled){
        openbiz::core::DB::getInstance()->ensureTableExists(_cacheName);
        fetch();
    }
};

template<typename T>
openbiz::data::DataArray<T>::DataArray():
DataArray("")
{

};

template<typename T>
openbiz::data::DataArray<T>::~DataArray()
{
    OPENBIZ_SAFE_DELETE(_vector);
};


template<typename T>
const bool openbiz::data::DataArray<T>::isEmpty() const
{
    return _vector->empty();
};

template<typename T>
const unsigned int openbiz::data::DataArray<T>::getTotalRecords() const
{
    return (unsigned int)_vector->size();
};

template<typename T>
void openbiz::data::DataArray<T>::clear()
{
    return _vector->clear();
};

template<typename T>
T& openbiz::data::DataArray<T>::get(const unsigned int index) const
{
    if(index>=0 && index<_vector->size())
        return _vector->at(index);
    else
        throw std::out_of_range("vector index out of range");
};

template<typename T>
void openbiz::data::DataArray<T>::set(const unsigned int index, T &data)
{
    if(index>=0 && index<_vector->size())
        return _vector->at(index) = data;
    else
        throw std::out_of_range("vector index out of range");
};


template<typename T>
void openbiz::data::DataArray<T>::add(const T &data)
{
    _vector->push_back(data);
};

template<typename T>
const bool openbiz::data::DataArray<T>::has(const T &data)
{
    if(_vector->cbegin()!=_vector->cend()){
        std::string stringData;
        stringData = static_cast<std::string>(data);
        for(auto it=_vector->cbegin();it!=_vector->cend();it++){
            if(stringData.compare((*it))==0){
                return true;
            }                
        }
    }
    return false;
};

#pragma mark - cache related feature
template<typename T>
void openbiz::data::DataArray<T>::save()
{
    if(!isCacheEnabled())return ;
    unsigned int records = getTotalRecords();
    if(records>0){
        openbiz::core::DB::getInstance()->removeAllRecords(_cacheName);
        for(unsigned int i=0;i<records;i++)
        {
            std::string stringData;
            stringData = static_cast<std::string>(get(i));
            openbiz::core::DB::getInstance()->insertRecord(_cacheName,std::to_string(i),stringData);
        }
    }
};

template<typename T>
void openbiz::data::DataArray<T>::fetch()
{
    if(!isCacheEnabled()) return ;
    const std::vector<openbiz::core::DB::Record> *records;
    records = openbiz::core::DB::getInstance()->fetchRecords(_cacheName);
    if(records->size()>0){
        for(auto it = records->cbegin(); it!= records->cend(); ++it )
        {
            T record;
            record = (*it).data;
            add(record);
        }
    }
    OPENBIZ_SAFE_DELETE(records);
};


template<typename T>
void openbiz::data::DataArray<T>::destroy()
{
    if(!isCacheEnabled())return ;
    openbiz::core::DB::getInstance()->removeAllRecords(_cacheName);
    clear();
};

template<typename T>
const bool openbiz::data::DataArray<T>::isCacheEnabled() const
{
    return _isCacheEnabled;
};
#endif
