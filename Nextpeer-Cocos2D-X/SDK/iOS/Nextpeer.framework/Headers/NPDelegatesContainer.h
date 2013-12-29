#import "NextpeerDelegate.h"
#import "NPNotificationDelegate.h"
#import "NPTournamentDelegate.h"
#import "NPCurrencyDelegate.h"

@interface NPDelegatesContainer : NSObject

#if __has_feature(objc_arc)
@property (nonatomic, weak) id<NextpeerDelegate> nextpeerDelegate;
@property (nonatomic, weak) id<NPNotificationDelegate> notificationDelegate;
@property (nonatomic, weak) id<NPTournamentDelegate> tournamentDelegate;
@property (nonatomic, weak) id<NPCurrencyDelegate> currencyDelegate;
#else
@property (nonatomic, assign) id<NextpeerDelegate> nextpeerDelegate;
@property (nonatomic, assign) id<NPNotificationDelegate> notificationDelegate;
@property (nonatomic, assign) id<NPTournamentDelegate> tournamentDelegate;
@property (nonatomic, assign) id<NPCurrencyDelegate> currencyDelegate;
#endif

+ (NPDelegatesContainer*)containerWithNextpeerDelegate:(id<NextpeerDelegate>)aNPDelegate;

+ (NPDelegatesContainer*)containerWithNextpeerDelegate:(id<NextpeerDelegate>)aNPDelegate
									tournamentDelegate:(id<NPTournamentDelegate>)aTournamentDelegate;

+ (NPDelegatesContainer*)containerWithNextpeerDelegate:(id<NextpeerDelegate>)aNPDelegate
								notificationDelegate:(id<NPNotificationDelegate>)aNoticeDelegate;

+ (NPDelegatesContainer*)containerWithNextpeerDelegate:(id<NextpeerDelegate>)aNPDelegate
                                  notificationDelegate:(id<NPNotificationDelegate>)aNoticeDelegate 
                                    tournamentDelegate:(id<NPTournamentDelegate>)aTournamentDelegate;

+ (NPDelegatesContainer*)containerWithNextpeerDelegate:(id<NextpeerDelegate>)aNPDelegate 
                                  notificationDelegate:(id<NPNotificationDelegate>)aNoticeDelegate 
                                    tournamentDelegate:(id<NPTournamentDelegate>)aTournamentDelegate 
                                      currencyDelegate:(id<NPCurrencyDelegate>)aCurrencyDelegate;


@end
