#define kNPFacebookPermissionProfile @"public_profile"
#define kNPFacebookPermissionEmail @"email"
#define kNPFacebookPermissionFriends @"user_friends"

@interface NPFacebookSession : NSObject

@property (readonly) NSString* accessToken;
@property (readonly) NSArray* permissions;
@property (readonly) bool hasProfilePermission;
@property (readonly) bool hasEmailPermission;
@property (readonly) bool hasFriendsPermission;

+(NPFacebookSession*)sessionWithAccessToken:(NSString*)accessToken andPermissions:(NSArray*)permissions;

@end

@protocol NPFacebookBridgeDelegate <NSObject>
@required

/** Get details of current active Facebook session (without bringin up Facebook UI).
Should return nil if there is no active Facebook session.
 */
-(NPFacebookSession*) getCurrentFacebookSession;

/** Destroy active Facebook session.
*/
-(void) destroyCurrentFacebookSession;

/** Log user in to Facebook (display Facebook login UI if needed), requesting specified read permissions.
@param permissions Permissions to request.
@param completionBlock Should be invoked with session details after successfull login to Facebook, or with nil if login failed.
 */
-(void) requestFacebookSessionWithPermissions:(NSArray*)permissions completionBlock:(void (^)(NPFacebookSession* session))completionBlock;

/** Invoke Facebook permissions dialog asking for specified read permissions.
@param permissions Permissions to request.
@param completionBlock Should be invoked with session details after permissions dialog was displayed, or with nil if error occured.
 */
-(void) requestFacebookPermissions:(NSArray*)permissions completionBlock:(void (^)(NPFacebookSession* session))completionBlock;

@end
