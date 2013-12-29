#include "Nextpeer_AndroidJNIHelper.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>

#if 1
#define  LOG_TAG    "Nextpeer_AndroidJNIHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...)
#endif

#endif //(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


namespace nextpeer {
    
    bool Nextpeer_AndroidJNIHelper::getEnv(JNIEnv **env)
    {
        bool bRet = false;
        
        do
        {
            JavaVM* JAVAVM = cocos2d::JniHelper::getJavaVM();
            
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

    
    bool Nextpeer_AndroidJNIHelper::getFieldInfo(JniFieldInfo& fieldInfo, const char* className, const char* fieldName, const char* paramCode)
    {
        jfieldID fieldID = 0;
        JNIEnv* pEnv = 0;
        bool bRet = false;
        
        do {
            if (!getEnv(&pEnv)) {
                break;
            }
            
            jclass classID = cocos2d::JniHelper::getClassID(className, pEnv);
            fieldID = pEnv->GetFieldID(classID, fieldName, paramCode);
            
            if (!fieldID) {
                LOGD("Failed to find field in Java class %s:%s", className, fieldName);
                break;
            }
            
            fieldInfo.env = pEnv;
            fieldInfo.classID = classID;
            fieldInfo.fieldID = fieldID;
            
            bRet = true;
            
        } while (0);
        
        return bRet;
    }
    
 
    jstring Nextpeer_AndroidJNIHelper::getStringFieldValue(const char* className, const char* fieldName, jobject object)
    {
        return (jstring)Nextpeer_AndroidJNIHelper::getObjectFieldValue(className, fieldName, "Ljava/lang/String;", object);
    }
    
    
    jint Nextpeer_AndroidJNIHelper::getIntFieldValue(const char* className, const char* fieldName, jobject object)
    {
        JniFieldInfo info;
        jint result = 0;
        
        if (Nextpeer_AndroidJNIHelper::getFieldInfo(info, className, fieldName, "I")) {
            result = (jint)info.env->GetIntField(object, info.fieldID);
        }
        
        return result;
    }
    
    
    jboolean Nextpeer_AndroidJNIHelper::getBoolFieldValue(const char* className, const char* fieldName, jobject object)
    {
        JniFieldInfo info;
        jboolean result = 0;
        
        if (Nextpeer_AndroidJNIHelper::getFieldInfo(info, className, fieldName, "Z")) {
            result = (jboolean)info.env->GetBooleanField(object, info.fieldID);
        }
        
        return result;
    }
    
    
    jobject Nextpeer_AndroidJNIHelper::getObjectFieldValue(const char* className, const char* fieldName, const char* signature, jobject object)
    {
        JniFieldInfo info;
        jobject result = 0;
        
        if (Nextpeer_AndroidJNIHelper::getFieldInfo(info, className, fieldName, signature)) {
            result = info.env->GetObjectField(object, info.fieldID);
        }
        
        return result;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}