//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//

#include "NextpeerEventQueue.h"

namespace nextpeer {
    NextpeerEventQueue* NextpeerEventQueue::_instance = 0;
    
    NextpeerEventQueue::NextpeerEventQueue()
    {
        pthread_mutex_init(&_lock, NULL);
    }
    
    NextpeerEventQueue* NextpeerEventQueue::getInstance()
    {
        if (!_instance) {
            _instance = new NextpeerEventQueue();
        }
        
        return _instance;
    }
    
    void NextpeerEventQueue::addToQueue(string eventName, Ref *data)
    {
        CC_SAFE_RETAIN(data);
        pthread_mutex_lock(&_lock);
        
        _queue.push_back(pair<string, Ref*>(eventName, data));
        
        pthread_mutex_unlock(&_lock);
    }
    
    unsigned long NextpeerEventQueue::queueSize()
    {
        return _queue.size();
    }
    
    pair<string, Ref*> NextpeerEventQueue::popQueue()
    {
        pthread_mutex_lock(&_lock);
        
        pair<string, Ref*> first = _queue[0];
        _queue.pop_front();
        
        if (first.second) first.second->autorelease();
        
        pthread_mutex_unlock(&_lock);
        
        return first;
    }
}
