//
//  model.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "DataObject.h"
#include "exception.h"

using namespace std;
using namespace openbiz::core;
using namespace openbiz::data;
using namespace openbiz::exception;

namespace openbiz
{    
#pragma mark - 重载父类方法
    void DataObject::parse(const std::string &json) throw (DataFormatInvalidException) {
        Json::Reader reader;
        bool result = reader.parse(json,this->_data);
        
        if(!result){
            throw DataFormatInvalidException(json);
        }
        
        //尝试给ID赋值
        if(this->_data["_id"].isString()){
            this->_id = this->_data["_id"].asString();
        }
        
        //save it to previous data
        reader.parse(json,this->_previousData);
        
        _changed.clear();
    }
        
    const string DataObject::serialize() const
    {
        return this->_data.toStyledString();
    }

#pragma mark - 实现自己的方法
    DataObject::DataObject(const std::string &cacheName):
    _isCacheEnabled(!cacheName.empty()),
    _cacheName(cacheName){

    }
    
    const string DataObject::getId() const throw()
    {
        return this->_id;
    }
    
    void DataObject::unset(std::string &key)
    {
        _data.removeMember(key);
        _changed[key]=Json::nullValue;
    }
    
    const bool DataObject::validate() throw (exception::DataValidationException)
    {
        return true;
    }
    
    void DataObject::clear()
    {
        this->_id.clear();
        this->_data.clear();
        this->_changed.clear();
        this->_previousData.clear();
    }
    
    void DataObject::reset()
    {
        this->_data = this->_previousData;
    }
    
    const bool DataObject::fetch()
    {
        if(!this->isCacheEnabled()) return false;
        if(this->isNew()) return false;
        
        DB::getInstance()->ensureTableExists(_cacheName);
        const DB::record *record = DB::getInstance()->fetchRecord(_cacheName,_id);
        if(record!=nullptr)
        {
            //fetch record content
            this->parse(record->data);
            _lastUpdate = record->timestamp;
            return true;
        }
        return false;
    }
    
    const void DataObject::destroy()
    {
        if(this->isNew())
        {
            this->clear();
            return;
        }
        
        
        DB::getInstance()->ensureTableExists(_cacheName);
        DB::getInstance()->removeRecord(_cacheName,_id);
        
        this->clear();
        return;
    }
    
    const bool DataObject::hasCachedData() const throw()
    {
        //ensure cache table exists
        DB::getInstance()->ensureTableExists(_cacheName);
        return DB::getInstance()->isRecordExists(_cacheName,_id);
    }
    
    const void DataObject::save() throw(openbiz::exception::DataValidationException)
    {
        if(!this->isCacheEnabled()) return;

        //if no record ID, then cannot save it
        if(this->isNew()) return;
        
        //validate data before save
        if(!this->validate()) return;
        
        //is record exists in db
        if(this->hasCachedData())
        {
            if(!this->hasChanged()) return;
            
            //update record and timestamp
            DB::getInstance()->updateRecord(_cacheName,_id,serialize());
        }else{
            //create new record
            DB::getInstance()->insertRecord(_cacheName,_id,serialize());
        }
        
        //update timestamp
        _lastUpdate = time(nullptr);
        
        _previousData = _data;
        _changed.clear();
        return;
    }
    
    const bool DataObject::isCacheEnabled() const throw()
    {
        return this->_isCacheEnabled;
    }
    
    const bool DataObject::isNew() const throw()
    {
        return ( this->_id.empty() && this->_previousData.empty() );
    }
    
    const bool DataObject::hasChanged() const throw()
    {
        if(this->_changed.isNull()) return false;
        return (this->_changed.size()>0);
    }
    
}