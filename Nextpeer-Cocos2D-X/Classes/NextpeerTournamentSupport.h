//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//

#ifndef __NextpeerTournamentSupport__
#define __NextpeerTournamentSupport__

#include <string>
using namespace std;
#include "cocos2d.h"
USING_NS_CC;

namespace nextpeer {
    // This class will answer whether a tournament is supported or not.
    // You can update it with your game logic, for example a certain tournament is supported after a specific level or XP.
    class NextpeerTournamentSupport : public Ref
    {
    public:
        static NextpeerTournamentSupport* getInstance();
        
        bool isTournamentSupported(string tournamentUuid);
    private:
        NextpeerTournamentSupport();
        static NextpeerTournamentSupport* _instance;
    };
}

#endif /* defined(__NextpeerTournamentSupport__) */