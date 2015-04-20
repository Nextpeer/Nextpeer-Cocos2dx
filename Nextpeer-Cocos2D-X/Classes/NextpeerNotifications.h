//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//

#ifndef ___NEXTPEER_NOTIFICATIONS
#define ___NEXTPEER_NOTIFICATIONS

#include <string>
#include <vector>
using namespace std;

#include "cocos2d.h"
USING_NS_CC;

// Notifications
#define NEXTPEER_NOTIFICATION_TOURNAMENT_STARTED "nextpeer_tournament_started"
#define NEXTPEER_NOTIFICATION_TOURNAMENT_ENDED "nextpeer_tournament_ended"
#define NEXTPEER_NOTIFICATION_RECEIVE_SYNCHRONIZED_EVENT "nextpeer_receive_synchronized_event"

#define NEXTPEER_NOTIFICATION_INCOMING_DATA_PACKET "nextpeer_incoming_data_packet"
#define NEXTPEER_NOTIFICATION_DASHBOARD_DID_APPEAR "nextpeer_dashboard_did_appear"
#define NEXTPEER_NOTIFICATION_DASHBOARD_DID_DISAPPEAR "nextpeer_dashboard_did_disappear"
#define NEXTPEER_NOTIFICATION_DASHBOARD_RETURN_TO_GAME "nextpeer_dashboard_return_to_game"

// The following notifications are not called for Android
#define NEXTPEER_NOTIFICATION_DASHBOARD_WILL_APPEAR "nextpeer_dashboard_will_appear"
#define NEXTPEER_NOTIFICATION_DASHBOARD_WILL_DISAPPEAR "nextpeer_dashboard_will_disappear"


namespace nextpeer {

    class TournamentStartData : public Ref
    {
    public:
        virtual ~TournamentStartData()
        {
            CC_SAFE_RELEASE_NULL(players);
        }
        
    public:
        string tournamentUuid;
        string tournamentName;
        unsigned int tournamentRandomSeed;
        unsigned int numberOfPlayers;
        __Array* players;
    };

    enum  NextpeerDataChannel { CHANNEL_RELIABLE = 0, CHANNEL_UNRELIABLE = 1 };

    class TournamentP2PData : public Ref
    {
    public:
        NextpeerDataChannel channel;
        string playerName;
        string playerId;
        string playerImageUrl;
        bool playerIsRecording;
        vector<unsigned char> message;
    };


};


#endif // ___NEXTPEER_NOTIFICATIONS
