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
        message += "URI: \t" + this->uri + "\n";
        message += "Timeout: \t" + std::to_string(BIZ_NETWORK_CONNECTION_TIMEOUT) + "\n";
        return message.c_str();
    };
}