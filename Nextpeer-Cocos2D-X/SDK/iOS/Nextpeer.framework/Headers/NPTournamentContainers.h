# pragma once

/**
 NPTournamentPlayer represents a player, and contains information about them.
 */
@interface NPTournamentPlayer : NSObject <NSCopying>

	/// The player name.
	@property (nonatomic, readonly) NSString* playerName;

	/// A unique and persistent identifier for the player in Nextpeer.
	@property (nonatomic, readonly) NSString* playerId;

	/// The player's avatar image URL.
	@property (nonatomic, readonly) NSString* imageUrl;

	/// The player's coutnry ISO code
	@property (nonatomic, readonly) NSString* countryISOCode;

	/// The player's avatar image. This is a cached object, and may return nil.
	@property (nonatomic, readonly) UIImage* playerImage;

	/// Player's score in the tournament (can be null if the player did not report the score yet)
	@property (nonatomic, readonly) NSNumber* score;

	/// Player's experience
	@property (nonatomic, readonly) uint32_t experience;

	/// Player's level
	@property (nonatomic, readonly) uint32_t level;

	/// A flag specifying if the player is a bot (a recording of a previous game) or a real player.
	@property (nonatomic, readonly) BOOL playerIsBot;

	/// A flag specifying if this player represents the current user.
	@property (nonatomic, readonly) BOOL isCurrentUser;

    /// Marks if the player forfeit the tournament. This can happen, for example, when the player exits mid-tournament in a tournament.
    @property (nonatomic, readonly) BOOL didForfeit;

    /// Marks if the player is still in the game.
    @property (nonatomic, readonly) BOOL isStillPlaying;

@end


/**
 The NPTournamentStatusContainer used to extract some info about the tournament
 */
@interface NPTournamentStartDataContainer : NSObject
	/// The tournament UUID is provided so that your game can identify which tournament needs to be loaded.
	/// You can find the UUID in the developer dashboard
	@property (nonatomic, readonly) NSString* tournamentUuid;

	/// The tournament display name
	@property (nonatomic, readonly) NSString* tournamentName;

	/// A random seed generated for this tournament. All players within the same tournament
	/// receive the same seed from the tournament. Can be used for level generation, to ensure
	/// all players play the same level in a specific game.
	@property (nonatomic, readonly) uint32_t tournamentRandomSeed;

	/// The number of players that started this tournament. Includes the current player.
	@property (nonatomic, readonly) uint32_t numberOfPlayers;

	/// The current player.
	@property (nonatomic, readonly) NPTournamentPlayer* currentPlayer;

	/// An array of the opponents in the tournament (NPTournamentPlayer* elements).
	/// Does not contain the current player.
	@property (nonatomic, readonly) NSArray* opponents;

    /// A flag that states if the current tournament is game controlled
    @property (nonatomic, readonly) BOOL tournamentIsGameControlled DEPRECATED_ATTRIBUTE;
@end

#pragma mark -
#pragma mark Tournament status-related classes
#pragma mark -

/**
 NPTournamentStatusInfo represents the current tournament status - the ranks and scores of the participating players.
 */
@interface NPTournamentStatusInfo : NSObject

	/// An array of NPTournamentPlayer objects, sorted by player ranks in ascending order (player at index 0 is ranked first).
    @property (nonatomic, readonly) NSArray* sortedResults;

@end

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
	/// @note This property can sometimes return nil, this happens if the image for the player that sent the message is una
	@property (nonatomic, readonly) UIImage* playerImage;

	/// Boolean value that indicates if this message came form a bot recording or a real-life player.
	@property (nonatomic, readonly) BOOL playerIsBot;

	/// The custom message (passed as a buffer).
	@property (nonatomic, readonly) NSData* message;
@end

/**
 The NPTournamentCustomMessageContainer can be used to create custom notifications and events while engaging the other players
 that are currently playing. The container that is passed contains the sending user's name and image as well as the message being sent.
 */
@interface NPTournamentCustomMessageContainer : NPTournamentCustomMessageBaseContainer
@end

/**
 The NPTournamentCustomUnreliableMessageContainer can be used to receive updates about the current game state from other players.
 The container that is passed contains the sending user's name and image as well as the message being sent.
 */
@interface NPTournamentCustomUnreliableMessageContainer : NPTournamentCustomMessageBaseContainer
@end
