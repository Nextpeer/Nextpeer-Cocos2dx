#import <Foundation/Foundation.h>

@class NPInGameNotification;

DEPRECATED_ATTRIBUTE
/// @deprecated In-game notifications are no longer used and are thus deprecated. See [NPNotificationDelegate nextpeerDidReceiveTournamentStatus:] for a replacement.
@interface NPNotificationContainer : NSObject 

@property (nonatomic, readonly) NSString* notificationText;
@property (nonatomic, readonly) UIImage* renderedImage;

@end
