#include <iostream>
#include <sqlite3.h>
#include "DataObject.h"
#include "DataCollection.h"
#include "RemoteDataObject.h"
#include "RemoteDataCollection.h"


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
    const std::string getVersion();
}