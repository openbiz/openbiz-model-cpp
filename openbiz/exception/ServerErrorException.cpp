//
//  ServerErrorException.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-3.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//
#include <stdio.h>
#include "ServerErrorException.h"
#include "config.h"
#include "json.h"
namespace openbiz
{
    namespace exception
    {
        ServerErrorException::ServerErrorException(RestClient::response r) throw():
        method(r.method),
        payload(r.payload),
        url(r.url),
        _code(r.code),
        _raw(r.body)
        {
            Json::Value data;
            Json::Reader reader;
            Json::StyledWriter writer;
            reader.parse(r.body,data);
            if(data["code"].isInt())
            {
                this->_code = data["code"].asInt() ;
            }
            if(data["name"].isString())
            {
                this->_name = data["name"].asString() ;
            }
            if(data["message"].isString())
            {
                this->_message = data["message"].asString() ;
            }
            if(data["data"].isObject())
            {
                this->_data = writer.write(data["data"]) ;
            }
        }
        
        const char* ServerErrorException::what() const throw()
        {

            std::string message;
            message += "Remote Server Error Exception: \n";
            message += "Method: \t" + this->method + "\n";
            message += "URL: \t" + this->url + "\n";
            if(!this->payload.empty())
            {
                message += "Payload: \t" + this->payload + "\n";
            }
#if (BIZ_TARGET_PLATFORM != BIZ_TARGET_PLATFORM)
            //std::to_string is not availble for android NDK
            message += "Code: \t" + std::to_string(_code) + "\n";
#endif
            if(!this->_name.empty())
            {
                message += "Name: \t" + this->_name + "\n";
                message += "Message: \t" + this->_message + "\n";
            }
            if(!this->_data.empty())
            {
                message += "Data: \t" + this->_data + "\n";
            }
            message += "Raw:\n";
            message += _raw;
            return message.c_str();
        };
    }
}
