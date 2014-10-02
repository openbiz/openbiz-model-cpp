//
//  UserInfo.h
//  openbizRestfulTest
//
//  Created by Jixian Wang on 14-10-2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __openbizRestfulTest__UserInfo__
#define __openbizRestfulTest__UserInfo__

#include <openbiz.h>
#include <stdio.h>
namespace GAPP{
    class User:public openbiz::DataObject
    {
    public:
        User()=default;
        virtual ~User()=default;
        void test();
    };
    
}
#endif /* defined(__openbizRestfulTest__UserInfo__) */
