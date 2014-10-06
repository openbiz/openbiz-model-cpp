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
#include "restclient.h"

namespace openbiz
{
    namespace exception
    {
        
        class NetworkConnectionException: public std::exception
        {
        public:
            //直接传递RestClient::response对象过来 巨省事儿~
            NetworkConnectionException(RestClient::response r)
            :uri(r.uri),method(r.method){} ;
            
            NetworkConnectionException(const std::string &uri)
                :uri(uri){} ;
            
            NetworkConnectionException(const std::string &method,const std::string &uri)
                :method(method),uri(uri){} ;
            
            const std::string method;
            const std::string uri;
            virtual const char* what() const throw();
        };
    }
}
#endif
