//
//  Created by Nextpeer development team.
//  Copyright (c) 2013 Nextpeer, Inc. All rights reserved.
//


#include "NextpeerPlayer.h"

namespace nextpeer
{
    NextpeerPlayer* NextpeerPlayer::create(string playerName, string playerId, string playerImageUrl, bool isRecording)
    {
        NextpeerPlayer* player = new NextpeerPlayer();

        player->init(playerName, playerId, playerImageUrl, isRecording);
        
        player->autorelease();
        return player;
    }
    
    void NextpeerPlayer::init(string playerName, string playerId, string playerImageUrl, bool isRecording)
    {
        this->setPlayerName(playerName);
        this->setPlayerId(playerId);
        this->setPlayerImageUrl(playerImageUrl);
        this->setIsRecording(isRecording);
    }
};

