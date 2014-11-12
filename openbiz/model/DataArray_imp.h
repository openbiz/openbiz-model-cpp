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

#pragma mark - Constructor, ensure SQLite table exists
template<typename T>
openbiz::data::DataArray<T>::DataArray(const std::string &cacheName):
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
    delete _vector;
    _vector = nullptr;
};


template<typename T>
const bool openbiz::data::DataArray<T>::isEmpty() const
{
    return _vector->empty();
};

template<typename T>
const unsigned int openbiz::data::DataArray<T>::getTotalRecords() const
{
    return _vector->size();
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
        return _vector[index];
    else
        throw std::out_of_range("vector index out of range");
};

template<typename T>
void openbiz::data::DataArray<T>::set(const unsigned int index, T &data)
{
    if(index>=0 && index<_vector->size())
        return _vector[index] = data;
    else
        throw std::out_of_range("vector index out of range");
};


template<typename T>
void openbiz::data::DataArray<T>::add(T &data)
{
    _vector->push_back(data);
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
            if(typeid(T) == typeid(std::string) )
            {
                stringData = get(i);
            }else{
                stringData = get(i)->serialize();
            }
            openbiz::core::DB::getInstance()->insertRecord(_cacheName,i,stringData);
        }
    }
};

template<typename T>
void openbiz::data::DataArray<T>::fetch()
{
    if(!isCacheEnabled()) return ;
    const std::vector<openbiz::core::DB::record*> *records;
    records = openbiz::core::DB::getInstance()->fetchRecords(_cacheName);
    if(records->size()>0){
        for(auto it = records->cbegin(); it!= records->cend(); ++it )
        {
            T record;
            if(typeid(T) == typeid(std::string))
            {
                record = (*it)->data;
            }
            else
            {
                record = static_cast<T>((*it)->data);
            }
            add(record);
        }
    }
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
