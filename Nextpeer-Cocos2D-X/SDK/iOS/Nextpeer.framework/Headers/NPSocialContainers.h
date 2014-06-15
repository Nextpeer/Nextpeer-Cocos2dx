/* 
 This file contains the social containers, you can use them to get extra details on the current player.
 */

#pragma mark -
#pragma mark NPGamePlayerContainer
#pragma mark -

/**
 The NPGamePlayerContainer can be used to retrieve data on the current player.
 */
@interface NPGamePlayerContainer : NSObject 

/// The player ID.
@property (nonatomic, readonly) NSString* playerId;

/// The player name.
@property (nonatomic, readonly) NSString* playerName;

/// The player image URL.
@property (nonatomic, readonly) NSString* profileImageUrl;

/// The player image.
/// @note This property can sometimes return nil (happens if the image is unavailable in the local cache).
@property (nonatomic, readonly) UIImage* playerImage;

/// Whether or not the current player is a Facebook (or Twitter in the future for example) user or not.
@property (nonatomic, readonly) BOOL isSocialAuthenticated;

@end
