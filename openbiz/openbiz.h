//系统标准库
#include <iostream>
#include <sqlite3.h>

//第三方类库
#include "restclient.h"
#include "json.h"

//Openbiz自定义库
#include "DB.h"
#include "Object.h"
#include "DataObject.h"
#include "DataCollection.h"
#include "RemoteDataObject.h"
#include "RemoteDataCollection.h"
#include "ServerErrorException.h"
#include "NetworkConnectionException.h"
#include "DataFormatInvalidException.h"
#include "FileUtils.h"

namespace openbiz
{
    namespace core
    {
        class DB;
        class Object;
    }
    namespace data
    {
        class DataObject;
        template<typename T> class DataCollection;
    }
    namespace remote
    {
        class DataObject;
        template<typename T> class DataCollection;
    }
    namespace exception
    {
        class ServerErrorException;
        class NetworkConnectionException;
        class DataFormatInvalidException;
        class DataValidationException;
    }
    namespace ext
    {
        class FileUtils;
        class JniHelper;
    }
    
    const std::string getVersion();
    void initialize(const std::string dbName);
    void cleanup();
    
}