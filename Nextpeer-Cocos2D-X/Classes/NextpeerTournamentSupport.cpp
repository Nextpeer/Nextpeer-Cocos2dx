//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//

#include "NextpeerTournamentSupport.h"

namespace nextpeer
{
    
    NextpeerTournamentSupport* NextpeerTournamentSupport::_instance = 0;
    
    NextpeerTournamentSupport* NextpeerTournamentSupport::getInstance()
    {
        if (!_instance) _instance = new NextpeerTournamentSupport();
        
        return _instance;
    }
    
    NextpeerTournamentSupport::NextpeerTournamentSupport()
    {}
    
    bool NextpeerTournamentSupport::isTournamentSupported(string tournamentUuid)
    {
        // For now the game supports each tournament. Update this code in case you wish to filter out a tournament.
        // If you do update this code, make sure not to create a auto release pool or do any long consuming task as this method getting called from the background thread (so don't do any main thread related things either).
        return true;
    }
};

