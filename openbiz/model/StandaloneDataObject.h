//
//  StandaloneDataObject.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/12/4.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __Openbiz_RestModel__StandaloneDataObject__
#define __Openbiz_RestModel__StandaloneDataObject__

#include <stdio.h>
#include "DataObject.h"

namespace openbiz
{
    namespace data
    {
        class StandaloneDataObject : public openbiz::data::DataObject
        {
        public:
            explicit StandaloneDataObject(const std::string &cacheName);
            virtual ~StandaloneDataObject();
        };
    }
}
#endif /* defined(__Openbiz_RestModel__StandaloneDataObject__) */
