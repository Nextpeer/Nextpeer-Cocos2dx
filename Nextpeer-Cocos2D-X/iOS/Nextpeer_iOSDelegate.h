//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//

#ifndef ___NEXTPEER_IOS_DELEGATE_H
#define ___NEXTPEER_IOS_DELEGATE_H

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#import "platform/CCPlatformConfig.h"
#import "Nextpeer/Nextpeer.h"



@interface Nextpeer_iOSDelegate : NSObject <NextpeerDelegate, NPTournamentDelegate>

+(Nextpeer_iOSDelegate*)sharedInstance;

@end

#endif // iOS

#endif // ___NEXTPEER_IOS_DELEGATE_H
