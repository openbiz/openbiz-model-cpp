//
//  Object.h
//  libRestModel
//
//  Created by Jixian Wang on 14-10-2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __libRestModel__Object__
#define __libRestModel__Object__

#include <stdio.h>
#include <iostream>

namespace openbiz
{
    namespace core
    {
        class Object
        {
        public:
            Object() = default;
            virtual ~Object() = default;
            virtual const std::string getVersion();
            virtual const std::string serialize() = 0;
            virtual void deserialize() = 0;
        };
    };
}
#endif /* defined(__libRestModel__Object__) */
