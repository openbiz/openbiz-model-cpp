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
        
        enum DataPermission {
            Create,
            Write,
            Read,
            Delete
        };
        
        typedef std::map<std::string,std::string> QueryParameters;
        
        class DataObject: public data::DataObject
        {
        public:        
            explicit DataObject(const std::string &url,
                                const std::string &cacheName=""):
                _baseUrl(url),
                data::DataObject::DataObject(cacheName){};
            
            virtual ~DataObject() = default;
            
            virtual const std::string getUrl() const throw();
            virtual const QueryParameters getQueryParameters() const throw();
            
            //fetch from remote but dont update local cache
            virtual const bool fetch() throw (openbiz::exception::NetworkConnectionException,
                                              openbiz::exception::ServerErrorException) override;
            
            //save to local and push to remote
            const void save() throw (openbiz::exception::DataValidationException,
                                     openbiz::exception::NetworkConnectionException,
                                     openbiz::exception::ServerErrorException);
            
            //destroy remote and local cache
            const void destroy() throw (openbiz::exception::NetworkConnectionException,
                                        openbiz::exception::ServerErrorException);
            
        protected:
            virtual const bool _hasPermission(DataPermission permission) const throw();            
            time_t _lastSync;
            const std::string _baseUrl;
        };
    }
}
#endif /* defined(__libRestModel__RemoteDataObject__) */
