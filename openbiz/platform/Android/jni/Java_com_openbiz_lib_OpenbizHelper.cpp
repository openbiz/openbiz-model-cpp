#include <jni.h>
#include <android/log.h>
#include <string>
#include "JniHelper.h"
#include "Java_com_openbiz_lib_OpenbizHelper.h"

#define  LOG_TAG    "Java_com_openbiz_lib_OpenbizHelper.cpp"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#define  CLASS_NAME "com/openbiz/lib/OpenbizHelper"

using namespace std;
using namespace openbiz::ext;
extern "C" {

}

std::string getFileDirectoryJNI() {
	JniMethodInfo t;
	std::string ret("");
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "getWritablePath", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		ret = JniHelper::jstring2string(str);
		t.env->DeleteLocalRef(str);
	}
	return ret;
}
