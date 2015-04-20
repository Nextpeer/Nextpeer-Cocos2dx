#pragma once

#import "NPTournamentContainers.h"

@protocol NextpeerDelegate<NSObject>

/**
 This method will be called when a tournament is about to start.
 The tournament start container will give you some details on the tournament which is about to be played.
 For example the tournament UUID, name and time.
 
 @param tournamentContainer The descriptor object for the start of the tournament.
 */
-(void)nextpeerDidTournamentStartWithDetails:(NPTournamentStartDataContainer *)tournamentContainer;

/**
 This method is invoked whenever the current tournament has finished.
 In here you can place some cleanup code. For example, 
 you can use this method to recycle the game scene.
 */
-(void)nextpeerDidTournamentEnd;

@optional

// All of the delegate methods below are optional.
// Implement them only when you need to more finely control Nextpeer's behavior.

/**
 Use this function to tell the SDK whether you support the given tournament. This method
 is called once for each tournament uuid that is present in the dashboard. If this particular
 game version doesn't support a certain tournament, use this function to tell the SDK to disable it.
 
 @param tournamentUuid The tournament ID, as set on the game dashboard.
 
 @return YES if you support this tournament and NO otherwise (default YES).
 */
-(BOOL)nextpeerSupportsTournamentWithId:(NSString* )tournamentUuid;

/**
 The user can be invited to a tournament which is not available. Use this method to customize the alert message which will be presented when the user try to play that match.
 
 @param tournamentUuid The tournament ID, as set on the game dashboard.
 
 @return The dialog message to present.
 */
-(NSString *)nextpeerNotSupportsTournamentMessageWithId:(NSString* )tournamentUuid;

/**
 This is where you should pause your game.
 */
- (void)nextpeerDashboardWillAppear;

/**
 This method is invoked when the dashboard has finished its animated transition and is now fully visible.
 */
- (void)nextpeerDashboardDidAppear;

/**
 This is where Cocoa based games should unpause and resume playback. 

 @warning Since an exit animation will play, this will cause negative performance if your game 
          is rendering on an EAGLView. For OpenGL games, you should refresh your view once and
          resume your game in [NextpeerDelegate nextpeerDashboardDidDisappear].
 */
- (void)nextpeerDashboardWillDisappear;

/**
 This is where OpenGL games should unpause and resume playback.
 */
- (void)nextpeerDashboardDidDisappear;

/**
 This method will be called when the player closes Nextpeer's dashboard and returns to the game.
 */
- (void)nextpeerDashboardDidReturnToGame;

/**
 This method will be called in case Nextpeer is not supported on the device.
 
 @return YES we will not show our error view and let you the opportunity to intervene. Default is NO - we will show a UIAlertView.
 */
-(BOOL)nextpeerNotSupportedShouldShowCustomError;
@end
