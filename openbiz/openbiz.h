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
#include "DataArray.h"
#include "RemoteDataObject.h"
#include "RemoteDataCollection.h"
#include "FileUtils.h"
#include "PlatformMacros.h"
#include "Util.h"

//Openbiz自定义异常
#include "exception.h"

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
        template<typename T> class DataArray;
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
        class DataPermissionException;
    }
    namespace ext
    {
        class FileUtils;
        class JniHelper;
    }
    
    namespace util
    {
        
    }
    
    const std::string getVersion();
    void initialize(const std::string dbName);
    void cleanup();
    
}