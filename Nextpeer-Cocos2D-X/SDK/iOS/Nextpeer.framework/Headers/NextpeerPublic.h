
@class NPDelegatesContainer;
@class NPGamePlayerContainer;

/**
 Defines where the in-game ranking display can appear on the screen.
 */
typedef NS_ENUM(int, NPRankingDisplayScreenPosition)
{
	NPNotificationPosition_TOP = 0, // Default
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
    NPRankingDisplayList = 0,
    
    /// Displays only the current player's avatar, and a label which indicates the rank of the current player relative to all the tournament participants. Does not show any other player.
    NPRankingDisplaySolo
};

/**
 Defines the animation style for the in-game ranking display.
 */
typedef NS_ENUM(int, NPRankingDisplayAnimationStyle) {
    /// Optimised animation, based on the current device. Older devices will have reduced animaiton, to prevent a negative impact on performance.
    NPRankingDisplayAnimationOptimised = 0,
    
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
    NPRankingDisplayAlignmentHorizontal = 0,
    
    /// Vertical alignment - avatars are aligned top-down.
    NPRankingDisplayAlignmentVertical
};

/**
 Defines the screen type to open.
 */
typedef NS_ENUM(int, NPScreenType) {
    NPScreenTypeDefault = 0,
    NPScreenTypeStream,
    NPScreenTypeLeaderboards,
    NPScreenTypeChallenges,
    NPScreenTypeBuddies
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
 Log in to Nextpeer with Facebook user. This method should be invoked when user logs in to Facebook form game UI.
 */
+ (void)loginWithFacebook;

/**
 Logout Facebook user from Nextpeer. This method should be invoked when user logs out from Facebook in game UI.
 */
+ (void)logoutFromFacebook;

/**
 Launches the Nextpeer Dashboard view at the top of your application's keyed window with the stream screen type.
 
 @note If [Nextpeer isNextpeerSupported] returns NO this method will not execute.
 If the player has not yet authorized your app, they will be prompted to setup an
 account or authorize your application before accessing the Nextpeer dashboard.
 */
+ (void)launchDashboard;

/**
 Launches the Nextpeer Dashboard view at the top of your application's keyed window with the given screen type.
 @param screenType The screen type to launch.
 @note If [Nextpeer isNextpeerSupported] returns NO this method will not execute.
 If the player has not yet authorized your app, they will be prompted to setup an
 account or authorize your application before accessing the Nextpeer dashboard.
 */
+ (void)launchDashboardWithType:(NPScreenType)screenType;

/**
 Call this method to verify if the current run time environment supports Nextpeer requirements.
 
 @note Minimum iOS version supported by the SDK is iOS 7.0. You can handle such case by implementing the 
       [NextpeerDelegate nextpeerNotSupportedShouldShowCustomError] method (otherwise Nextpeer will display alert).
 
 @return YES if the run time requirements match, NO otherwise.
 */
+ (BOOL)isNextpeerSupported;

/**
 Use this method to retrieve the current player details such as name and image.
 
 @note If the user never opened Nextpeer's dashboard or Nextpeer was not initialized the method will return nil.
 */
+ (NPGamePlayerContainer *)getCurrentPlayerDetails;

/**
 Call this method to capture a specail moment in you game. A moment can be a new level, high score or any other special event in your game.
 */
+(void)captureMoment;
@end
