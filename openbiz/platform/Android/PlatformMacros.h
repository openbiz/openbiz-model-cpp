//
//  PlatformMarcos.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-5.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef Openbiz_RestModel_PlatformMarcos_h
#define Openbiz_RestModel_PlatformMarcos_h

#include <string>
#include <sstream>

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}


#endif