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
namespace openbiz
{
    namespace core
    {
        class DB
        {
        public:
            DB();
            ~DB();
            static DB* getInstance();
            static void destroyInstance();
            void initialize(const std::string &dbName);
            
            void ensureTableExists(const std::string &tableName) const;
            
            const bool isTableExists(const std::string &tableName) const;
            
            const bool isRecordExists(const std::string &tableName,
                                      const std::string &recordId) const;
            
            const bool insertRecord(const std::string &tableName,
                                    const std::string &recordId,
                                    const std::string &data) const;
            
            const bool updateRecord(const std::string &tableName,
                                    const std::string &recordId,
                                    const std::string &data) const;
            
            const sqlite3 *db();
        protected:
            static DB *_instance;
            static sqlite3 *_db;
        }; 
    }
}
#endif /* defined(__Openbiz_RestModel__DB__) */
