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
    const string DataObject::serialize(){
        return this->_serializedData;
    };
    
    void DataObject::deserialize(){
    };
}