#import "NPTournamentContainers.h"

/**
 The reason for firing a synchronized event.
 */
typedef NS_ENUM(int, NPSynchronizedEventFireReason) {
    /// All participants have registered for the event.
    NPSynchronizedEventFireReasonAllReached = 1,
    
    /// The registration timeout was reached before all participants registered for the event (at least one participant didn't register for the event).
    NPSynchronizedEventFireReasonTimeout,
    
    /// The synchronized event was already fired before the latest registration attempt was made.
    NPSynchronizedEventFireReasonAlreadyFired
};

/**
 Implement this protocol to receive various method calls regarding the user's
 interaction with the current Nextpeer tournament
 */
@protocol NPTournamentDelegate <NSObject>

@optional 

/**
 This method will be called when Nextpeer has received a buffer from another player.
 You can use these buffers to create custom notifications and events while engaging the other players
 that are currently playing. The container that is passed contains the sending user's name and image as well
 as the message being sent.
 */
-(void)nextpeerDidReceiveTournamentCustomMessage:(NPTournamentCustomMessageContainer*)message;

/**
 This method will be called when Nextpeer has received a buffer from another player using the unreliable connection.
 You can use these buffers to receive updates about the game state that is going on other players' devices. 
 The container that is passed contains the sending user's name and image as well as the message being sent.
 */
-(void)nextpeerDidReceiveUnreliableTournamentCustomMessage:(NPTournamentCustomUnreliableMessageContainer*)message;

/**
 Tells the delegate that the synchronized event was fired.
 
 The event will only be fired if you registered for it beforehand with [Nextpeer registerToSynchronizedEvent:withTimetout:].
 
 @param eventName The event that was fired.
 @param fireReason The reason for firing the synchronized event.
 */
-(void)nextpeerDidReceiveSynchronizedEvent:(NSString*)eventName withReason:(NPSynchronizedEventFireReason)fireReason;

/**
 This method is invoked when a tournament status is reported. A tournament status includes information
 regarding all the players in the tournament - their ranks, who is still playing, their names, IDs, avatar images, etc.
 This information can be used to, for example, generate custom ranking notifications.
 
 The rate of tournament status updates is approximately one per second.
 
 @param tournamentStatus The current tournament status.
 */
-(void)nextpeerDidReceiveTournamentStatus:(NPTournamentStatusInfo*)tournamentStatus;
@end
