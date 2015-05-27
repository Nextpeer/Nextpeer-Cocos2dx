#include "CCNextpeerFacebook.h"
#include "Nextpeer_Android.h"
#include "platform/CCPlatformMacros.h"

#ifndef CC_TARGET_PLATFORM
#error "CC_TARGET_PLATFORM should be defined!!!"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif

namespace nextpeer {

	const char *NextpeerFacebookClass = "com.nextpeer.android.NextpeerCocos2DXFacebookBridge";

	void CCNextpeerFacebook::initialize() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerFacebookClass, "init", "()V")) {
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        }
#endif
	}

	void CCNextpeerFacebook::login() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerFacebookClass, "login", "()V")) {
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        }
#endif
	}

	void CCNextpeerFacebook::logout() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        cocos2d::JniMethodInfo methodInfo;
        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerFacebookClass, "logout", "()V")) {
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        }
#endif
	}
}
