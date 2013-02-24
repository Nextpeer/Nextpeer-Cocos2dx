//
//  PZNextpeer.m
//  PZNextpeer
//
//  Created by Nextpeer platforms development team.
//  Copyright (c) 2013 Nextpeer, Inc. All rights reserved.
//


#import "PZNextpeer.h"

#import "Nextpeer/Nextpeer.h"

#import <Foundation/Foundation.h>

namespace PZ {
    static PZNextpeer *s_np;
    
    PZNextpeer::PZNextpeer()
    {
        
    }
    
    PZNextpeer::~PZNextpeer()
    {
        
    }
    
    PZNextpeer* PZNextpeer::shared(){
        if (! s_np) {
            s_np = new PZNextpeer();
        }
        return s_np;
    }
    
    /** @name Open the dashboard */
    
    /**
     Launches the Nextpeer Dashboard
     
     */
    void PZNextpeer::launchDashboard() {
        [Nextpeer launchDashboard];
    }
    
    /** @name Tournament managment */
    
    /**
     This method is used to push a buffer to the other players.
     This can potentially be used to create custom notifications or some other interactive mechanism that incorporates the other players.
     @param pBuffer. This is the buffer you wish to send to the other players
     @param length. The length of the buffer
     @note  The buffer will be sent to the other players and will activate the
     -(void)nextpeerDidReceiveTournamentCustomMessage: method on their NPTournamentDelegate delegate.
     */
    void PZNextpeer::pushDataToOtherPlayers(void * pBuffer, int length) {
        if (pBuffer)
        {
            [Nextpeer pushDataToOtherPlayers:[NSData dataWithBytes:pBuffer length:length]];
        }        
    }
    
    /**
     Call this method to report the current score for the tournament. This allows Nextpeer to send various notifications about the players' scores.
     
     */
    void PZNextpeer::reportScoreForCurrentTournament(uint32_t score) {
        [Nextpeer reportScoreForCurrentTournament:score];
    }
    
    /**
     Call this method when your game manage the current tournament and the player just died (a.k.a. 'Last Man Standing').
     Nextpeer will call NextpeerDelegate's nextpeerDidTournamentEnd method after reporting the last score.
     
     @note: The method will act only if the current tournament is from 'GameControlled' tournament type
     */
    void PZNextpeer::reportControlledTournamentOverWithScore(uint32_t score) {
        [Nextpeer reportControlledTournamentOverWithScore:score];
    }
    
    /**
     Call this method to check if any tournament is running at the moment.
     
     */
    bool PZNextpeer::isCurrentlyInTournament() {
        return [Nextpeer isCurrentlyInTournament];
    }
    
    /**
     Call this method when the user wishes to exit the current tournament.
     @note This will close any in-game notifiactions and dialogs.
     */
    void PZNextpeer::reportForfeitForCurrentTournament() {
        [Nextpeer reportForfeitForCurrentTournament];
    }
    
    /**
     This method will return the amount of seconds left for this tournament.
     @note: If no tournament is currently taking place then this method will return 0.
     */
    uint32_t PZNextpeer::timeLeftInTournament() {
        return [Nextpeer timeLeftInTournament];
    }
}