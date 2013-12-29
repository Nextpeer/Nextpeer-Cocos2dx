//
//  Created by Nextpeer development team.
//  Copyright (c) 2013 Nextpeer, Inc. All rights reserved.
//

#ifndef ___NEXTPEER_NOTIFIER_H
#define ___NEXTPEER_NOTIFIER_H

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

#endif // ___NEXTPEER_NOTIFIER_H
