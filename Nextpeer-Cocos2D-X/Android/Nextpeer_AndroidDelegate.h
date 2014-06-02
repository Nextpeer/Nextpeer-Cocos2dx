//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//

#ifndef __NextpeerAndroidDelegate__
#define __NextpeerAndroidDelegate__

#include "CCPlatformConfig.h"

#ifndef CC_TARGET_PLATFORM
#error "CC_TARGET_PLATFORM should be defined!!!"
#endif

#include <jni.h>

#include "Export.h"
#include "CCNextpeer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// JNI calls
extern "C" {
	JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onTournamentStartNative(JNIEnv* env, jobject caller, jobject startData, jobjectArray opponents);
	JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onTournamentEndNative(JNIEnv* env, jobject caller, jobject endData);
	JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onReceiveTournamentCustomMessageNative(JNIEnv* env, jobject caller, jobject message);
	JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onReceiveUnreliableTournamentCustomMessageNative(JNIEnv* env, jobject caller, jobject message);

	JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onNextpeerAppearNative(JNIEnv* env, jobject caller);
	JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onNextpeerDisappearNative(JNIEnv* env, jobject caller);
	JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onNextpeerReturnToGameNative(JNIEnv* env, jobject caller);
    JNIEXPORT bool JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onSupportsTournamentNative(JNIEnv* env, jobject caller, jstring tournamentUuid);
	JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onReceiveSynchronizedEventNative(JNIEnv* env, jobject caller, jstring name, jobject fireReason);
}
#endif

#endif /* defined(__NextpeerAndroidDelegate__) */