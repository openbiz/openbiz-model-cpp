//
//  model.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "DataObject.h"
using namespace std;
using namespace openbiz::data;

namespace openbiz
{
#pragma mark - 重载父类方法
    void DataObject::parse(const std::string &data ){
        Json::Reader reader;
        reader.parse(data,this->_data);
        
        //尝试给ID赋值
        if(this->_data["_id"].isString()){
            this->_id = this->_data["_id"].asString();
        }
    }
    
    const string DataObject::serialize() const
    {
        return this->_data.toStyledString();
    }

#pragma mark - 实现自己的方法
    template<typename T> void DataObject::set(std::string &key, T value)
    {
        this->_data[key]=value;
        this->_changed[key]=value;
    }
    
    void DataObject::unset(std::string &key)
    {

    }
    
    

    
    const string DataObject::getId() const throw()
    {
        return this->_id;
    };
    
    
    const bool DataObject::fetch()
    {
        return true;
    }
    
    const bool DataObject::destroy()
    {
        return true;
    }
    
    const bool DataObject::save()
    {
        cout<< this->_cacheName <<endl;
        return true;
    }
    
    const bool DataObject::isNew() const throw()
    {
        return !this->_id.empty();
    }
    
    const bool DataObject::hasChanged() const throw()
    {
        return !this->_changed.isNull();
    }
}