//
//  DB.cpp
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-7.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#include <iostream>
#include <stdexcept>
#include <vector>
#include <regex>
#include "DB.h"
#include "PlatformMacros.h"
#include "FileUtils.h"
#include "sqlite3_json_extension.h"

#define OPENBIZ_CACHE_CREATE_TABLE_SQL(tableName) \
    "CREATE TABLE IF NOT EXISTS `"+tableName+"` (`id` PRIMARY KEY, `timestamp` NUMERIC, `data` TEXT);"

#define OPENBIZ_CACHE_DROP_TABLE_SQL(tableName) \
    "DROP TABLE IF EXISTS `"+tableName+"` ;"

#define OPENBIZ_CACHE_CHECK_TABLE_EXISTS_SQL \
    "SELECT 1 FROM `sqlite_master` WHERE `type`='table' AND `name`= ? ;"

#define OPENBIZ_CACHE_CHECK_RECORD_EXISTS_SQL(tableName) \
    "SELECT `id`,`data`,`timestamp` FROM `"+tableName+"` WHERE `id`= ? ;"

#define OPENBIZ_CACHE_FETCH_RECORD_SQL(tableName) \
    "SELECT `id`,`data`,`timestamp` FROM `"+tableName+"` WHERE `id`= ? ;"

#define OPENBIZ_CACHE_FETCH_RECORDS_SQL(tableName) \
    "SELECT `id`,`data`,`timestamp` FROM `"+tableName+"` LIMIT ?,?;"

#define OPENBIZ_CACHE_QUERY_RECORDS_SQL(tableName) \
    "SELECT `id`,`data`,`timestamp` FROM `"+tableName+"` WHERE JSON_CONTAINS(?,data) LIMIT ?,?;"

#define OPENBIZ_CACHE_COUNT_FETCHED_RECORDS_SQL(tableName) \
    "SELECT count(data) AS total FROM `"+tableName+"` LIMIT ?,?;"

#define OPENBIZ_CACHE_COUNT_FOUND_RECORDS_SQL(tableName) \
    "SELECT count(data) AS total FROM `"+tableName+"` WHERE JSON_CONTAINS(?,data) LIMIT ?,?;"


#define OPENBIZ_CACHE_UPDATE_RECORD_SQL(tableName) \
    "UPDATE `"+tableName+"` SET `timestamp`=datetime(),`data`= ? WHERE id= ? ;"

#define OPENBIZ_CACHE_INSERT_RECORD_SQL(tableName) \
    "INSERT INTO `"+tableName+"` (`id`,`timestamp`,`data`) VALUES (?, datetime(), ?); "

#define OPENBIZ_CACHE_REMOVE_RECORD_SQL(tableName) \
    "DELETE FROM `"+tableName+"` WHERE `id`= ? ; "

#define OPENBIZ_CACHE_REMOVE_ALL_RECORDS_SQL(tableName) \
    "DELETE FROM `"+tableName+"` ;"

