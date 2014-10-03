//
//  RemoteDataObject.h
//  libRestModel
//
//  Created by Jixian Wang on 14-10-2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __libRestModel__RemoteDataObject__
#define __libRestModel__RemoteDataObject__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "DataObject.h"

namespace openbiz
{
    namespace remote
    {
        class DataObject: public data::DataObject
        {
        public:
            DataObject()  = default;
            const std::string fetch();
            virtual const std::string getId();
            
        protected:
            const std::string _id;
            virtual const std::string getBaseURI() =0;
            virtual const std::string serialize() override;
            virtual void deserialize() override;
            
        };
    }
}
#endif /* defined(__libRestModel__RemoteDataObject__) */
