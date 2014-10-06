//系统标准库
#include <iostream>
#include <sqlite3.h>

//第三方类库
#include "restclient.h"
#include "json.h"

//Openbiz自定义库
#include "DataObject.h"
#include "DataCollection.h"
#include "RemoteDataObject.h"
#include "RemoteDataCollection.h"
#include "ServerErrorException.h"
#include "NetworkConnectionException.h"
#include "DataFormatInvalidException.h"


namespace openbiz
{
    namespace core
    {
        class Object;
    }
    namespace data
    {
        class DataObject;
        class DataCollection;
    }
    namespace remote
    {
        class DataObject;
        class DataCollection;
    }
    namespace exception
    {
        class ServerErrorException;
        class NetworkConnectionException;
        class DataFormatInvalidException;
    }
    
    const std::string getVersion();
}