//
//  NetworkConnectionException.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-3.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "NetworkConnectionException.h"
#include "config.h"

namespace openbiz
{
    const char* exception::NetworkConnectionException::what() const throw()
    {
        std::string message;
        message += "Network Connection Exception: \n";
        if(!this->method.empty()){
            message += "Method: \t" + this->method + "\n";
        }
        message += "URL: \t" + this->url + "\n";
#if (BIZ_TARGET_PLATFORM != BIZ_TARGET_PLATFORM)
        //std::to_string is not availble for android NDK
        message +=  "TIMEOUT: \t" + std::to_string(OPENBIZ_NETWORK_CONNECTION_TIMEOUT) + "\n";
#endif
        return message.c_str();
    };
}