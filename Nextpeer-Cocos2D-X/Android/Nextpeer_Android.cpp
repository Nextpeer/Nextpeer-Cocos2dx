//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//


#include "Nextpeer_Android.h"
#include "NextpeerNotifier.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

using namespace std;

namespace nextpeer {
	const char *NextpeerClass = "com/nextpeer/android/NextpeerCocos2DX";

	/*
		Helper function for calling static functions on the main Nextpeer class
	 */
	static void callStaticVoidMethod(const char *name, const char *signature, ...)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		cocos2d::JniMethodInfo methodInfo;

		if ( cocos2d::JniHelper::getStaticMethodInfo( methodInfo,
												NextpeerClass,
				                                name,
				                                signature) ) {
			va_list args;
			va_start(args, signature);
			methodInfo.env->CallStaticVoidMethodV(methodInfo.classID, methodInfo.methodID, args);
			va_end(args);
		}
#endif
	}

	static int callStaticIntMethod(const char *name, const char *signature, ...)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		cocos2d::JniMethodInfo methodInfo;

		jint ret = 0;

		if ( cocos2d::JniHelper::getStaticMethodInfo( methodInfo,
												NextpeerClass,
				                                name,
				                                signature) ) {
			va_list args;
			va_start(args, signature);
			ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID, args);
			va_end(args);
		}
		return ret;
#else
		return 0;
#endif
	}


	void Nextpeer_Android::initialize(const char* apiKey)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		cocos2d::JniMethodInfo methodInfo;

		if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerClass, "initialize", "(Ljava/lang/String;)V")) {
			jstring stringArg = methodInfo.env->NewStringUTF(apiKey);
			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg);
			methodInfo.env->DeleteLocalRef(stringArg);
		}
        
        // This initializes the event queue and starts the scheduler
        NextpeerNotifier::getInstance()->queueScheduler();
#endif
	}

	void Nextpeer_Android::launchDashboard()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		callStaticVoidMethod("launch", "()V");
#endif
	}

	void Nextpeer_Android::reportScoreForCurrentTournament(uint32_t score)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		callStaticVoidMethod("reportScoreForCurrentTournament", "(I)V", score);
#endif		
	}

	void Nextpeer_Android::reportControlledTournamentOverWithScore(uint32_t score)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		callStaticVoidMethod("reportControlledTournamentOverWithScore", "(I)V", score);
#endif
	}

	void Nextpeer_Android::reportForfeitForCurrentTournament()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		callStaticVoidMethod("reportForfeitForCurrentTournament", "()V");
#endif
	}

	uint32_t Nextpeer_Android::timeLeftInTournament()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		return callStaticIntMethod("timeLeftForTournament", "()I");
#else
		return 0;
#endif
	}

	bool Nextpeer_Android::isCurrentlyInTournament()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		cocos2d::JniMethodInfo methodInfo;
		jboolean ret = 0;

		if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerClass, "isCurrentlyInTournament", "()Z")) {
			ret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
		}

		return (bool)ret;
#else
		return false;
#endif
	}

	std::string Nextpeer_Android::getCurrentPlayerId()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		cocos2d::JniMethodInfo methodInfo;

		if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerClass, "getCurrentPlayerId", "()Ljava/lang/String;")) {
			jstring id = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
			if (!id) return string("");

			return cocos2d::JniHelper::jstring2string(id);
		}
		else {
			return string("");
		}
#else
		return string("");
#endif
	}

	std::string Nextpeer_Android::getCurrentPlayerName()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		cocos2d::JniMethodInfo methodInfo;

		if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerClass, "getCurrentPlayerName", "()Ljava/lang/String;")) {
			jstring name = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
			if (!name) return string("");

			return cocos2d::JniHelper::jstring2string(name);
		}
#else
		return string("");
#endif
	}

	void Nextpeer_Android::unreliablePushDataToOtherPlayers(void* pBuffer, uint32_t length)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (length == 0) return;

		cocos2d::JniMethodInfo methodInfo;

		if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerClass, "unreliablePushDataToOtherPlayers", "([B)V")) {
			jbyteArray javaArray = methodInfo.env->NewByteArray(length);
			methodInfo.env->SetByteArrayRegion(javaArray, 0, length, (const jbyte*)pBuffer);

			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, javaArray);

			methodInfo.env->DeleteLocalRef(javaArray);
		}
#endif
	}

	void Nextpeer_Android::pushDataToOtherPlayers(void* pBuffer, uint32_t length)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (length == 0) return;

		cocos2d::JniMethodInfo methodInfo;

		if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo, NextpeerClass, "pushDataToOtherPlayers", "([B)V")) {
			jbyteArray javaArray = methodInfo.env->NewByteArray(length);
			methodInfo.env->SetByteArrayRegion(javaArray, 0, length, (const jbyte*)pBuffer);

			methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, javaArray);

			methodInfo.env->DeleteLocalRef(javaArray);
		}
#endif
	}
    
    void Nextpeer_Android::enableRankingDisplay(bool enableRankingDisplay) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        callStaticVoidMethod("enableRankingDisplay", "(Z)V", enableRankingDisplay);
#endif
    }
} // namespace nextpeer

