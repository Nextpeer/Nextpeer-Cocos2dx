//
//  PZNextpeer.h
//  PZNextpeer
//
//  Created by Nextpeer platforms development team.
//  Copyright (c) 2013 Nextpeer, Inc. All rights reserved.
//

#ifndef _PZ_NEXTPEER_H_
#define _PZ_NEXTPEER_H_

/**
 * This header is used for defining event types using in CCNotificationCenter
 */

// The game should start by Nextpeer
#define NP_EVNET_START_GAME    "nextpeer_start_game"

// The game should end by Nextpeer
#define NP_EVNET_END_GAME    "nextpeer_end_game"


#include "Export.h"
#include <stddef.h>

namespace PZ {
    
    /**
     Use the PZNextpeer class to interface your application with the Nextpeer service.
     */
    class EXPORT_DLL PZNextpeer
    {
        
    public:
        PZNextpeer();
        ~PZNextpeer();
        
        static PZNextpeer* shared();
        
        /** @name Open the dashboard */
        
        /**
         Launches the Nextpeer Dashboard
         
         */
        void launchDashboard();
        
        /** @name Tournament managment */
        
        /**
         This method is used to push a buffer to the other players.
         This can potentially be used to create custom notifications or some other interactive mechanism that incorporates the other players.
         @param pBuffer. This is the buffer you wish to send to the other players
         @param length. The length of the buffer
         @note  The buffer will be sent to the other players and will activate the
         -(void)nextpeerDidReceiveTournamentCustomMessage: method on their NPTournamentDelegate delegate.
         */
        void pushDataToOtherPlayers(void * pBuffer, int length);
        
        /**
         Call this method to report the current score for the tournament. This allows Nextpeer to send various notifications about the players' scores.
         
         */
        void reportScoreForCurrentTournament(uint32_t score);
        
        /**
         Call this method when your game manage the current tournament and the player just died (a.k.a. 'Last Man Standing').
         Nextpeer will call NextpeerDelegate's nextpeerDidTournamentEnd method after reporting the last score.
         
         @note: The method will act only if the current tournament is from 'GameControlled' tournament type
         */
        void reportControlledTournamentOverWithScore(uint32_t score);
        
        /**
         Call this method to check if any tournament is running at the moment.
         
         */
        bool isCurrentlyInTournament();
        
        /**
         Call this method when the user wishes to exit the current tournament.
         @note This will close any in-game notifiactions and dialogs.
         */
        void reportForfeitForCurrentTournament();
        
        /**
         This method will return the amount of seconds left for this tournament.
         @note: If no tournament is currently taking place then this method will return 0.
         */
        uint32_t timeLeftInTournament();
    };
}


#endif // _PZ_NEXTPEER_H_