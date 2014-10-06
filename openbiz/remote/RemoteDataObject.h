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
            DataObject(const std::string &url,
                       const std::string &cacheName=""):
                _baseUrl(url),
                data::DataObject::DataObject(cacheName){};
            
            ~DataObject() = default;
            
            virtual const std::string getUrl() const throw();
            
            //fetch from remote but dont update local cache
            virtual const bool fetch() throw (openbiz::exception::NetworkConnectionException) override;
            
            //fetch from remote and update local cache
            virtual const bool sync();
            
            //save to local and push to remote
            virtual const bool save() override;
            
            //destroy remote and local cache
            virtual const bool destroy() throw (openbiz::exception::NetworkConnectionException) override;
            
        protected:
            std::string _id;
            const std::string _baseUrl;
            
        };
    }
}
#endif /* defined(__libRestModel__RemoteDataObject__) */
