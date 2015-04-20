/*
 Public Nextpeer API - Push Notification
 */
#import "NextpeerPublic.h"

@interface Nextpeer (Push)

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
@end