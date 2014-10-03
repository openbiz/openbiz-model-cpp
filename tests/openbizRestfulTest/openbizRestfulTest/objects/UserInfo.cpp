//
//  UserInfo.cpp
//  openbizRestfulTest
//
//  Created by Jixian Wang on 14-10-2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "UserInfo.h"
#include "RemoteDataObject.h"
namespace GAPP{
    
    void User::test(){
        std::cout << "version is: " << this->getVersion() << this->fetch()<< std::endl;
    };
    

    
    const std::string User::getBaseURI(){
        return this->_baseUri;
    };
};