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
            :url(r.url),method(r.method){} ;
            
            NetworkConnectionException(const std::string &url)
                :url(url){} ;
            
            NetworkConnectionException(const std::string &method,const std::string &url)
                :method(method),url(url){} ;
            
            const std::string method;
            const std::string url;
            virtual const char* what() const throw();
        };
    }
}
#endif
