#ifndef ___NEXTPEER_ANDROID_JNI_HELPER_H
#define ___NEXTPEER_ANDROID_JNI_HELPER_H

#include "platform/CCPlatformMacros.h"

#ifndef CC_TARGET_PLATFORM
#error "CC_TARGET_PLATFORM should be defined!!!"
#endif


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

namespace nextpeer {
    
    typedef struct _JniFieldInfo {
        JNIEnv*     env;
        jclass      classID;
        jfieldID    fieldID;
    } JniFieldInfo;
    
    class Nextpeer_AndroidJNIHelper
    {
    public:
        static bool getFieldInfo(JniFieldInfo& fieldInfo, const char* className, const char* fieldName, const char* paramCode);
        static jstring getStringFieldValue(const char* className, const char* fieldName, jobject object);
        static jint getIntFieldValue(const char* className, const char* fieldName, jobject object);
        static jboolean getBoolFieldValue(const char* className, const char* fieldName, jobject object);
        static jobject getObjectFieldValue(const char* className, const char* fieldName, const char* signature, jobject object);
        
        static bool getEnv(JNIEnv **env);
    };
}


#endif // ___NEXTPEER_ANDROID_JNI_HELPER_H
