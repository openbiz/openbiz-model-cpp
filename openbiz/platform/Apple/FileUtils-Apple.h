//
//  FileUtils-Apple.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-5.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __Openbiz_RestModel__FileUtils_Apple__
#define __Openbiz_RestModel__FileUtils_Apple__

#include <stdio.h>
#include "FileUtils.h"
namespace openbiz
{
    namespace ext
    {
        class FileUtilsApple : public FileUtils
        {
        public:
            FileUtilsApple()=default;
            virtual const std::string getWritablePath() const override;
        };
        
    }
}
#endif /* defined(__Openbiz_RestModel__FileUtils_Apple__) */
