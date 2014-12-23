//
//  DataArray.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14/11/2.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __Openbiz_RestModel__DataArray__
#define __Openbiz_RestModel__DataArray__

#include <stdio.h>
#include <vector>
#include <memory>
#include "DB.h"
#include "Object.h"

#define OPENBIZ_DATA_ARRAY_API \
using DataArray::isEmpty; \
using DataArray::getTotalRecords; \
using DataArray::clear; \
using DataArray::get; \
using DataArray::add; \
using DataArray::set;

namespace openbiz
{
    namespace data
    {
        template<typename T>
        class DataArray: public core::Object
        {
        public:
            explicit DataArray();
            explicit DataArray(const std::string &cacheName);
            virtual ~DataArray();
            
            const std::string serialize() const;
            void parse(const std::string &data) throw (openbiz::exception::DataFormatInvalidException);

            
            const bool isEmpty() const;
            const unsigned int getTotalRecords() const;
            T& get(const unsigned int index) const;
            void add(const T &data);
            void set(const unsigned int index, T &data);
            const bool has(const T &data);
            void clear();
            
            //local persisent cache feature
            void fetch();
            void destroy();
            void save();
            const bool isCacheEnabled() const;
            
        protected:
            std::vector<T> *_vector;
            const bool _isCacheEnabled;
            const std::string _cacheName;
        };
    }
}

#include "DataArray_imp.h"
#endif /* defined(__Openbiz_RestModel__DataArray__) */
