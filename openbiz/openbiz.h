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


namespace openbiz
{
    namespace core
    {
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
    }
    
    const std::string getVersion();
}