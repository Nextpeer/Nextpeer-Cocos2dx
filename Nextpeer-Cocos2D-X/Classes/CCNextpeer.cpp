//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//

#include "CCNextpeer.h"

#include "CCPlatformConfig.h"

#ifndef CC_TARGET_PLATFORM
#error "CC_TARGET_PLATFORM should be defined!!!"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#   include "Nextpeer_iOS.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#   include "Nextpeer_Android.h"
#endif

namespace nextpeer
{
    CCNextpeer* CCNextpeer::sharedInstance = 0;
    
    CCNextpeer::CCNextpeer() {};
    CCNextpeer::~CCNextpeer() {};
    
    CCNextpeer* CCNextpeer::getInstance()
    {
        if (CCNextpeer::sharedInstance == 0) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            CCNextpeer::sharedInstance = new Nextpeer_iOS();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            CCNextpeer::sharedInstance = new Nextpeer_Android();
#else
            CCNextpeer::sharedInstance = 0; // unsupported platform
#endif
        }
        
        return CCNextpeer::sharedInstance;
    }
};
