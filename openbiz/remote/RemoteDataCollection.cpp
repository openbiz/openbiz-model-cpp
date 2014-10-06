//
//  RemoteDataCollection.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "RemoteDataCollection.h"

using namespace std;
using namespace openbiz;
using namespace openbiz::remote;
using namespace openbiz::exception;

namespace openbiz
{
    const std::string DataCollection::getUrl() const throw()
    {
        return this->_baseUrl.c_str();
    }
    

    const std::vector<openbiz::data::DataObject *> DataCollection::fetch(int limit,int offset)
    {
        std::cout<<"test test"<<std::endl;
        RestClient::response r = RestClient::get(this->getUrl());
        switch(r.code)
        {
            case -1:
                throw NetworkConnectionException(r);
                break;
                break;
            case 200:
                data::DataCollection::parse(r.body);
                break;
            case 204:
            default:
                break;                
        }
        return _records;
    }

    const std::vector<openbiz::data::DataObject *> DataCollection::query(const std::string &keyword,int limit,int offset){
        return _records;
    }
}