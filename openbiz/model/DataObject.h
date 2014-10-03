//
//  model.h
//  libRestModel
//
//  Created by Jixian Wang on 14-10-1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __libRestModel__DataObject__
#define __libRestModel__DataObject__

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include "Object.h"

namespace openbiz
{
    namespace data
    {
        class DataObject: public core::Object
        {
        public:
            DataObject()  = default;
            virtual const std::string serialize();
            virtual void deserialize();
            
            
        protected:
            const std::string _serializedData;
            
        };
    };
}

#endif /* defined(__libRestModel__DataObject__) */