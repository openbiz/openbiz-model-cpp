//
//  DataFormatInvalidException.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-6.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __Openbiz_RestModel__DataFormatInvalidException__
#define __Openbiz_RestModel__DataFormatInvalidException__

#include <stdio.h>
#include <iostream>

namespace openbiz
{
    namespace exception
    {
        
        class DataFormatInvalidException: public std::exception
        {
        public:
            DataFormatInvalidException(const std::string &data):data(data){};
            const std::string data;
            virtual const char* what() const throw();
        };
    }
}
#endif /* defined(__Openbiz_RestModel__DataFormatInvalidException__) */
