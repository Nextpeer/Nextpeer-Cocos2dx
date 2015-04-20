//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//

#ifndef __NextpeerNotifications__
#define __NextpeerNotifications__

#include "NextpeerNotifications.h"

// Containers for notifications
namespace nextpeer {    
    class NextpeerNotifier : public CCObject
    {
    public:
        static NextpeerNotifier* getInstance();
        
        // Generic
        void broadcastTournamentStarted(TournamentStartData* tournamentStartData);
        void broadcastTournamentEnded();
        void broadcastReceiveSynchronizedEvent(CCString* eventName);
        
        // Tournament specific
        void broadcastIncomingTournamentDataPacket(TournamentP2PData* data);
        
        // Dashboard notifications
        void broadcastDashboardWillAppear();
        void broadcastDashboardWillDisappear();
        void broadcastDashboardDidAppear();
        void broadcastDashboardDidDisappear();
        void broadcastDashboardNextpeerReturnToGame();
        
        void queueScheduler();
    private:
        NextpeerNotifier();
        static NextpeerNotifier* _instance;
    };
}

#endif /* defined(__NextpeerNotifications__) */