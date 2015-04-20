#import "NextpeerDelegate.h"
#import "NPTournamentDelegate.h"
#import "NPFacebookBridgeDelegate.h"

@interface NPDelegatesContainer : NSObject

#if __has_feature(objc_arc)
@property (nonatomic, weak) id<NextpeerDelegate> nextpeerDelegate;
@property (nonatomic, weak) id<NPTournamentDelegate> tournamentDelegate;
@property (nonatomic, weak) id<NPFacebookBridgeDelegate> facebookBridgeDelegate;
#else
@property (nonatomic, assign) id<NextpeerDelegate> nextpeerDelegate;
@property (nonatomic, assign) id<NPTournamentDelegate> tournamentDelegate;
@property (nonatomic, assign) id<NPFacebookBridgeDelegate> facebookBridgeDelegate;
#endif

+ (NPDelegatesContainer*)containerWithNextpeerDelegate:(id<NextpeerDelegate>)aNPDelegate;

+ (NPDelegatesContainer*)containerWithNextpeerDelegate:(id<NextpeerDelegate>)aNPDelegate
									tournamentDelegate:(id<NPTournamentDelegate>)aTournamentDelegate;

+ (NPDelegatesContainer*)containerWithNextpeerDelegate:(id<NextpeerDelegate>)aNPDelegate
									tournamentDelegate:(id<NPTournamentDelegate>)aTournamentDelegate
								facebookBridgeDelegate:(id<NPFacebookBridgeDelegate>)aFacebookDelegate;

@end
