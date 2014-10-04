//
//  model.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "DataObject.h"
using namespace std;

namespace openbiz
{
    
    const string data::DataObject::getId()
    {
        return "";
    };
    
    void data::DataObject::parse(std::string data){
        Json::Reader reader;
        reader.parse(data,this->_data);
    }
    
    const std::string data::DataObject::serialize()
    {
        return this->_data.toStyledString();
    }
    
    const bool data::DataObject::save(){
        cout<< this->_cacheName <<endl;
        return true;
    }
    

    
}