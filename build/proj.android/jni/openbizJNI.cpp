#include <jni.h>
#include "platform/android/jni/JniHelper.h"

using namespace openbiz::ext;

extern "C"
{
	jint JNI_OnLoad(JavaVM *vm, void *reserved)
	{
		JniHelper::setJavaVM(vm);
		return JNI_VERSION_1_4;
	}
}
