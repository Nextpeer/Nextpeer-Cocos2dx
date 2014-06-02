/*
 Public Nextpeer API - Tournament
 */

#import "NextpeerPublic.h"

@interface Nextpeer (Tournament)

/**
 This method is used to push a buffer to the other players.
 This can potentially be used to create custom notifications or some other interactive mechanism
 that incorporates the other players. The buffer will be sent to the other players and will activate the 
 NPTournamentDelegate::nextpeerDidReceiveTournamentCustomMessage: method on their delegate.
 */
+ (void)pushDataToOtherPlayers:(NSData*)data;

/**
 This method is used to push a buffer to the other players in an unreliable fashion.
 This is usually used to update other game clients about the current game state for this specific player. 
 The buffer will be sent to the other players and will activate the
 NPTournamentDelegate::nextpeerUnreliableDidReceiveTournamentCustomMessage: method on their delegate.
 The data is not guranteed to reach all or even any of the players. Use this method when you need a low latency data transfer.

 -- Note that unerliable data is limited to just 1300 bytes, any buffers over that size will be discarded with a warning to the console.
 */
+ (void)unreliablePushDataToOtherPlayers:(NSData*)data;

/**
 @deprecated In-game notifications are no longer used, so this method is deprecated and will have no effect. Consider using pushMessageToOtherPlayers: instead.
 
 This method will broadcast a notification to the other players in the tournament.
 The current player's image will be displayed along with the text.
 
 To use the current player's name in the message use %PLAYER_NAME%.
 E.g., @"%PLAYER_NAME% sent you a bomb!"
 */
+ (void)pushMessageToOtherPlayers:(NSString*)message DEPRECATED_ATTRIBUTE;

/**
 Call this method to report the current score for the tournament. This allows Nextpeer to send
 various notifications about the players' scores.
 */
+ (void)reportScoreForCurrentTournament:(uint32_t)score;

/**
 Call this method to change the score modifier of the giving recording. The modifier can be negative or positive and thus points will either
 be added or reduced from the recording's score.
 */
+ (void)reportScoreModifier:(int32_t)modifier forRecording:(NSString*)recordingPlayerId;

/**
 Registers to a synchronized event.
 
 A synchronized event can be used to synchronize all players at a particular point in the game. For example, at the beginning of the game, each client may need to load resources, which takes variable time, depending on the player's device. The event will be fired (see [NPTournamentDelegate nextpeerDidReceiveSynchronizedEvent:withReason:]) either when everyone registered for it, or after the specified timeout, and all players will receive it at the same time.
 
 When working with synchronized events, you should be aware of the following edge cases:
 1. Clients who are too late to register to an event will not be notified of the event until they register.
 2. Recordings will pause when they register to an event that wasn't registered to by a real player, and will wait until the event is fired due the registration of a live player(s).
 3. Recordings that are late to register to an event will behave just as regular clients, and will continue their playback as usual.
 
 @param eventName The name of the synchronized event to register to.
 @param timeout The maximum amount of time to wait for all other participants to register for the sync event.
 */
+ (void)registerToSynchronizedEvent:(NSString*)eventName withTimetout:(NSTimeInterval)timeout;

/**
 Call this method to pause the given recording.
 */
+ (void)requestPauseRecording:(NSString*)recordingPlayerId;

/**
 Call this method to resume the given recording.
 */
+ (void)requestResumeRecording:(NSString*)recordingPlayerId;

/**
 Call this method to stop the given recording.
 */
+ (void)requestStopRecording:(NSString*)recordingPlayerId;

/**
 Call this method to rewind the given recording by timeDelta milliseconds.
 */
+ (void)requestRewindRecording:(NSString*)recordingPlayerId withTimeDelta:(uint32_t)timeDelta;

/**
 Call this method to fast forwad the given recording by timeDelta milliseconds.
 */
+ (void)requestFastForwardRecording:(NSString*)recordingPlayerId withTimeDelta:(uint32_t)timeDelta;


/**
 Call this method to check if any tournament is running at the moment.
 */
+ (BOOL)isCurrentlyInTournament;

/**
 Call this method when the user wishes to exit the current tournament.
 This will close any in-game notifiactions and dialogs.
 */
+ (void)reportForfeitForCurrentTournament;

/**
 Call this method when your game manages the current tournament and the player just died (a.k.a. 'Last Man Standing').
 Nextpeer will call the NextpeerDelegate::nextpeerDidTournamentEnd method after reporting the last score.
 
 @note The method will act only if the current tournament is from a 'GameControlled' tournament type.
 */
+ (void)reportControlledTournamentOverWithScore:(uint32_t)score;

/**
 This method will return the amount of seconds left for this tournament.
 
 @note If no tournament is currently taking place then this method will return 0.
 */
+ (NSUInteger)timeLeftInTournament;

/**
 Call this method to enable or disable the in-game ranking display during a tournament. You can change this setting during a tournament (making the ranking display appear and disappear), but will not be animated.
 */
+(void)enableRankingDisplay:(BOOL)enableRankingDisplay;

/**
 Call this method when you have finished running the inter-game logic. The player will be taken to their next tournament.
 
 @see NextpeerDelegate::shouldAllowInterGameScreen
 */
+ (void)resumePlayAgainLogic;

@end
