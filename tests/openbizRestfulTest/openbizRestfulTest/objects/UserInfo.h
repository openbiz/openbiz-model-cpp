//
//  UserInfo.h
//  openbizRestfulTest
//
//  Created by Jixian Wang on 14-10-2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __openbizRestfulTest__UserInfo__
#define __openbizRestfulTest__UserInfo__

#include "openbiz.h"
#include <stdio.h>
namespace GAPP{
    class User:public openbiz::RemoteDataObject
    {
    public:
        User()=default;
        ~User()=default;
        void test();
        
    protected:
        const std::string _baseUri = "http://v2.pickatale.com/manifest.json";
        const std::string getBaseURI();

    };
    
}
#endif /* defined(__openbizRestfulTest__UserInfo__) */
