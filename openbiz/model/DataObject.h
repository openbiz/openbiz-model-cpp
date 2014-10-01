//
//  model.h
//  libRestModel
//
//  Created by Jixian Wang on 14-10-1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __libRestModel__DataObject__
#define __libRestModel__DataObject__

#include "openbiz.h"
#include <iostream>
#include <vector>
#include <stdio.h>


namespace openbiz
{
    class DataObject
    {
    public:
        DataObject()  = default;
        void set(std::string* key, std::string*  value);
        std::string get(std::string* key);
        
    protected:
        std::string _id;
    };
}

#endif /* defined(__libRestModel__DataObject__) */