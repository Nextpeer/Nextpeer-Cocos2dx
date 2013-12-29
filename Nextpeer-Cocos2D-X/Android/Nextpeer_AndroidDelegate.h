//
//  Created by Nextpeer development team.
//  Copyright (c) 2013 Nextpeer, Inc. All rights reserved.
//

#ifndef ___NEXTPEER_ANDROID_DELEGATE_H
#define ___NEXTPEER_ANDROID_DELEGATE_H

#include "platform/CCPlatformMacros.h"

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
}
#endif


#endif // ___NEXTPEER_ANDROID_DELEGATE_H