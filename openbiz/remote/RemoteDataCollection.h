//
//  RemoteDataCollection.h
//  libRestModel
//
//  Created by Jixian Wang on 14-10-2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __libRestModel__RemoteDataCollection__
#define __libRestModel__RemoteDataCollection__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include "DataCollection.h"
#include "RemoteDataObject.h"



namespace openbiz
{
    namespace remote
    {
        enum RemotePaging {
            Supported,
            NotSupported
        };
        
        template<typename T>
        class DataCollection: public openbiz::data::DataCollection<T>
        {
        public:
           
            DataCollection(const std::string &url,
                           const std::string &cacheName="",
                           const RemotePaging usingRemotePaging = RemotePaging::Supported);
            virtual ~DataCollection() = 0;
            
            virtual const std::string getUrl() const throw();
            void fetch();
            void refresh();
            
        protected:
            virtual const bool _hasPermission(DataPermission permission) const throw();            
            virtual const QueryParameters getQueryParameters() const throw();
            QueryParameters _presetQueryParameters;
            bool _isUsingCachedData;
            void _processFetchedData(const RestClient::response &r);
            const std::string _baseUrl;
            const bool _usingRemotePaging;

        };
    };
}

#include "RemoteDataCollection_imp.h"
#endif /* defined(__libRestModel__RemoteDataCollection__) */
