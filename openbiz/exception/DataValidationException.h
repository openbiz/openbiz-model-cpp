//
//  DataValidationException.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/10/20.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __Openbiz_RestModel__DataValidationException__
#define __Openbiz_RestModel__DataValidationException__

#include <stdio.h>
#include <iostream>

namespace openbiz{
    namespace exception
    {
        
        class DataValidationException: public std::runtime_error
        {
        public:
            
        };
    }
}
#endif /* defined(__Openbiz_RestModel__DataValidationException__) */
