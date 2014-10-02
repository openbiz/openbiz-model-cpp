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
#include <string>
#include <stdio.h>


namespace openbiz
{
    class DataObject: public Object
    {
    public:
        DataObject()  = default;
        
//        DataObject parse();
        const std::string serialize();
        DataObject *deserialize();
        
    protected:
        const std::string _id;
        const std::string _serializedData;
        const std::string _baseUri;

        
    };
}

#endif /* defined(__libRestModel__DataObject__) */