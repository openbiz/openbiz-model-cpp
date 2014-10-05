//
//  FileUtils.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-5.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef Openbiz_RestModel_FileUtils_h
#define Openbiz_RestModel_FileUtils_h

#include <stdio.h>
#include <iostream>

namespace openbiz
{
    namespace ext
    {
        class FileUtils
        {
        public:
            virtual ~FileUtils();
            static FileUtils* getInstance();
            static void destroyInstance();
            virtual std::string getWritablePath() const = 0;
        protected:
            FileUtils();
            FileUtils(FileUtils const&);             // copy constructor is private
            FileUtils& operator=(FileUtils const&);  // assignment operator is private
            static FileUtils *_instance;
        };
    }
}
#endif
