//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//

#ifndef __NextpeerEventQueue__
#define __NextpeerEventQueue__

#include <pthread.h>
#include <deque>
#include <string.h>
using namespace std;

#include "cocos2d.h"
USING_NS_CC;

// On Android we queue the events and let the main loop scheduler pull them.
// This way we can communicate with the main thread of the game engine.
// Note that this is not needed on iOS.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#   define USE_EVENT_QUEUE
#endif

namespace nextpeer {
    class NextpeerEventQueue
    {
    protected:
        static NextpeerEventQueue* _instance;
        NextpeerEventQueue();
        
    public:
        static NextpeerEventQueue* getInstance();
        
        void addToQueue(string eventName, CCObject* data);
        unsigned long queueSize();
        pair<string, CCObject*> popQueue();
        
    protected:
        deque<pair<string, CCObject*> > _queue;
        pthread_mutex_t _lock;
    };
}

#endif /* defined(__NextpeerEventQueue__) */
