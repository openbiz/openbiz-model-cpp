//
//  ThreadUtils.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/12/16.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __Openbiz_RestModel__ThreadUtils__
#define __Openbiz_RestModel__ThreadUtils__

#include <stdio.h>
#include <iostream>

namespace openbiz
{
    namespace ext
    {
        class ThreadUtils
        {
        public:
            virtual ~ThreadUtils()=default;
            static ThreadUtils* getInstance();
            static void destroyInstance();
            virtual const bool isOnMainThread() const ;
        protected:
            ThreadUtils()=default;
            ThreadUtils(ThreadUtils const&);             // copy constructor is private
            ThreadUtils& operator=(ThreadUtils const&);  // assignment operator is private
            static ThreadUtils *_instance;
        };
    }
}
#endif /* defined(__Openbiz_RestModel__ThreadUtils__) */
