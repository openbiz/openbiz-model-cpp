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
#include "exception.h"

namespace openbiz
{
    namespace remote
    {
        class DataObject: public data::DataObject
        {
        public:
            typedef struct {
                std::string uri;
                std::string cacheName;
                bool isCacheEnabled;
                operator openbiz::data::DataObject::Metadata *();
            } Metadata;
            
            explicit DataObject(Metadata *metadata):
                _baseUri(metadata->uri),
            data::DataObject::DataObject( static_cast<openbiz::data::DataObject::Metadata *>(*metadata)){};
            
            ~DataObject() = default;
            //fetch from remote but dont update local cache
            virtual const bool fetch();
            
            //fetch from remote and update local cache
            virtual const bool sync();
            
            //save to local and push to remote
            virtual const bool save() override;
            
        protected:
            std::string _id;
            const std::string _baseUri;
            
        };
    }
}
#endif /* defined(__libRestModel__RemoteDataObject__) */
