//
//  model.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "DataObject.h"
#include "exception.h"
#include "DB.h"

using namespace std;
using namespace openbiz::core;
using namespace openbiz::data;
using namespace openbiz::exception;

namespace openbiz
{    
#pragma mark - 重载父类方法
    void DataObject::parse(const std::string &data) throw (DataFormatInvalidException) {
        Json::Reader reader;
        bool result = reader.parse(data,this->_data);
        
        if(!result){
            throw DataFormatInvalidException(data);
        }
        
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
    const string DataObject::getId() const throw()
    {
        return this->_id;
    };    
    
    void DataObject::unset(std::string &key)
    {

    }
    
    
    void DataObject::clear()
    {
        this->_id.clear();
        this->_data.clear();
    }
    
    void DataObject::reset()
    {
        this->_data = this->_previousData;
    }
    
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
        if(!_isCacheEnabled) return false;
        //if no record ID, then cannot save it
        if(_id.empty()) return false;
        
        //ensure cache table exists
        DB::getInstance()->ensureTableExists(_cacheName);
        
        //is record exists in db
        if(DB::getInstance()->isRecordExists(_cacheName,_id)){
            //update record and timestamp
            DB::getInstance()->updateRecord(_cacheName,_id,serialize());
        }else{
            //create new record
            DB::getInstance()->insertRecord(_cacheName,_id,serialize());
        }
        
        //update timestamp
        _lastUpdate = std::time(nullptr);

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