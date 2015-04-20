#import "Nextpeer+Push.h"

// Use this macro to create Nextpeer's app delegate right before the main() function of the main.m file.
// If you want to integration push notification support, add a "#define NEXTPEER_ADD_PUSH_NOTIFICATION_SUPPORT" before the #import statem of this header.
#define NEXTPEER_APP_DELEGATE_CREATE(BASE_APP_DELEGATE) \
@interface NextpeerAppDelegate : BASE_APP_DELEGATE \
@end\
\
@implementation NextpeerAppDelegate \
\
- (NSUInteger)application:(UIApplication *)np_application supportedInterfaceOrientationsForWindow:(UIWindow *)np_window \
{ \
return nextpeerAppDelegateSupportedInterfaceOrientationsForWindow(self, np_application, np_window); \
} \
\
_NEXTPEER_PUSH_NOTIFICATION_METHODS \
\
@end


// Use this macro as the name of UIApplication's delegate in the main() function of the main.m file.
#define NEXTPEER_APP_DELEGATE @"NextpeerAppDelegate"





#ifdef NEXTPEER_ADD_PUSH_NOTIFICATION_SUPPORT
#define _NEXTPEER_PUSH_NOTIFICATION_METHODS \
- (BOOL)application:(UIApplication *)np_application didFinishLaunchingWithOptions:(NSDictionary *)np_launchOptions \
{ \
return nextpeerApplicationDidFinishLaunchingWithOptions(self, np_application, np_launchOptions); \
} \
\
-(void)application:(UIApplication*)np_application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)np_deviceToken \
{ \
[Nextpeer registerDeviceToken:np_deviceToken]; \
\
if ([[super class] instancesRespondToSelector:@selector(application:didRegisterForRemoteNotificationsWithDeviceToken:)]) \
{ \
[super application:np_application didRegisterForRemoteNotificationsWithDeviceToken:np_deviceToken]; \
} \
} \
\
- (void)application:(UIApplication *)np_application didReceiveRemoteNotification:(NSDictionary *)np_userInfo \
{ \
[Nextpeer handleRemoteNotification:np_userInfo]; \
\
if ([[super class] instancesRespondToSelector:@selector(application:didReceiveRemoteNotification:)]) \
{ \
[super application:np_application didReceiveRemoteNotification:np_userInfo]; \
} \
}
#else
#define _NEXTPEER_PUSH_NOTIFICATION_METHODS
#endif



// extern "C" is required for Objective-C++, otherwise its linker won't be able to find these symbols.
#if defined __cplusplus
extern "C" {
#endif

NSUInteger nextpeerAppDelegateSupportedInterfaceOrientationsForWindow(id<UIApplicationDelegate> appDelegate, UIApplication* application, UIWindow* window);
BOOL nextpeerApplicationDidFinishLaunchingWithOptions(id<UIApplicationDelegate> appDelegate, UIApplication* application, NSDictionary* launchOptions);

#if defined __cplusplus
};
#endif





