@class NPDelegatesContainer;

/**
 Defines where notifications (including the in-game ranking display) can appear on the screen.
 */
typedef NS_ENUM(int, NPNotificationPosition)
{
    /// The default notification position.
	NPNotificationPosition_TOP = 1,
    
	NPNotificationPosition_BOTTOM,
	NPNotificationPosition_TOP_LEFT,
	NPNotificationPosition_BOTTOM_LEFT,
	NPNotificationPosition_TOP_RIGHT,
	NPNotificationPosition_BOTTOM_RIGHT,
    NPNotificationPosition_LEFT,
    NPNotificationPosition_RIGHT
};

/**
 Defines the possible styles for the in-game ranking display.
 */
typedef NS_ENUM(int, NPRankingDisplayStyle) {
    /// Displays the ranks as a list of 2 or 3 players, centered on the current player, who is flanked by the players immediately above and below him in rank.
    NPRankingDisplayList = 1,
    
    /// Displays only the current player's avatar, and a label which indicates the rank of the current player relative to all the tournament participants. Does not show any other player.
    NPRankingDisplaySolo
};

/**
 Defines the animation style for the in-game ranking display.
 */
typedef NS_ENUM(int, NPRankingDisplayAnimationStyle) {
    /// Optimised animation, based on the current device. Older devices will have reduced animaiton, to prevent a negative impact on performance.
    NPRankingDisplayAnimationOptimised = 1,
    
    /// Full animation (on all devices). In some cases this may negatively affect performance, particularly on older devices.
    NPRankingDisplayAnimationFull,
    
    /// No animation (on all devices). Use this if testing shows that the optimised animation style negatively affects performance.
    NPRankingDisplayAnimationNone
};

/**
 Defines the alignment of the in-game ranking display.
 */
typedef NS_ENUM(int, NPRankingDisplayAlignment) {
    /// Horizontal alignment - avatars are aligned left-to-right.
    NPRankingDisplayAlignmentHorizontal = 1,
    
    /// Vertical alignment - avatars are aligned top-down.
    NPRankingDisplayAlignmentVertical
};

@interface Nextpeer : NSObject

/**
 @return The release Version String of the Nextpeer client library in use.
 */
+ (NSString*)releaseVersionString;

/**
 @param productKey This is your unique product key you received when registering your application. Is copied.
 @param delegatesContainer The delegates container is retained but none of the delegates in the container are retained.
 */
+ (void)initializeWithProductKey:(NSString*)productKey
                    andDelegates:(NPDelegatesContainer*)delegatesContainer;

/**
 @param productKey This is your unique product key you received when registering your application. Is copied.
 @param settings The available settings are defined as NextpeerSettingXXXXXXXXXXXX. See NextpeerSettings.h.
 @param delegatesContainer The delegates container is retained but none of the delegates in the container are retained.
 */
+ (void)initializeWithProductKey:(NSString*)productKey
                     andSettings:(NSDictionary*)settings
                    andDelegates:(NPDelegatesContainer*)delegatesContainer;

/**
 Launches the Nextpeer Dashboard view at the top of your application's keyed window.
 
 @note If [Nextpeer isNextpeerSupported] returns NO this method will not execute.
 If the player has not yet authorized your app, they will be prompted to setup an
 account or authorize your application before accessing the Nextpeer dashboard.
 */
+ (void)launchDashboard;

/**
 Removes the Nextpeer dashboard from your application's keyed window.
 */
+ (void)dismissDashboard;

/**
 Call this method when you wish to change the notification orientation in run time.
 It's preferable to use the settings dictionary if you wish to set this up at start-time.
 
 @deprecated This method no longer has any effect. Please use the NextpeerSettingNotificationOrientation and NextpeerSettingObserveNotificationOrientationChange keys in NextpeerSettings.h.
 */
+ (void)setNotificationOrientation:(UIInterfaceOrientation)orientation DEPRECATED_ATTRIBUTE;

/**
 Let the platform handle a url request, this will used when the Facebook App redirects to the app during the SSO process.
 
 @note The SDK may launch the Nextpeer dashboard under some scenarios from this call.
 
 @param url The URL that was passed to the application delegate's handleOpenURL method(s).
 
 @return YES if the url starts with np[app_id] and the SDK handled the request; NO if the attempt to handle the URL failed (not supported by the platform).
 */
+ (BOOL)handleOpenURL:(NSURL *)url;

/**
 Call this method to verify if the current run time environment supports Nextpeer requirements.
 
 @note Minimum iOS version supported by the SDK is iOS 4.0. You can handle such case by implementing the 
       [NextpeerDelegate nextpeerNotSupportedShouldShowCustomError] method (otherwise Nextpeer will display alert).
 
 @return YES if the run time requirements match, NO otherwise.
 */
+ (BOOL)isNextpeerSupported;

/**
 Call this method register this user's device token. This will allow Nextpeer to send invitations to this user
 when he/she is invited to play the current game. Note that this is only relevant if you've followed the push notification
 integration instructions and provided the p12 file for your game.
 
 @param deviceToken The device token, as reported by the iOS SDK.
 
 Example:
 
     - (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
         // Updates the device token and registers the token with Nextpeer
         [Nextpeer registerDeviceToken:deviceToken];
     }
 
 */
+ (void)registerDeviceToken:(NSData*)deviceToken;

/**
 Call this method after the launching of the app. This allows Nextpeer to respond to any push or local notifications
 that may have been received when the app was in the background.
 Note that you will need to call this method after Nextpeer has already been initialized.
 
 @param launchOptions The launch options of the application, as reported by the iOS SDK.
 
 Example:
 
     - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
         ...
         [Nextpeer initializeWithProductKey:...];
         ...
         [Nextpeer handleLaunchOptions:launchOptions];
         ...
     }
 
 @return Returns a boolean value indicating if the notification will be handled by Nextpeer.
 */
+ (BOOL)handleLaunchOptions:(NSDictionary*)launchOptions;

/**
 Call this method after the receiving a remote push notification while the app is running.
 
 @param userInfo The user info for the notification, as reported by the iOS SDK.
 
 Example:
 
     - (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
        ...
        [Nextpeer handleRemoteNotification:userInfo];
        ...
     }
 
 @return Returns a boolean value indicating if the notification will be handled by Nextpeer.
 */
+ (BOOL)handleRemoteNotification:(NSDictionary*)userInfo;

/**
 Call this method after the receiving a local push notification while the app is running.
 
 @param notification The notification, as reported by the iOS SDK.
 
 Example:
 
     - (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification {
         ...
         [Nextpeer handleLocalNotification:notification];
         ...
     }
 
 @return Returns a boolean value indicating if the notification will be handled by Nextpeer.
 */
+ (BOOL)handleLocalNotification:(UILocalNotification*)notification;

@end