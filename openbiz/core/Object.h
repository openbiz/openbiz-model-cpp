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
            Object();
            virtual ~Object() = 0;
            virtual const std::string serialize();
            virtual void parse(const std::string &data);
            
            Object* retain();
            unsigned int release();
            unsigned int release() const;
            
        protected:
        private:
            unsigned int _refCount;
        };
    };
}
#endif /* defined(__libRestModel__Object__) */
