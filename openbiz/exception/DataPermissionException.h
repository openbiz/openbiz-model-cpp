//
//  DataPermissionException.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/11/1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __Openbiz_RestModel__DataPermissionException__
#define __Openbiz_RestModel__DataPermissionException__

#include <stdio.h>
#include <iostream>
namespace openbiz{
    namespace exception
    {
        
        class DataPermissionException: public std::runtime_error
        {
        public:
            DataPermissionException(const char* msg):std::runtime_error(msg){};
        };
    }
}
#endif /* defined(__Openbiz_RestModel__DataPermissionException__) */
