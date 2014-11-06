//
//  Util.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/11/4.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __Openbiz_RestModel__Util__
#define __Openbiz_RestModel__Util__

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>

namespace openbiz
{
    namespace util
    {
        template<typename T> std::string to_string(const T &value){
            std::ostringstream os ; os << value ; return os.str();
        };
        time_t convertISOTime(const std::string &time);
    }
}
#endif /* defined(__Openbiz_RestModel__Util__) */
