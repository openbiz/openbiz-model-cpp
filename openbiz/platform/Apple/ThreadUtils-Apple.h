//
//  ThreadUtils-Apple.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/12/16.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __Openbiz_RestModel__ThreadsUtils_Apple__
#define __Openbiz_RestModel__ThreadsUtils_Apple__

#include <stdio.h>
#include "ThreadUtils.h"
namespace openbiz
{
    namespace ext
    {
        class ThreadUtilsApple : public ThreadUtils
        {
        public:
            ThreadUtilsApple()=default;
            virtual const bool isOnMainThread() const;
        };
        
    }
}
#endif /* defined(__Openbiz_RestModel__FileUtils_Apple__) */