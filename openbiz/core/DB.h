//
//  DB.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-7.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef __Openbiz_RestModel__DB__
#define __Openbiz_RestModel__DB__

#include <stdio.h>
#include <sqlite3.h>
#include <iostream>
#include <stdexcept>
#include <mutex>
#include "Object.h"

namespace openbiz
{
    namespace core
    {
        class DB
        {
        public:
            struct Record : public openbiz::core::Object
            {
                std::string Id;
                std::string data;
                time_t timestamp;
            };
            
            DB();
            ~DB();
            static DB* getInstance();
            static void destroyInstance();
            static void dropDatabase();
            static void recreateDatabase();
            
            void initialize(const std::string &dbName);
            
            void ensureTableExists(const std::string &tableName) const;
            
            const bool isTableExists(const std::string &tableName) const;
            
            const bool isRecordExists(const std::string &tableName,
                                      const std::string &recordId) const;
            
            const Record* fetchRecord(const std::string &tableName,
                                      const std::string &recordId) const;
            
            const bool insertRecord(const std::string &tableName,
                                    const std::string &recordId,
                                    const std::string &data) const;
            
            const bool updateRecord(const std::string &tableName,
                                    const std::string &recordId,
                                    const std::string &data) const;
            
            const bool removeRecord(const std::string &tableName,
                                    const std::string &recordId) const;
            
            const bool removeAllRecords(const std::string &tableName) const;
            
            const std::vector<Record> *fetchRecords(const std::string &tableName,
                                                    int offset=0,
                                                    int limit=-1) const;
            
            const std::vector<Record> *fetchRecords(const std::string &tableName,
                                                     const std::string &keyword,
                                                     int offset=0,
                                                     int limit=-1) const;
            
            unsigned int countRecords(const std::string &tableName);
            unsigned int countRecords(const std::string &tableName,const std::string &keyword);
            
            const sqlite3 *db();
            
        protected:
            static DB *_instance;
            static sqlite3 *_db;
            static std::mutex _mtx;
            static std::string _dbName;
        }; 
    }
}
#endif /* defined(__Openbiz_RestModel__DB__) */
