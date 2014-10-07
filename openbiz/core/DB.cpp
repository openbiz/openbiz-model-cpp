//
//  DB.cpp
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-7.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include <iostream>
#include <stdexcept>
#include "DB.h"
#include "PlatformMacros.h"
#include "FileUtils.h"

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
                throw std::runtime_error("Please define a db name");
            }
            return _db;
        };
        
        void DB::initialize(const std::string &dbName)
        {
            if(!dbName.empty()){
                const std::string path = ext::FileUtils::getInstance()->getWritablePath();
                const std::string dbFullname = path + "/" + dbName;
                int result = sqlite3_open(dbFullname.c_str(),&_db);
                if(result){
                    throw std::runtime_error("Con't open database file: "+dbFullname);
                }
                
            }else{
                throw std::runtime_error("Please define a db name");
            }
        }
        
        void DB::destroyInstance(){
            BIZ_SAFE_DELETE(_instance);
        };
    }
}