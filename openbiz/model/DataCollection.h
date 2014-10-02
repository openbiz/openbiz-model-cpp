//
//  DataCollection.h
//  libRestModel
//
//  Created by Jixian Wang on 14-10-1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//
#ifndef __libRestModel__DataCollection__
#define __libRestModel__DataCollection__

#include "openbiz.h"
#include <stdio.h>
#include <vector>

namespace openbiz
{
    class DataCollection:public Object
    {
    public:
        DataCollection() = default;
        virtual ~DataCollection() = default;
        const std::string serialize();
        DataCollection *deserialize();
        std::vector<openbiz::DataObject> fetch();
        std::vector<openbiz::DataObject> query(int limit,int offset);
        std::vector<openbiz::DataObject> query(const std::string keyword,int limit,int offset);

    protected:
        std::vector<openbiz::DataObject> _records;
        const std::string _baseUri;
    };
}

#endif /* defined(__libRestModel__DataCollection__) */