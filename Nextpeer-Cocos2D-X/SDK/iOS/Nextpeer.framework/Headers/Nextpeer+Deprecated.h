/*
 Public Nextpeer API - Deprecated API
 */
#import "NextpeerPublic.h"

/**
 The following API has been deprected from Nextpeer.
 */
@interface Nextpeer (Deprecated)

#pragma mark - Notification

/**
 Let the platform handle a url request, this will used when the Facebook App redirects to the app during the SSO process.
 
 @note The SDK may launch the Nextpeer dashboard under some scenarios from this call.
 
 @param url The URL that was passed to the application delegate's handleOpenURL method(s).
 
 @return YES if the url starts with np[app_id] and the SDK handled the request; NO if the attempt to handle the URL failed (not supported by the platform).
 */
+ (BOOL)handleOpenURL:(NSURL *)url DEPRECATED_ATTRIBUTE;

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
+ (BOOL)handleLocalNotification:(UILocalNotification*)notification DEPRECATED_ATTRIBUTE;

#pragma mark - Feed

/**
 Use this method to open Nextpeer's feed dashboard.
 */
+ (void)openFeedDashboard DEPRECATED_ATTRIBUTE;

#pragma mark - Social

/**
 Use this method to invoke the Facebook post dialog.
 The user will be prompted to login if she hasn't done that before.
 
 @param message Message to be displayed on the wall. Must be specified.
 @param link Link for the given post. Could link to anywhere. If nil then the link would be to the app's iTunes page (what was specified in Nextpeer's dashboard).
 @param imageUrl URL for an image to be displayed on the post. If nil then the image is the app's icon as it appears in Nextpeer's dashboard.
 */
+ (void)postToFacebookWallMessage:(NSString*)message link:(NSString*)link imageUrl:(NSString*)imageUrl DEPRECATED_ATTRIBUTE;

#pragma mark - Tournament

/**
 This method will return the amount of seconds left for this tournament.
 
 @return The number of seconds left in the tournament, or 0 if there is no ongoing tournament or if the tournament is not time-based.
 */
+ (NSUInteger)timeLeftInTournament DEPRECATED_ATTRIBUTE;

/**
 Call this method when you have finished running the inter-game logic. The player will be taken to their next tournament.
 
 @see [NextpeerDelegate shouldAllowInterGameScreen]
 */
+ (void)resumePlayAgainLogic DEPRECATED_ATTRIBUTE;

@end
