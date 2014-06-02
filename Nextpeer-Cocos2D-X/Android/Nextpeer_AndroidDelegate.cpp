//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//


#include "Nextpeer_Android.h"
#include "Nextpeer_AndroidDelegate.h"
#include "Nextpeer_AndroidJNIHelper.h"

#include "NextpeerTournamentSupport.h"
#include "NextpeerNotifier.h"
#include "NextpeerPlayer.h"
using namespace nextpeer;

#include <string>
#include <vector>
using namespace std;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

// Utils
static TournamentP2PData* createTournamentP2PData(NextpeerDataChannel channel, jobject messageObject)
{
    static const char* messageObjectClass = "com/nextpeer/android/NextpeerTournamentCustomMessage";
    
    TournamentP2PData* p2pData = new TournamentP2PData();
    
    p2pData->channel = channel;
    
    p2pData->playerName = cocos2d::JniHelper::jstring2string(Nextpeer_AndroidJNIHelper::getStringFieldValue(messageObjectClass, "playerName", messageObject));
    p2pData->playerId = cocos2d::JniHelper::jstring2string(Nextpeer_AndroidJNIHelper::getStringFieldValue(messageObjectClass, "playerId", messageObject));
    p2pData->playerImageUrl = cocos2d::JniHelper::jstring2string(Nextpeer_AndroidJNIHelper::getStringFieldValue(messageObjectClass, "playerImageUrl", messageObject));
    p2pData->playerIsRecording = (bool)Nextpeer_AndroidJNIHelper::getBoolFieldValue(messageObjectClass, "playerIsBot", messageObject);
    
    JNIEnv* pEnv = 0;
    Nextpeer_AndroidJNIHelper::getEnv(&pEnv);
    
    jbyteArray byteMessage = (jbyteArray)Nextpeer_AndroidJNIHelper::getObjectFieldValue(messageObjectClass, "customMessage", "[B", messageObject);
    jsize arraylen = pEnv->GetArrayLength(byteMessage);
    
    vector<unsigned char> buffer = vector<unsigned char>(arraylen);
    pEnv->GetByteArrayRegion(byteMessage, 0, arraylen, (jbyte*)&buffer[0]);
    buffer.resize(arraylen);
    
    p2pData->message = buffer;
    
    return p2pData;
}

// JNI calls
JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onTournamentStartNative(JNIEnv* env, jobject caller, jobject startData, jobjectArray opponents)
{
    static const char* startDataClass = "com/nextpeer/android/NextpeerTournamentStartData";
    static const char* playerClass = "com/nextpeer/android/NextpeerTournamentPlayer";
    
	TournamentStartData* startDataObject = new TournamentStartData();

    // Copy over the data from the Java object over to the C++ object
    startDataObject->tournamentUuid = cocos2d::JniHelper::jstring2string(Nextpeer_AndroidJNIHelper::getStringFieldValue(startDataClass, "tournamentUuid", startData));
    startDataObject->tournamentName = cocos2d::JniHelper::jstring2string(Nextpeer_AndroidJNIHelper::getStringFieldValue(startDataClass, "tournamentName", startData));
    startDataObject->tournamentTimeInSeconds = (unsigned int)Nextpeer_AndroidJNIHelper::getIntFieldValue(startDataClass, "tournamentTimeSeconds", startData);
    startDataObject->tournamentRandomSeed = (unsigned int)Nextpeer_AndroidJNIHelper::getIntFieldValue(startDataClass, "tournamentRandomSeed", startData);
    startDataObject->isGameControlled = (bool)Nextpeer_AndroidJNIHelper::getBoolFieldValue(startDataClass, "tournamentIsGameControlled", startData);
    startDataObject->numberOfPlayers = (unsigned int)Nextpeer_AndroidJNIHelper::getIntFieldValue(startDataClass, "numberOfPlayers", startData);

    JNIEnv* pEnv = 0;
    Nextpeer_AndroidJNIHelper::getEnv(&pEnv);
    
    jsize opponentsCount = pEnv->GetArrayLength(opponents);
    
    // We don't use autorelease since this is probably not the main thread of the application
    CCArray* players = new CCArray();
    players->initWithCapacity(opponentsCount);
    for (int i = 0; i < opponentsCount; i++) {
        jobject player = env->GetObjectArrayElement(opponents, i);
        string playerName = cocos2d::JniHelper::jstring2string(Nextpeer_AndroidJNIHelper::getStringFieldValue(playerClass, "playerName", player));
        string playerId = cocos2d::JniHelper::jstring2string(Nextpeer_AndroidJNIHelper::getStringFieldValue(playerClass, "playerId", player));
        string playerImageUrl = cocos2d::JniHelper::jstring2string(Nextpeer_AndroidJNIHelper::getStringFieldValue(playerClass, "playerImageUrl", player));
        bool isRecording = (bool)Nextpeer_AndroidJNIHelper::getBoolFieldValue(playerClass, "playerIsBot", player);
        
        NextpeerPlayer* playerObj = new NextpeerPlayer();
        playerObj->init(playerName, playerId, playerImageUrl, isRecording);
        players->addObject(playerObj);
        playerObj->release();
    }
    
    startDataObject->players = players;

    NextpeerNotifier::getInstance()->broadcastTournamentStarted((TournamentStartData*)startDataObject);

    // We must explicitly release this object, since we can't use the autorelease pool from this thread
    startDataObject->release();
}

JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onTournamentEndNative(JNIEnv* env, jobject caller, jobject endData)
{
    NextpeerNotifier::getInstance()->broadcastTournamentEnded();
}

JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onReceiveTournamentCustomMessageNative(JNIEnv* env, jobject caller, jobject message)
{
    TournamentP2PData* data = createTournamentP2PData(CHANNEL_RELIABLE, message);
    
    NextpeerNotifier::getInstance()->broadcastIncomingTournamentDataPacket(data);
    
    // We must explicitly release this object, since we can't use the autorelease pool from this thread
    data->release();
}

JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onReceiveUnreliableTournamentCustomMessageNative(JNIEnv* env, jobject caller, jobject message)
{
    TournamentP2PData* data = createTournamentP2PData(CHANNEL_UNRELIABLE, message);
    
    NextpeerNotifier::getInstance()->broadcastIncomingTournamentDataPacket(data);
    
    // We must explicitly release this object, since we can't use the autorelease pool from this thread
    data->release();
}

JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onNextpeerAppearNative(JNIEnv* env, jobject caller)
{
    NextpeerNotifier::getInstance()->broadcastDashboardDidAppear();
}

JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onNextpeerDisappearNative(JNIEnv* env, jobject caller)
{
    NextpeerNotifier::getInstance()->broadcastDashboardDidDisappear();
}

JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onNextpeerReturnToGameNative(JNIEnv* env, jobject caller)
{
    NextpeerNotifier::getInstance()->broadcastDashboardNextpeerReturnToGame();
}


JNIEXPORT bool JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onSupportsTournamentNative(JNIEnv* env, jobject caller, jstring tournamentUuid)
{
    string uuid = cocos2d::JniHelper::jstring2string(tournamentUuid);
    return NextpeerTournamentSupport::getInstance()->isTournamentSupported(uuid);
}

JNIEXPORT void JNICALL Java_com_nextpeer_android_NextpeerCocos2DX_onReceiveSynchronizedEventNative(JNIEnv* env, jobject caller, jstring name, jobject fireReason) {
    
    string eventName = cocos2d::JniHelper::jstring2string(name);

    NextpeerNotifier::getInstance()->broadcastReceiveSynchronizedEvent(CCString::create(eventName));
}

#endif