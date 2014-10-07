#include "openbiz.h"
#include "config.h"

using namespace std;
using namespace openbiz;
namespace openbiz {
    const std::string getVersion(){
        return OPENBIZ_VERSION;
    }
    
    void initialize(const string &dbName)
    {
        if(!dbName.empty()){
            const std::string path = ext::FileUtils::getInstance()->getWritablePath();
        }
    };
    void cleanup(){
        ext::FileUtils::destroyInstance();
    };
}