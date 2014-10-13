#include "openbiz.h"
#include "config.h"

using namespace std;
using namespace openbiz;
namespace openbiz {
    const std::string getVersion(){
        return OPENBIZ_VERSION;
    }
    
    void initialize(const string dbName)
    {
        core::DB::getInstance()->initialize(dbName);
    };
    void cleanup(){
        ext::FileUtils::destroyInstance();
        core::DB::destroyInstance();
    };
}
