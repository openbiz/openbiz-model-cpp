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
#include <cstdio>
#include "openbiz.h"
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
"SELECT count(data) AS total FROM `"+tableName+"`;"

#define OPENBIZ_CACHE_COUNT_FOUND_RECORDS_SQL(tableName) \
"SELECT count(data) AS total FROM `"+tableName+"` WHERE JSON_CONTAINS(?,data);"


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
        string DB::_dbName = "";
        std::mutex DB::_mtx;
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
                if(!_db){
                    const std::string path = ext::FileUtils::getInstance()->getWritablePath();
                    const std::string dbFullname = path + "/" + dbName;
                    int result = sqlite3_open(dbFullname.c_str(),&_db);
                    DB::_dbName = dbName;
                    if(result == SQLITE_OK){
                        //register sqlite json extension to db connection instance
                        sqlite3_json_extension_init(_db,NULL);
                    }
                    else{
                        throw std::runtime_error("Con't open database file: "+dbFullname);
                    }
                }
            }else{
                throw std::runtime_error("Please define a db name");
            }
        }
        
        void DB::dropDatabase()
        {
            if(!DB::_dbName.empty()){
                _mtx.lock();
                sqlite3_close(_db);
                _mtx.unlock();
                _db = nullptr;
                const std::string path = ext::FileUtils::getInstance()->getWritablePath();
                const std::string dbFullname = path + "/" + DB::_dbName;
                std::remove(dbFullname.c_str());
            }
            destroyInstance();
            
        }
        
        void DB::ensureTableExists(const std::string &tableName) const
        {
            if(!isTableExists(tableName)){
                _mtx.lock();
                sqlite3_stmt *stmt;
                string sqlString(OPENBIZ_CACHE_CREATE_TABLE_SQL(tableName));
                const char* sql = sqlString.c_str();
                sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
                sqlite3_bind_text(stmt, 1,
                                       tableName.c_str(),static_cast<int>(tableName.size()), SQLITE_STATIC);
                sqlite3_step(stmt);
                sqlite3_finalize(stmt);
                _mtx.unlock();
            }
            return;
        }
        
        const bool DB::isTableExists(const std::string &tableName) const
        {
            _mtx.lock();
            sqlite3_stmt *stmt;
            int rc;
            string sqlString(OPENBIZ_CACHE_CHECK_TABLE_EXISTS_SQL);
            const char* sql = sqlString.c_str();
            sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1,
                                   tableName.c_str(),static_cast<int>(tableName.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            _mtx.unlock();
            if(rc == SQLITE_ROW){
                return true;
            }
            return false;
        }
        
        const bool DB::isRecordExists(const std::string &tableName,
                                      const std::string &recordId) const
        {
            _mtx.lock();
            sqlite3_stmt *stmt;
            int rc;
            string sqlString(OPENBIZ_CACHE_CHECK_RECORD_EXISTS_SQL(tableName));
            const char* sql = sqlString.c_str();
            sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1,
                                   recordId.c_str(),static_cast<int>(recordId.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            _mtx.unlock();
            if(rc == SQLITE_ROW){
                return true;
            }
            return false;
        }
        
        const bool DB::removeRecord(const std::string &tableName,
                                    const std::string &recordId) const
        {
            _mtx.lock();
            sqlite3_stmt *stmt;
            int rc;
            string sqlString(OPENBIZ_CACHE_REMOVE_RECORD_SQL(tableName));
            const char* sql = sqlString.c_str();
            sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1,
                                   recordId.c_str(),static_cast<int>(recordId.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            _mtx.unlock();
            if(rc == SQLITE_DONE){
                return true;
            }
            return false;
        }
        
        const bool DB::removeAllRecords(const std::string &tableName) const
        {
            _mtx.lock();
            sqlite3_stmt *stmt;
            int rc;
            string sqlString(OPENBIZ_CACHE_REMOVE_ALL_RECORDS_SQL(tableName));
            const char* sql = sqlString.c_str();
            sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            rc = sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            _mtx.unlock();
            if(rc == SQLITE_DONE){
                return true;
            }
            return false;
        }
        
        const DB::Record* DB::fetchRecord(const std::string &tableName,
                                          const std::string &recordId) const
        {
            _mtx.lock();
            DB::Record* record = nullptr;
            sqlite3_stmt *stmt;
            int rc;
            string sqlString(OPENBIZ_CACHE_FETCH_RECORD_SQL(tableName));
            const char* sql = sqlString.c_str();
            sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1,
                                   recordId.c_str(),static_cast<int>(recordId.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            if(rc == SQLITE_ROW){
                record = new DB::Record;
                record->Id      = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
                record->data    = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
                record->timestamp = static_cast<time_t>((sqlite3_column_int(stmt,2)));
            }
            sqlite3_finalize(stmt);
            _mtx.unlock();
            if(Debugger::getDebugDatabaseOption()->DebugUpdateOperation && record!=nullptr)
            {
                std::cout << "Fetched Record :" << std::endl;
                std::cout << "Table:" << tableName << std::endl;
                std::cout << "RecordId:" << recordId << std::endl;
                std::cout << "Data:" << record->data << std::endl;
            }
            return record;
        }
        
        const bool DB::insertRecord(const std::string &tableName,
                                    const std::string &recordId,
                                    const std::string &data) const
        {
            if(Debugger::getDebugDatabaseOption()->DebugInsertOperation)
            {
                std::cout << "Insert Record :" << std::endl;
                std::cout << "Table:" << tableName << std::endl;
                std::cout << "RecordId:" << recordId << std::endl;
                std::cout << "Data:" << data << std::endl;
            }
            _mtx.lock();
            sqlite3_stmt *stmt;
            int rc;
            string sqlString(OPENBIZ_CACHE_INSERT_RECORD_SQL(tableName));
            const char* sql =sqlString.c_str();
            
            sqlite3_prepare(_db, sql, -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1, recordId.c_str(),static_cast<int>(recordId.size()), SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, data.c_str(),static_cast<int>(data.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            _mtx.unlock();
            if(rc == SQLITE_DONE){
                return true;
            }
            return false;
        };
        
        const bool DB::updateRecord(const std::string &tableName,
                                    const std::string &recordId,
                                    const std::string &data) const
        {
            if(Debugger::getDebugDatabaseOption()->DebugUpdateOperation)
            {
                std::cout << "Update Record :" << std::endl;
                std::cout << "Table:" << tableName << std::endl;
                std::cout << "RecordId:" << recordId << std::endl;
                std::cout << "Data:" << data << std::endl;
            }
            
            _mtx.lock();
            sqlite3_stmt *stmt;
            int rc;
            string sqlString(OPENBIZ_CACHE_UPDATE_RECORD_SQL(tableName));
            const char* sql = sqlString.c_str();
            sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1, data.c_str(),static_cast<int>(data.size()), SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, recordId.c_str(),static_cast<int>(recordId.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            sqlite3_finalize(stmt);
            _mtx.unlock();
            if(rc == SQLITE_DONE){
                return true;
            }
            return false;
        };
        
        const std::vector<DB::Record*> *DB::fetchRecords(const std::string &tableName, int offset, int limit) const
        {
            _mtx.lock();
            std::vector<DB::Record*> *records = new std::vector<DB::Record*>;
            
            sqlite3_stmt *stmt;
            int rc;
            string sqlString(OPENBIZ_CACHE_FETCH_RECORDS_SQL(tableName));
            const char* sql = sqlString.c_str();
            sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            sqlite3_bind_int(stmt, 1, offset);
            sqlite3_bind_int(stmt, 2, limit);
            rc = sqlite3_step(stmt);
            
            while(rc == SQLITE_ROW)
            {
                DB::Record *record = new DB::Record;
                record->Id      = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
                record->data    = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
                record->timestamp = static_cast<time_t>((sqlite3_column_int(stmt,2)));
                records->push_back(record);
                rc = sqlite3_step(stmt);
            }
            sqlite3_finalize(stmt);
            _mtx.unlock();
            return records;
        };
        
        const std::vector<DB::Record*> *DB::fetchRecords(const std::string &tableName, const std::string &keyword, int offset, int limit) const
        {
            _mtx.lock();
            std::vector<DB::Record*> *records = new std::vector<DB::Record*>;
            
            sqlite3_stmt *stmt;
            int rc;
            string sqlString(OPENBIZ_CACHE_QUERY_RECORDS_SQL(tableName));
            const char* sql = sqlString.c_str();
            sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1,
                                   keyword.c_str(),static_cast<int>(keyword.size()), SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, offset);
            sqlite3_bind_int(stmt, 3, limit);
            rc = sqlite3_step(stmt);
            
            while(rc == SQLITE_ROW)
            {
                DB::Record *record = new DB::Record;
                record->Id      = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
                record->data    = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
                record->timestamp = static_cast<time_t>((sqlite3_column_int(stmt,2)));
                records->push_back(record);
                rc = sqlite3_step(stmt);
            }
            sqlite3_finalize(stmt);
            _mtx.unlock();
            return records;
        };
        
        unsigned int DB::countRecords(const std::string &tableName)
        {
            _mtx.lock();
            sqlite3_stmt *stmt;
            int rc;
            string sqlString(OPENBIZ_CACHE_COUNT_FETCHED_RECORDS_SQL(tableName));
            const char* sql = sqlString.c_str();
            sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            rc = sqlite3_step(stmt);
            int result = 0;
            if(rc == SQLITE_ROW){
                result =  sqlite3_column_int(stmt,0);
            }
            sqlite3_finalize(stmt);
            _mtx.unlock();
            return result;
        };
        
        unsigned int DB::countRecords(const std::string &tableName,const std::string &keyword)
        {
            _mtx.lock();
            sqlite3_stmt *stmt;
            int rc;
            string sqlString(OPENBIZ_CACHE_COUNT_FOUND_RECORDS_SQL(tableName));
            const char* sql = sqlString.c_str();
            sqlite3_prepare_v2(_db, sql, -1, &stmt, NULL);
            sqlite3_bind_text(stmt, 1,
                                   keyword.c_str(),static_cast<int>(keyword.size()), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            int result = 0;
            if(rc == SQLITE_ROW){
                result = sqlite3_column_int(stmt,0);
            }
            sqlite3_finalize(stmt);
            _mtx.unlock();
            return result;
        };
        
        
        void DB::destroyInstance(){
            _mtx.lock();
            if(_db!=NULL){
                sqlite3_close(_db);
            }
            _mtx.unlock();
            OPENBIZ_SAFE_DELETE(_instance);
        };
    }
}
