//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#import "Nextpeer_iOSDelegate.h"

#include "NextpeerNotifier.h"
#include "NextpeerPlayer.h"
#include "NextpeerTournamentSupport.h"
#include "cocos2d.h"

using namespace nextpeer;

static Nextpeer_iOSDelegate* _nextpeer_ios_delegate_instance = nil;

@interface Nextpeer_iOSDelegate ()
-(TournamentP2PData*)generateP2PStructForChannel:(NextpeerDataChannel)channel andMessage:(NPTournamentCustomMessageBaseContainer*)message;
@end

@implementation Nextpeer_iOSDelegate

+(Nextpeer_iOSDelegate*)sharedInstance
{
    if (!_nextpeer_ios_delegate_instance) {
        _nextpeer_ios_delegate_instance = [[Nextpeer_iOSDelegate alloc] init];
    }
    
    return _nextpeer_ios_delegate_instance;
}

// NextpeerDelegate methods

-(void)nextpeerWillTournamentStartWithDetails:(NPTournamentStartDataContainer *)tournamentContainer
{
    TournamentStartData* startData = new TournamentStartData();
    startData->tournamentUuid = string([tournamentContainer.tournamentUuid UTF8String]);
    startData->tournamentName = string([tournamentContainer.tournamentName UTF8String]);
    startData->tournamentTimeInSeconds = tournamentContainer.tournamentTimeSeconds;
    startData->tournamentRandomSeed = tournamentContainer.tournamentRandomSeed;
    startData->isGameControlled = tournamentContainer.tournamentIsGameControlled;
    startData->numberOfPlayers = tournamentContainer.numberOfPlayers;
    
    // Convert the opponents objects
    CCArray* players = CCArray::createWithCapacity([tournamentContainer.opponents count]);
    for (NPTournamentPlayer* player in tournamentContainer.opponents) {
        string playerName([player.playerName UTF8String]);
        string playerId([player.playerId UTF8String]);
        string playerImageUrl([player.playerImageUrl UTF8String]);
        bool isRecording = player.playerIsBot;
        
        players->addObject(NextpeerPlayer::create(playerName, playerId, playerImageUrl, isRecording));
    }
    
    players->retain();
    startData->players = players;
    
    startData->autorelease();
    NextpeerNotifier::getInstance()->broadcastTournamentStarted(startData);
}

-(void)nextpeerDidTournamentStartWithDetails:(NPTournamentStartDataContainer *)tournamentContainer
{
    // Left empty on purpose -> all logic done in nextpeerWillTournamentStartWithDetails due to a
    // Nextpeer bug that allows P2P packets between the "will" and "did" callbacks.
}

-(BOOL)nextpeerSupportsTournamentWithId:(NSString* )tournamentUuid {
    string uuid([tournamentUuid UTF8String]);
    return NextpeerTournamentSupport::getInstance()->isTournamentSupported(uuid);
}

-(void)nextpeerDidTournamentEnd
{
    NextpeerNotifier::getInstance()->broadcastTournamentEnded();
}

-(void)nextpeerDashboardDidAppear
{
    NextpeerNotifier::getInstance()->broadcastDashboardDidAppear();
}

-(void)nextpeerDashboardDidDisappear
{
    NextpeerNotifier::getInstance()->broadcastDashboardDidDisappear();
}

-(void)nextpeerDashboardWillAppear
{
    NextpeerNotifier::getInstance()->broadcastDashboardWillAppear();
}

-(void)nextpeerDashboardWillDisappear
{
    NextpeerNotifier::getInstance()->broadcastDashboardWillDisappear();
}

-(void)nextpeerDashboardDidReturnToGame
{
    NextpeerNotifier::getInstance()->broadcastDashboardNextpeerReturnToGame();
}

-(void)nextpeerDidReceiveSynchronizedEvent:(NSString*)eventName withReason:(NPSynchronizationEventFireReason)fireReason {
    
    string event([eventName UTF8String]);
    NextpeerNotifier::getInstance()->broadcastReceiveSynchronizedEvent(CCString::create(event));
}

// NPTournamentDelegate methods

-(void)nextpeerDidReceiveTournamentCustomMessage:(NPTournamentCustomMessageContainer*)message
{
    TournamentP2PData* data = [self generateP2PStructForChannel:CHANNEL_RELIABLE andMessage:message];
    NextpeerNotifier::getInstance()->broadcastIncomingTournamentDataPacket(data);
}

-(void)nextpeerDidReceiveUnreliableTournamentCustomMessage:(NPTournamentCustomUnreliableMessageContainer*)message
{
    TournamentP2PData* data = [self generateP2PStructForChannel:CHANNEL_UNRELIABLE andMessage:message];
    NextpeerNotifier::getInstance()->broadcastIncomingTournamentDataPacket(data);
}

-(TournamentP2PData*)generateP2PStructForChannel:(NextpeerDataChannel)channel andMessage:(NPTournamentCustomMessageBaseContainer*)message
{
    TournamentP2PData* data = new TournamentP2PData();
    
    data->channel = channel;
    data->playerName = string([message.playerName UTF8String]);
    data->playerId = string([message.playerId UTF8String]);
    data->playerImageUrl = string([message.playerImageUrl UTF8String]);
    data->playerIsRecording = message.playerIsBot;

    // convert the actual message into a vector of bytes
    std::vector<unsigned char> buffer = std::vector<unsigned char>([message.message length]);
    memcpy(&buffer[0], [message.message bytes], [message.message length]);
    buffer.resize([message.message length]);
    data->message = buffer;
    
    data->autorelease();
    
    return data;
}

// NPNotificationDelegate

- (BOOL)nextpeerShouldShowWelcomeBanner
{
    return false;
}

@end

#endif