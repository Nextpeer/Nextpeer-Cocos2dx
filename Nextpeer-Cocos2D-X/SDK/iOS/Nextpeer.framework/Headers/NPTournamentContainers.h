/* 
 This file contains the tournament containers, you can use them to get extra details on the tournament which about to start, or the one which ended.
   More over, you can use the NPTournamentCustomMessageContainer for your in-tournament custom messages.
 */

@class NPTournamentPlayer;

#pragma mark -
#pragma mark NPTournamentCustomMessageBaseContainer
#pragma mark -

/**
 The base class for the reliable and unreliable custom message containers.
 */
@interface NPTournamentCustomMessageBaseContainer : NSObject

/// The player name.
@property (nonatomic, readonly) NSString* playerName;

/// A unique player identifier for the current game.
@property (nonatomic, readonly) NSString* playerId;

/// The player's profile image URL.
@property (nonatomic, readonly) NSString* playerImageUrl;

/// The player image
/// @note This property can sometimes return nil, this happens if the image for the player that sent the message is unavailable.
@property (nonatomic, readonly) UIImage* playerImage;

/// Boolean value that indicates if this message came form a bot recording or a real-life player.
@property (nonatomic, readonly) BOOL playerIsBot;

/// The custom message (passed as a buffer).
@property (nonatomic, readonly) NSData* message;

@end

#pragma mark -
#pragma mark NPTournamentCustomMessageContainer
#pragma mark -

/**
 The NPTournamentCustomMessageContainer can be used to create custom notifications and events while engaging the other players
 that are currently playing. The container that is passed contains the sending user's name and image as well as the message being sent.
 */
@interface NPTournamentCustomMessageContainer : NPTournamentCustomMessageBaseContainer
@end

#pragma mark -
#pragma mark NPTournamentCustomUnreliableMessageContainer
#pragma mark -

/**
 The NPTournamentCustomUnreliableMessageContainer can be used to receive updates about the current game state from other players.
 The container that is passed contains the sending user's name and image as well as the message being sent.
 */
@interface NPTournamentCustomUnreliableMessageContainer : NPTournamentCustomMessageBaseContainer
@end

#pragma mark -
#pragma mark NPTournamentStartDataContainer
#pragma mark -

/**
 The NPTournamentStartDataContainer used to extract some info about the tournament which is about to be played  
 */
@interface NPTournamentStartDataContainer : NSObject 

/// The tournament UUID is provided so that your game can identify which tournament needs to be loaded.
/// You can find the UUID in the developer dashboard
@property (nonatomic, readonly) NSString* tournamentUuid;

/// The tournament display name
@property (nonatomic, readonly) NSString* tournamentName;

/// The tournament time to play in seconds
@property (nonatomic, readonly) uint32_t tournamentTimeSeconds;

/// A random seed generated for this tournament. All players within the same tournament
/// receive the same seed from the tournament. Can be used for level generation, to ensure
/// all players play the same level in a specific game.
@property (nonatomic, readonly) uint32_t tournamentRandomSeed;

/// A flag that states if the current tournament is game controlled
@property (nonatomic, readonly) BOOL tournamentIsGameControlled;

/// The number of players that started this tournament. Includes the current player.
@property (nonatomic, readonly) uint32_t numberOfPlayers;

/// The current player.
@property (nonatomic, readonly) NPTournamentPlayer* currentPlayer;

/// An array of the opponents in the tournament (NPTournamentPlayer* elements). Does not contain the current player.
@property (nonatomic, readonly) NSArray* opponents;

@end

#pragma mark -
#pragma mark NPTournamentEndDataContainer
#pragma mark -

/**
 The NPTournamentEndDataContainer used to extract some info about the tournament which just ended
 */
@interface NPTournamentEndDataContainer : NSObject 

/// The tournament UUID is provided so that your game can identify which tournament needs to be loaded.
/// You can find the UUID in the developer dashboard.
@property (nonatomic, readonly) NSString* tournamentUuid;

/// The player name.
@property (nonatomic, readonly) NSString* playerName;

/// The player total currency amount (after the tournament ended of course).
@property (nonatomic, readonly) uint32_t currentCurrencyAmount;

/// The player rank in the tournament (where 1 means first, 1..tournamentTotalPlayers).
@property (nonatomic, readonly) uint32_t playerRankInTournament;

/// The amount of players in the tournament.
@property (nonatomic, readonly) uint32_t tournamentTotalPlayers;

/// The player's score at the end of the tournament.
@property (nonatomic, readonly) uint32_t playerScore;

@end

#pragma mark -
#pragma mark Tournament status-related classes
#pragma mark -

/**
 NPTournamentStatusInfo represents the current tournament status - the ranks and scores of the participating players.
 */
@interface NPTournamentStatusInfo : NSObject

/// And array of NPTournamentPlayerResults objects, sorted by player ranks in ascending order (player at index 0 is ranked first).
@property (nonatomic, readonly) NSArray* sortedResults;

@end



/**
 NPTournamentPlayer represents a player, and contains information about them.
 */
@interface NPTournamentPlayer : NSObject <NSCopying>

/// The player name.
@property (nonatomic, readonly, strong) NSString* playerName;

/// A unique and persistent identifier for the player in Nextpeer.
@property (nonatomic, readonly, strong) NSString* playerId;

/// The player's avatar image URL.
@property (nonatomic, readonly, strong) NSString* playerImageUrl;

/// The player's avatar image. This is a cached object, and may return nil.
@property (nonatomic, readonly, assign) UIImage* playerImage;

/// A flag specifying if the player is a bot (a recording of a previous game) or a real player.
@property (nonatomic, readonly, assign) BOOL playerIsBot;

/**
 Checks if the receiver represents the current user.

 @return YES if the receiving tournament player object represents the current user, NO otherwise.
 */
-(BOOL)isCurrentUser;

@end



/**
 NPTournamentPlayerResults represents the tournament results for a given player.
 */
@interface NPTournamentPlayerResults : NSObject

/// The player for which this object reports the results.
@property (nonatomic, readonly, strong) NPTournamentPlayer* player;

/// Marks if the player is still in the game.
@property (nonatomic, readonly, assign) BOOL isStillPlaying;

/// Marks if the player forfeit the tournament. This can happen, for example, when the player exits mid-tournament in a timed tournament.
@property (nonatomic, readonly, assign) BOOL didForfeit;

/// The score of the player.
@property (nonatomic, readonly, assign) uint32_t score;

@end
