//
//  Util.cpp
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/11/4.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "Util.h"
#include <string>
#include <sstream>
#include <iostream>
#include "openbiz.h"

time_t openbiz::util::convertISOTime(const std::string &time){
    struct tm tm;
    struct tm tm2;
    strptime(time.c_str(), "%FT%TZ", &tm);
    time_t t = mktime(&tm);
    tm2 = *gmtime(&t);
    time_t t2=mktime(&tm);
    return t2;
};