/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h""

#import "RootViewController.h"

// NP Integration steps: Add those imports
#import "PZNextpeer.h"

// NP Integration steps: You can add this if you wish to support Push notification
/**
 If enabled the application will try to register push notification
 */
// #define NEXTPEER_SHOULD_USE_PUSH_NOTIFICATION 1

@implementation AppController
@synthesize viewController;


#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
    // NP Integration steps: Add the following code
    [self initializeNextpeer];
    [Nextpeer handleLaunchOptions:launchOptions];
    
    
#ifdef NEXTPEER_SHOULD_USE_PUSH_NOTIFICATION
    // Register for push
    [[UIApplication sharedApplication] registerForRemoteNotificationTypes:UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound | UIRemoteNotificationTypeAlert];    
#endif
    
    // NP Integration steps: until here
	
    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
										pixelFormat: kEAGLColorFormatRGBA8
										depthFormat: GL_DEPTH_COMPONENT16
								 preserveBackbuffer: NO
                                                                                 sharegroup:nil
                                                                          multiSampling:NO
                                                                    numberOfSamples:0];
    
    __glView.multipleTouchEnabled = YES;
    // Use RootViewController manage EAGLView 
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
        {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
        }
    else
    {
        // use this mehod on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden: YES];
    
    cocos2d::CCApplication::sharedApplication()->run();
    return YES;
}

-(NSUInteger)application:(UIApplication *)application supportedInterfaceOrientationsForWindow:(UIWindow *)window
{
    if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
        return UIInterfaceOrientationMaskAll;
    else  /* iphone */
        return UIInterfaceOrientationMaskAllButUpsideDown;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
	cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    
	cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}

// NP Integration steps: Add the following callbacks
-(void)application:(UIApplication*)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken
{
    [Nextpeer registerDeviceToken:deviceToken];
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo
{
    [Nextpeer handleRemoteNotification:userInfo];
}

-(void)application:(UIApplication*)application didReceiveLocalNotification:(UILocalNotification *)notification
{
    [Nextpeer handleLocalNotification:notification];
}

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url {
    return [Nextpeer handleOpenURL:url];
}
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation  {
    return [Nextpeer handleOpenURL:url];
}

// NP Integration steps: Add the following methods
#pragma mark -
#pragma mark Nextpeer integration
#pragma mark -

- (void)initializeNextpeer
{
    NSDictionary* settings = [NSDictionary dictionaryWithObjectsAndKeys:
                              [NSNumber numberWithBool:TRUE], NextpeerSettingSupportsDashboardRotation,
                              [NSNumber numberWithInt:NPNotificationPosition_BOTTOM], NextpeerSettingNotificationPosition,
                              [NSNumber numberWithBool:TRUE], NextpeerSettingObserveNotificationOrientationChange,
                              nil];
    
	// NP Integration steps: Make sure to place you code from the developer dashboard
	[Nextpeer initializeWithProductKey:@"PUT_YOUR_PRODUCT_KEY_HERE" andSettings:settings andDelegates:
     [NPDelegatesContainer containerWithNextpeerDelegate:self notificationDelegate:nil tournamentDelegate:self currencyDelegate:nil]];
}


// Public method called from the main menu in order to show Nextpeer dashboard
- (void)showNextpeerDashboard {
    [Nextpeer launchDashboard];
}

/* NextpeerDelegate */

////////////////////////////////////////////////////////////
///
/// @note   This method will be called when a tournament is about to start.
///         The tournament start container will give you some details on the tournament which is about to be played.
///         For example the tournament uuid, name and time.
////////////////////////////////////////////////////////////
-(void)nextpeerDidTournamentStartWithDetails:(NPTournamentStartDataContainer *)tournamentContainer {
    
    // Using Cocos2d notification center to let the cpp scene know that the game starts
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(NP_EVNET_START_GAME);
}

////////////////////////////////////////////////////////////
///
/// @note   This method is invoked whenever the current tournament has finished.
///         In here you can place some cleanup code. For example,
///			you can use this method to recycle the game scene.
///
////////////////////////////////////////////////////////////
-(void)nextpeerDidTournamentEnd {
    
    // Using Cocos2d notification center to let the cpp scene know that the game ended
    cocos2d::CCNotificationCenter::sharedNotificationCenter()->postNotification(NP_EVNET_END_GAME);
}

- (void)nextpeerDashboardWillAppear {
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)nextpeerDashboardWillDisappear {
    cocos2d::CCDirector::sharedDirector()->resume();
}

/* NPNotificationDelegate */

// Disable the Welcome banner on this app
- (BOOL)nextpeerShouldShowWelcomeBanner {
    return NO;
}

// NP Integration steps: until here
@end

