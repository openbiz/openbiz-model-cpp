//
//  DataFormatInvalidException.cpp
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-6.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "DataFormatInvalidException.h"
namespace openbiz
{
    const char* exception::DataFormatInvalidException::what() const throw()
    {
        std::string message;
        message += "JSON Data is invalid: \n";
        if(!this->data.empty()){
            message += "Data: \n" + this->data + "\n";
        }
        return message.c_str();
    };
}