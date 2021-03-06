#include "openbiz.h"
#include "config.h"
#include "curl.h"

using namespace std;
using namespace openbiz;
namespace openbiz {
    const std::string getVersion(){
        return OPENBIZ_VERSION;
    }    
    
    void initialize(const string dbName)
    {
        try{
            core::DB::getInstance()->initialize(dbName);
        }catch(std::exception e){
        }
        curl_global_init(CURL_GLOBAL_ALL);
    };
    
    void cleanup(){
        ext::FileUtils::destroyInstance();
        core::DB::destroyInstance();
        curl_global_cleanup();
    };
}

