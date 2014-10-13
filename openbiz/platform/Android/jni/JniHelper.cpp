#include <jni.h>
#include <iostream>
#include <cstring>
#include <string>
#include <android/log.h>

#include "openbiz.h"
#include "JniHelper.h"

#if 1
#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

#define JAVAVM    openbiz::ext::JniHelper::getJavaVM()

using namespace std;
using namespace openbiz::ext;
extern "C" {
	static bool getEnv(JNIEnv **env)
    {
        bool bRet = false;

        do 
        {
            if (JAVAVM->GetEnv((void**)env, JNI_VERSION_1_4) != JNI_OK)
            {
                LOGD("Failed to get the environment using GetEnv()");
                break;
            }

            if (JAVAVM->AttachCurrentThread(env, 0) < 0)
            {
                LOGD("Failed to get the environment using AttachCurrentThread()");
                break;
            }

            bRet = true;
        } while (0);        

        return bRet;
    }

    static jclass getClassID_(const char *className, JNIEnv *env)
    {
        JNIEnv *pEnv = env;
        jclass ret = 0;

        do 
        {
            if (! pEnv)
            {
                if (! getEnv(&pEnv))
                {
                    break;
                }
            }
            
            ret = pEnv->FindClass(className);
            if (! ret)
            {
                 LOGD("Failed to find class of %s", className);
                break;
            }
        } while (0);

        return ret;
    }

    static bool getStaticMethodInfo_(openbiz::ext::JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
    {
        jmethodID methodID = 0;
        JNIEnv *pEnv = 0;
        bool bRet = false;

        do 
        {
            if (! getEnv(&pEnv))
            {
                break;
            }

            jclass classID = getClassID_(className, pEnv);

            methodID = pEnv->GetStaticMethodID(classID, methodName, paramCode);
            if (! methodID)
            {
                LOGD("Failed to find static method id of %s", methodName);
                break;
            }

            methodinfo.classID = classID;
            methodinfo.env = pEnv;
            methodinfo.methodID = methodID;

            bRet = true;
        } while (0);

        return bRet;
    }

    static bool getMethodInfo_(openbiz::ext::JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
    {
        jmethodID methodID = 0;
        JNIEnv *pEnv = 0;
        bool bRet = false;

        do 
        {
            if (! getEnv(&pEnv))
            {
                break;
            }

            jclass classID = getClassID_(className, pEnv);

            methodID = pEnv->GetMethodID(classID, methodName, paramCode);
            if (! methodID)
            {
                LOGD("Failed to find method id of %s", methodName);
                break;
            }

            methodinfo.classID = classID;
            methodinfo.env = pEnv;
            methodinfo.methodID = methodID;

            bRet = true;
        } while (0);

        return bRet;
    }

    

}
namespace openbiz
{
	namespace ext
    {
		JavaVM* JniHelper::m_psJavaVM = NULL;

		JavaVM* JniHelper::getJavaVM()
		{
		    return m_psJavaVM;
		}

		void JniHelper::setJavaVM(JavaVM *javaVM)
		{
		    m_psJavaVM = javaVM;
		}

		jclass JniHelper::getClassID(const char *className, JNIEnv *env)
		{
		    return getClassID_(className, env);
		}

		bool JniHelper::getStaticMethodInfo(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
		{
		    return getStaticMethodInfo_(methodinfo, className, methodName, paramCode);
		}

		bool JniHelper::getMethodInfo(JniMethodInfo &methodinfo, const char *className, const char *methodName, const char *paramCode)
		{
		    return getMethodInfo_(methodinfo, className, methodName, paramCode);
		}
		jstring JniHelper::string2jstring(const char* pat)
		{			
			JNIEnv *env = new JNIEnv;;
			if (! getEnv(&env)){
				jstring ret = NULL;
				return  ret;
			}
		    //定义java String类 strClass
		    jclass strClass = (env)->FindClass("java/lang/String");
		    //获取String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
		    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
		    //建立byte数组
		    jbyteArray bytes = (env)->NewByteArray(strlen(pat));
		    //将char* 转换为byte数组
		    (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
		    // 设置String, 保存语言类型,用于byte数组转换至String时的参数
		    jstring encoding = (env)->NewStringUTF("UTF-8");
		    //将byte数组转换为java String,并输出
		    return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
		}

		std::string JniHelper::jstring2string(jstring jstr)
		{
			JNIEnv *env = new JNIEnv;
			if (! getEnv(&env)){
				return 0;
			}
		    char*   rtn   =   NULL;
		    jclass   clsstring   =   env->FindClass("java/lang/String");
		    jstring   strencode   =   env->NewStringUTF("UTF-8");
		    jmethodID   mid   =   env->GetMethodID(clsstring,   "getBytes",   "(Ljava/lang/String;)[B");
		    jbyteArray   barr=   (jbyteArray)env->CallObjectMethod(jstr,mid,strencode);
		    jsize   alen   =   env->GetArrayLength(barr);
		    jbyte*   ba   =   env->GetByteArrayElements(barr,JNI_FALSE);
		    if(alen   >   0)
		    {
		        rtn   =   (char*)malloc(alen+1);
		        memcpy(rtn,ba,alen);
		        rtn[alen]=0;
		    }
		    env->ReleaseByteArrayElements(barr,ba,0);
		    std::string stemp(rtn);
		    free(rtn);
		    return   stemp;
		}
	}
}
