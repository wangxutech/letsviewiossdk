#import <Foundation/Foundation.h>
//! Project version number for WXMirrorCore.
FOUNDATION_EXPORT double WXMirrorCoreVersionNumber;

//! Project version string for WXMirrorCore.
FOUNDATION_EXPORT const unsigned char WXMirrorCoreVersionString[];

#import <WXMirrorCore/WXMirrorLogger.h>
#import <WXMirrorCore/WXMirrorDevice.h>

@interface WXMirrorCore : NSObject

+ (void)authentications:(NSString *)sdk version:(NSString *)version userAppId:(NSString *)appId activeCode:(NSString *)code response:(void (^)(BOOL, NSString *))resultBlock;

+ (void)active:(NSString *)protocol version:(NSString *)version userAppId:(NSString *)appId activeCode:(NSString *)code response:(void(^)(BOOL result, NSString *msg))resultBlock;

+ (NSArray *)check:(NSString *)protocol;

@end
