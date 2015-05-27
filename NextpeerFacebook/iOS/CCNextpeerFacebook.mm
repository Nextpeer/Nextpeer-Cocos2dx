#import <FacebookSDK/FacebookSDK.h>
#import <Nextpeer/Nextpeer.h>
#import "CCNextpeerFacebook.h"
#import "Nextpeer_iOS.h"

@interface NextpeerFacebookBridgeDelegate : NSObject <NPFacebookBridgeDelegate>

-(NPFacebookSession*) getCurrentFacebookSession;
-(void) destroyCurrentFacebookSession;
-(void) requestFacebookSessionWithPermissions:(NSArray*)permissions completionBlock:(void (^)(NPFacebookSession* session))completionBlock;
-(void) requestFacebookPermissions:(NSArray*)permissions completionBlock:(void (^)(NPFacebookSession* session))completionBlock;

@end

@implementation NextpeerFacebookBridgeDelegate

-(NPFacebookSession*)makeNPFacebookSession:(FBSession*)fbSession
{
    NSString* accessToken = fbSession.accessTokenData.accessToken;
    NSArray* permissions = fbSession.permissions;
    return [NPFacebookSession sessionWithAccessToken:accessToken andPermissions:permissions];
}

-(NPFacebookSession*) getCurrentFacebookSession
{
    [FBSession openActiveSessionWithAllowLoginUI:false];
    if (FBSession.activeSession == nil || !FBSession.activeSession.isOpen) {
        return nil;
    }
    return [self makeNPFacebookSession:FBSession.activeSession];
}

-(void) destroyCurrentFacebookSession
{
    if (FBSession.activeSession != nil) {
        [FBSession.activeSession closeAndClearTokenInformation];
    }
}

-(void) requestFacebookSessionWithPermissions:(NSArray*)permissions completionBlock:(void (^)(NPFacebookSession* session))completionBlock
{
    [FBSession openActiveSessionWithReadPermissions:permissions allowLoginUI:true
        completionHandler:^(FBSession *session, FBSessionState status, NSError *error) {

        if (error == nil && session != nil && session.isOpen) {
            completionBlock([self makeNPFacebookSession:session]);
        }
        else {
            NSLog(@"Facebook open session error: %@", error);
            completionBlock(nil);
        }
    }];
}

-(void) requestFacebookPermissions:(NSArray*)permissions completionBlock:(void (^)(NPFacebookSession* session))completionBlock
{
    if (FBSession.activeSession == nil || !FBSession.activeSession.isOpen) {
        completionBlock(nil);
        return;
    }

    [FBSession.activeSession requestNewReadPermissions:permissions completionHandler:^(FBSession *session, NSError *error) {
        if (error == nil && session != nil && session.isOpen) {
            completionBlock([self makeNPFacebookSession:session]);
        }
        else {
            NSLog(@"Facebook request permissions error: %@", error);
            completionBlock(nil);
        }
    }];
}

@end

namespace nextpeer {

	void CCNextpeerFacebook::initialize() {
		Nextpeer_iOS::getInstance()->setFacebookBridge([NextpeerFacebookBridgeDelegate new]);
	}

	void CCNextpeerFacebook::login() {
		[Nextpeer loginWithFacebook];
	}

	void CCNextpeerFacebook::logout() {
		[Nextpeer logoutFromFacebook];
	}
}
