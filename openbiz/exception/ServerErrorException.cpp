//
//  ServerErrorException.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-3.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "ServerErrorException.h"
#include "config.h"
#include "json.h"
namespace openbiz
{
    namespace exception
    {
        ServerErrorException::ServerErrorException(RestClient::response r) noexcept:
        method(r.method),
        payload(r.payload),
        uri(r.uri),
        _code(r.code)
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
            message += "URI: \t" + this->uri + "\n";
            if(!this->payload.empty())
            {
                message += "Payload: \t" + this->payload + "\n";
            }
            message += "Code: \t" + std::to_string(this->_code) + "\n";
            if(!this->_name.empty())
            {
                message += "Name: \t" + this->_name + "\n";
                message += "Message: \t" + this->_message + "\n";
            }
            if(!this->_data.empty())
            {
                message += "Data: \t" + this->_data + "\n";
            }
            return message.c_str();
        };
    }
}