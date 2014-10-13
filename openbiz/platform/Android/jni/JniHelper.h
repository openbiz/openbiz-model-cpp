#ifndef __ANDROID_JNI_HELPER_H__
#define __ANDROID_JNI_HELPER_H__

#include <jni.h>
#include <string>
#include "platform/PlatformMacros.h"

namespace openbiz
{
	namespace ext
    {
    	typedef struct JniMethodInfo_
		{
		    JNIEnv *    env;
		    jclass      classID;
		    jmethodID   methodID;
		} JniMethodInfo;

		class JniHelper
		{
		public:
			static JavaVM* getJavaVM();
		    static void setJavaVM(JavaVM *javaVM);
    		static jclass getClassID(const char *className, JNIEnv *env=0);
    		static bool getStaticMethodInfo(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode);
    		static bool getMethodInfo(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode);
			static std::string jstring2string( jstring jstr);
			static jstring string2jstring( const char* pat);
		private:
    		static JavaVM *m_psJavaVM;
		};
	}
}

#endif // __ANDROID_JNI_HELPER_H__