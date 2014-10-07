//
//  DB.cpp
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-7.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include "DB.h"
#include "PlatformMacros.h"

namespace openbiz
{
    namespace core
    {
        DB* DB::_instance = nullptr;
        sqlite3* DB::_db = nullptr;
        DB::~DB(){};
        DB::DB(){};
        
        DB* DB::getInstance()
        {
            if (_instance == nullptr)
            {
                _instance = new DB();
            }
            return _instance;
        }
        
        const sqlite3* DB::db(){
            if(_db==nullptr)
            {
            
            }
            return _db;
        };
        
        void DB::destroyInstance(){
            BIZ_SAFE_DELETE(_instance);
        };
    }
}