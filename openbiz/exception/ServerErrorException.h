//
//  ServerErrorException.h
//  libRestModel
//
//  Created by Jixian Wang on 14-10-3.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef libRestModel_ServerErrorException_h
#define libRestModel_ServerErrorException_h
#include <stdio.h>
#include <iostream>
#include "restclient.h"

namespace openbiz{
    namespace exception
    {

        class ServerErrorException: public std::exception
        {
        public:
            ServerErrorException(const std::string &method,
                                 const std::string &uri) noexcept
                                :method(method),uri(uri){} ;
            
            ServerErrorException(const std::string &method,
                                 const std::string &uri,
                                 unsigned int code) noexcept
                                :method(method),uri(uri),_code(code){};
            
            //如果500错误服务器处于生产模式，没有给出详细信息就调用这个
            ServerErrorException(const std::string &method,
                                 const std::string &uri,
                                 unsigned int code,
                                 const std::string &name,
                                 const std::string &message) noexcept
                                :method(method),uri(uri),_code(code),
                                _name(name),_message(message){};
            
            //如果500错误服务器处于开发模式，有给出详细信息就调用这个
            ServerErrorException(const std::string &method,
                                 const std::string &uri,
                                 unsigned int code,
                                 const std::string &name,
                                 const std::string &message,
                                 const std::string &data) noexcept
                                :method(method),uri(uri),_code(code),_name(name),
                                _message(message),_data(data){};

            //直接传递RestClient::response对象过来 巨省事儿~
            ServerErrorException(RestClient::response r) noexcept;
            
           
            const std::string uri;
            const std::string method;
            const std::string payload;
            virtual const char* what() const throw();

            inline const unsigned int getCode() const   {return this->_code;};
            inline const std::string getName() const    {return this->_name.c_str();};
            inline const std::string getMessage() const {return this->_message.c_str();};
            inline const std::string getData() const    {return this->_data.c_str();};
            
            
        protected:
            unsigned int _code;
            std::string _name;
            std::string _message;
            std::string _data;
        };
    }
}
#endif
