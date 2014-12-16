#include "FileUtils-Android.h"
#include "jni/Java_com_openbiz_lib_OpenbizHelper.h"
#include <android/log.h>

#define  LOG_TAG    "FileUtils-Android.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace std;
namespace openbiz
{
    namespace ext
    {
        FileUtils* FileUtils::getInstance()
        {
            if (_instance == nullptr)
            {
                _instance = new FileUtilsAndroid();
            }
            return _instance;
        }
        
        const string FileUtilsAndroid::getWritablePath() const
        {
            // save to document folder
            string dir("");
            string tmp = getFileDirectoryJNI();

            if (tmp.length() > 0)
            {
                dir.append(tmp);
                return dir;
            }            
            return "";
        }
    }
}
