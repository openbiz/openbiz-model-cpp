//
//  DataCollection.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "DataCollection.h"

using namespace std;
using namespace openbiz;
using namespace openbiz::data;
using namespace openbiz::exception;

namespace openbiz
{
#pragma mark - 重载父类方法
    void DataCollection::parse(const std::string &data) throw (DataFormatInvalidException) {
        Json::Reader reader;
        bool result = reader.parse(data,this->_data);
        
        if(!result){
            throw DataFormatInvalidException(data);
        }
        
        if(this->_data.empty()) return;

        //创建每一个成员变量去
        for(auto it = _data.begin(); it!= _data.end(); ++it ){
            DataObject *record = new DataObject();
            if(it->isObject()){
                record->parse(it->toStyledString());
            }
            _records.push_back(record);
        }

    }
    
    const string DataCollection::serialize() const
    {
        return this->_data.toStyledString();
    }
    
    

    const std::vector<DataObject*> DataCollection::fetch(int limit,int offset)
    {
        return this->_records;
    }

    
    const std::vector<DataObject*> DataCollection::query(const std::string &keyword,int limit,int offset){
        return this->_records;
    }
    
    
}