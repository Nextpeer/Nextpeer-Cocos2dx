#pragma once


/**
 NSNumber BOOL
 
 Default: YES
 
 Defines if Nextpeer should observe device orientation change and adjust the dashboard according to changes.
 Nextpeer will keep the transformation in the main orientation. For example if you game supports landscape orientation, Nextpeer will switch between LandscapeLeft to LandscapeRight (but will not switch to portrait).
 */
extern NSString* NextpeerSettingSupportsDashboardRotation;

/**
 NSNumber UIInterfaceOrientation
 
 Default: [UIApplication sharedApplication].statusBarOrientation
 
 Defines the orientation in which the Nextpeer dashboard will be first launched. If not specified, Nextpeer will try to orient itself according to the status bar orientation.
 */
extern NSString* NextpeerSettingInitialDashboardOrientation;

/**
 NSNumber UIInterfaceOrientation

 Default: auto-selection of the orientation depending on the integrated bundle.

 Defines what orientation the the in-game ranking display should appear in by default. The notification system does not auto rotate (unless NextpeerSettingObserveNotificationOrientationChange is specified as YES).
 */
extern NSString* NextpeerSettingNotificationOrientation;

/**
 NSNumber BOOL

 Default: NO

 Defines if Nextpeer should observe notification orientation change and adjust the in-game ranking display accordingly. For example, if your game supports both Landscape Right and Landscape Left rotations, you can set this setting to YES, so that the in-game ranking display will follow the orientation of the game.
 */
extern NSString* NextpeerSettingObserveNotificationOrientationChange;

/**
 NSNumber NPRankingDisplayScreenPosition (see NextpeerPublic.h)

 Default: NPNotificationPosition_TOP.
 
 Specifies where the in-game ranking display will appear.

 Behavior:
	 NPNotificationPosition_TOP              rankings are shown in the top-center of the screen
	 NPNotificationPosition_BOTTOM           rankings are shown in the bottom-center of the screen
	 NPNotificationPosition_BOTTOM_LEFT      rankings are shown in the bottom-left of the screen
	 NPNotificationPosition_TOP_LEFT         rankings are shown in the top-left of the screen
	 NPNotificationPosition_BOTTOM_RIGHT     rankings are shown in the bottom-right of the screen
	 NPNotificationPosition_TOP_RIGHT        rankings are shown in the top-right of the screen
     NPNotificationPosition_LEFT             rankings are shown in the middle-left of the screen
     NPNotificationPosition_RIGHT            rankings are shown in the middle-right of the screen
 */
extern NSString* NextpeerSettingNotificationPosition;

/**
 NSNumber NPRankingDisplayStyle (see NextpeerPublic.h)
 
 Default: NPRankingDisplayList
 
 Specifies the style for the in-game ranking display.
 */
extern NSString* NextpeerSettingRankingDisplayStyle;

/**
 NSNumber NPRankingDisplayAnimationStyle (see NextpeerPublic.h)
 
 Default: NPRankingDisplayAnimationOptimised
 
 Specifies the style of the animation of the in-game ranking display. This setting can be set to optimise performance.
 */
extern NSString* NextpeerSettingRankingDisplayAnimationStyle;

/**
 NSNumber NPRankingDisplayAlignment (see NextpeerPublic.h)
 
 Default: NPRankingDisplayAlignmentHorizontal
 
 Specifies the alignment of the in-game ranking display. This setting only has effect if the ranking display style is set to NPRankingDisplayList.
 */
extern NSString* NextpeerSettingRankingDisplayAlignment;

/**
 NSNumber BOOL
 
 Default: NO
 Nextpeer uses remote and local notifications to alert the user about invites, buddy requests and so on. 
 If the application is in idle state and the user taps on a notification, Nextpeer will open the designated screen to the user.
 This setting will allow you to opt out from this, Nextpeer will not open any UI flow and will merly notify the user on the event.

 */
extern NSString* NextpeerSettingShouldOptOutFromNextpeerPushInteractions;

