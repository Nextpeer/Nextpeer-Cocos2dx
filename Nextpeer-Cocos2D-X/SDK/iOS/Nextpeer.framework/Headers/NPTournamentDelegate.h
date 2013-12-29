#import "NPTournamentContainers.h"

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
 This method is invoked whenever the current tournament has finished
 and the platform gathered the information from all the players.
 It might take some time between the call to NextpeerDelegate::nextpeerDidTournamentEnd to this,
 as the platform retrieving the last result of each player.
 */
-(void)nextpeerDidReceiveTournamentResults:(NPTournamentEndDataContainer*)tournamentContainer;

@end
