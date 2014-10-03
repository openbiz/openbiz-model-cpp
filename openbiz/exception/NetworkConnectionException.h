//
//  NetworkConnectionException.h
//  libRestModel
//
//  Created by Jixian Wang on 14-10-3.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef libRestModel_NetworkConnectionException_h
#define libRestModel_NetworkConnectionException_h
#include <stdio.h>
#include <iostream>

namespace openbiz
{
    namespace exception
    {
        
        class NetworkConnectionException: public std::logic_error{
        public:
            explicit NetworkConnectionException(const std::string s):logic_error(s){};
            NetworkConnectionException(const std::string msg,const std::string uri, unsigned int timeout);
        };
    }
}
#endif
