//
//  RemoteDataObject.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "RemoteDataObject.h"
#include "restclient-cpp/restclient.h"

using namespace std;
namespace openbiz
{
   
    const string RemoteDataObject::getBaseURI()
    {
            return "";
    };
    
    const string RemoteDataObject::fetch()
    {
        cout<< this->getBaseURI()<< endl;
        RestClient::response r = RestClient::get(this->getBaseURI());
        const string result = r.body;
        return result;
    };
    
    const string RemoteDataObject::serialize(){
        return "";
    };
    void RemoteDataObject::deserialize(){
    
    };
}