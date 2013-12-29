@class NPNotificationContainer;

/**
 Implement this delegate to control and be notified of Nextpeer notifications (both outside and inside a game).
 */
@protocol NPNotificationDelegate<NSObject>

@optional
/**
 @deprecated In-game notifications are no longer used and are thus deprecated. This method will never be called. The replacement is the in-game ranking display, see [Nextpeer enableRankingDisplay:] in Nextpeer+Tournament.h if you wish to disable it.
 
 Return whether or not Nextpeer should display a notification with the provided data.
 If false is returned, NPNotificationDelegate::nextpeerHandleDisallowedNotification: gets called.
 If true is returned, NPNotificationDelegate::nextpeerNotificationWillShow: gets called before the notification appears.
 */
- (BOOL)nextpeerIsNotificationAllowed:(NPNotificationContainer *)notice DEPRECATED_ATTRIBUTE; 

/**
 @deprecated In-game notifications are no longer used and are thus deprecated. This method will never be called.
 
 Gets called when NPNotificationDelegate::nextpeerIsNotificationAllowed: returns false. It is recommended to here display some sort of game
 specific version of the notification based on the notification data.
 */
- (void)nextpeerHandleDisallowedNotification:(NPNotificationContainer *)notice DEPRECATED_ATTRIBUTE;

/**
 @deprecated In-game notifications are no longer used and are thus deprecated. This method will never be called.
 
 Gets called every time a notification is about to appear.
 */
- (void)nextpeerNotificationWillShow:(NPNotificationContainer *)notice DEPRECATED_ATTRIBUTE;

/**
 Should return whether Nextpeer can show the welcome banner. Defaults to YES.
 */
- (BOOL)nextpeerShouldShowWelcomeBanner;

/**
 This method is invoked when a tournament status is reported. A tournament status includes information
 regarding all the players in the tournament - their ranks, who is still playing, their names, IDs, avatar images, etc.
 This information can be used to, for example, generate custom ranking notifications.
 
 The rate of tournament status updates is approximately one per second.
 */
-(void)nextpeerDidReceiveTournamentStatus:(NPTournamentStatusInfo*)tournamentStatus;

@end
