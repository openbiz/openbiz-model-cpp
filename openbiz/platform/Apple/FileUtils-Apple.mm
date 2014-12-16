//
//  FileUtils-Apple.cpp
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-5.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "FileUtils-Apple.h"

namespace openbiz
{
    namespace ext
    {
        static NSFileManager* s_fileManager = [NSFileManager defaultManager];
        FileUtils* FileUtils::getInstance()
        {
            if (_instance == nullptr)
            {
                _instance = new (std::nothrow) FileUtilsApple();                
            }
            return _instance;
        }
        
        const std::string FileUtilsApple::getWritablePath() const
        {
            // save to document folder
            NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
            NSString *documentsDirectory = [paths objectAtIndex:0];
            std::string strRet = [documentsDirectory UTF8String];
            strRet.append("/");
            return strRet;
        }
    }
}