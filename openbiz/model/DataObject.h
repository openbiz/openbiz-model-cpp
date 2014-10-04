//
//  model.h
//  libRestModel
//
//  Created by Jixian Wang on 14-10-1.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __libRestModel__DataObject__
#define __libRestModel__DataObject__

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <time.h>
#include "Object.h"
#include "json.h"


namespace openbiz
{
    namespace data
    {
        class DataObject: public core::Object
        {
        public:
            typedef struct {
                std::string cacheName;
                bool isCacheEnabled;
            } Metadata;
            
            DataObject():_isCacheEnabled(false){};
            
            DataObject(Metadata *metadata):
                _isCacheEnabled(metadata->isCacheEnabled),
                _cacheName(metadata->cacheName){};
            
            const std::string getId();
            virtual const std::string serialize();
            virtual void parse(std::string data);
            virtual const bool save();
//            virtual const std::string getCacheName();
//            bool isNew();
//            bool hasChanged();
//            bool hasChanged(std::string attribute);
            
        protected:
            std::string _id;
            Json::Value _data;
            Json::Value _changed;
            time_t _lastUpdate;
            const bool _isCacheEnabled;
            std::string _cacheName;
            

        };
    };
}

#endif /* defined(__libRestModel__DataObject__) */