using namespace std;

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
                if(result == SQLITE_OK){
                    //register sqlite json extension to db connection instance
                    sqlite3_json_extension_init(_db,NULL);
                }
                else{
                    throw std::runtime_error("Con't open database file: "+dbFullname);
                }
            }else{
                throw std::runtime_error("Please define a db name");
            }
        }
        
        void DB::ensureTableExists(const std::string &tableName) const
        {
            if(!isTableExists(tableName)){
                sqlite3_stmt *stmt;
                int rc;
                const char* sql = std::string(OPENBIZ_CACHE_CREATE_TABLE_SQL(tableName)).c_str();
                rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
                rc = sqlite3_bind_text(stmt, 1,
                                       tableName.c_str(),static_cast<int>(tableName.size()), SQLITE_STATIC);
                rc = sqlite3_step(stmt);
            }
            return;
        }
        
        const bool DB::isTableExists(const std::string &tableName) const
        {
            sqlite3_stmt *stmt;
            int rc;
            const char* sql = std::string(OPENBIZ_CACHE_CHECK_TABLE_EXISTS_SQL).c_str();
            rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            rc = sqlite3_bind_text(stmt, 1,
                                   tableName.c_str(),static_cast<int>(tableName.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            if(rc == SQLITE_ROW){
                return true;
            }
            return false;
        }
        
        const bool DB::isRecordExists(const std::string &tableName,
                                      const std::string &recordId) const
        {
            sqlite3_stmt *stmt;
            int rc;
            const char* sql = std::string(OPENBIZ_CACHE_CHECK_RECORD_EXISTS_SQL(tableName)).c_str();
            rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            rc = sqlite3_bind_text(stmt, 1,
                                   recordId.c_str(),static_cast<int>(recordId.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            if(rc == SQLITE_ROW){
                return true;
            }
            return false;
        }
        
        const bool DB::removeRecord(const std::string &tableName,
                                    const std::string &recordId) const
        {
            sqlite3_stmt *stmt;
            int rc;
            const char* sql = std::string(OPENBIZ_CACHE_REMOVE_RECORD_SQL(tableName)).c_str();
            rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            rc = sqlite3_bind_text(stmt, 1,
                                   recordId.c_str(),static_cast<int>(recordId.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            if(rc == SQLITE_DONE){
                return true;
            }
            return false;
        }
        
        const bool DB::removeAllRecords(const std::string &tableName) const
        {
            sqlite3_stmt *stmt;
            int rc;
            const char* sql = std::string(OPENBIZ_CACHE_REMOVE_ALL_RECORDS_SQL(tableName)).c_str();
            rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            rc = sqlite3_step(stmt);
            if(rc == SQLITE_DONE){
                return true;
            }
            return false;
        }
        
        const DB::record* DB::fetchRecord(const std::string &tableName,
                                          const std::string &recordId) const
        {
            DB::record* record = nullptr;
            sqlite3_stmt *stmt;
            int rc;
            const char* sql = std::string(OPENBIZ_CACHE_FETCH_RECORD_SQL(tableName)).c_str();
            rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            rc = sqlite3_bind_text(stmt, 1,
                                   recordId.c_str(),static_cast<int>(recordId.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            if(rc == SQLITE_ROW){
                record = new DB::record;
                record->Id      = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
                record->data    = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
                record->timestamp = static_cast<time_t>((sqlite3_column_int(stmt,2)));
            }
            return record;
        }
        
        const bool DB::insertRecord(const std::string &tableName,
                                    const std::string &recordId,
                                    const std::string &data) const
        {
            sqlite3_stmt *stmt;
            int rc;
            const char* sql = std::string(OPENBIZ_CACHE_INSERT_RECORD_SQL(tableName)).c_str();
            rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            rc = sqlite3_bind_text(stmt, 1,
                                   recordId.c_str(),static_cast<int>(recordId.size()), SQLITE_STATIC);
            rc = sqlite3_bind_text(stmt, 2,
                                   data.c_str(),static_cast<int>(data.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            if(rc == SQLITE_DONE){
                return true;
            }
            return false;
        };
        const bool DB::updateRecord(const std::string &tableName,
                                    const std::string &recordId,
                                    const std::string &data) const
        {
            sqlite3_stmt *stmt;
            int rc;
            const char* sql = std::string(OPENBIZ_CACHE_UPDATE_RECORD_SQL(tableName)).c_str();
            rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            rc = sqlite3_bind_text(stmt, 1,
                                   recordId.c_str(),static_cast<int>(recordId.size()), SQLITE_STATIC);
            rc = sqlite3_bind_text(stmt, 2,
                                   data.c_str(),static_cast<int>(data.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            if(rc == SQLITE_DONE){
                return true;
            }
            return false;
        };
        
        const std::vector<DB::record*> *DB::fetchRecords(const std::string &tableName, int offset, int limit) const{
            std::vector<DB::record*> *records = new std::vector<DB::record*>;
            
            sqlite3_stmt *stmt;
            int rc;
            const char* sql = std::string(OPENBIZ_CACHE_FETCH_RECORDS_SQL(tableName)).c_str();
            rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            rc = sqlite3_bind_int(stmt, 1, offset);
            rc = sqlite3_bind_int(stmt, 2, limit);
            rc = sqlite3_step(stmt);
            
            while(rc == SQLITE_ROW)
            {
                DB::record *record = new DB::record;
                record->Id      = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
                record->data    = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
                record->timestamp = static_cast<time_t>((sqlite3_column_int(stmt,2)));
                records->push_back(record);
                rc = sqlite3_step(stmt);
            }
            return records;
        };
        
        const std::vector<DB::record*> *DB::fetchRecords(const std::string &tableName, const std::string &keyword, int offset, int limit) const{
            std::vector<DB::record*> *records = new std::vector<DB::record*>;
            
            sqlite3_stmt *stmt;
            int rc;
            const char* sql = std::string(OPENBIZ_CACHE_QUERY_RECORDS_SQL(tableName)).c_str();
            rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            rc = sqlite3_bind_text(stmt, 1,
                                   keyword.c_str(),static_cast<int>(keyword.size()), SQLITE_STATIC);
            rc = sqlite3_bind_int(stmt, 2, offset);
            rc = sqlite3_bind_int(stmt, 3, limit);
            rc = sqlite3_step(stmt);
            
            while(rc == SQLITE_ROW)
            {
                DB::record *record = new DB::record;
                record->Id      = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
                record->data    = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
                record->timestamp = static_cast<time_t>((sqlite3_column_int(stmt,2)));
                records->push_back(record);
                rc = sqlite3_step(stmt);
            }
            return records;
        };
        
        unsigned int DB::countRecords(const std::string &tableName){
            sqlite3_stmt *stmt;
            int rc;
            const char* sql = std::string(OPENBIZ_CACHE_COUNT_FETCHED_RECORDS_SQL(tableName)).c_str();
            rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            rc = sqlite3_step(stmt);
            if(rc == SQLITE_ROW){
                return sqlite3_column_int(stmt,0);
            }
            return 0;
        };

        unsigned int DB::countRecords(const std::string &tableName,const std::string &keyword){
            sqlite3_stmt *stmt;
            int rc;
            const char* sql = std::string(OPENBIZ_CACHE_COUNT_FOUND_RECORDS_SQL(tableName)).c_str();
            rc = sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            rc = sqlite3_bind_text(stmt, 1,
                                   keyword.c_str(),static_cast<int>(keyword.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            if(rc == SQLITE_ROW){
                return sqlite3_column_int(stmt,0);
            }
            return 0;
        };
        
        
        void DB::destroyInstance(){
            if(_db!=NULL){
                sqlite3_close(_db);        
            }
            OPENBIZ_SAFE_DELETE(_instance);
        };
    }
}
