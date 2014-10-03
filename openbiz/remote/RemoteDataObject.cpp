//
//  RemoteDataObject.cpp
//  libRestModel
//
//  Created by Jixian Wang on 14-10-2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "RemoteDataObject.h"
#include "restclient-cpp/restclient.h"
#include "json.h"

using namespace std;
namespace openbiz
{
   
    const string remote::DataObject::getId()
    {
        return "";
    };
    
    const string remote::DataObject::getBaseURI()
    {
        return "";
    };
    
    const string remote::DataObject::fetch()
    {
        cout<< this->getBaseURI()<< endl;
        RestClient::response r = RestClient::get(this->getBaseURI());
        if(r.code!=-1){
            const string result = r.body;
            Json::Reader reader;
            Json::StyledWriter writer;
            Json::Value root;
            reader.parse(r.body, root);
            return root["permissions"][0].asString();
//            return writer.write(root["app"]);
        }else{
            return "CONNECTION ERROR";
        }
    };
    
    const string remote::DataObject::serialize(){
        return "";
    };
    void remote::DataObject::deserialize(){
    
    };
}