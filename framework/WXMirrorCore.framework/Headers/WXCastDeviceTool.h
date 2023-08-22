//
//  WXCastDeviceTool.h
//  WXMirrorCore
//
//  Created by fbs on 2022/6/23.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WXCastDeviceTool : NSObject

+ (BOOL)isWifiConnect;

+ (NSString *)getIPAddress:(BOOL)preferIPv4;

/// 获取设备当前 IP 地址
+ (NSString *)deviceIpAddress;

/// 获取设备当前 IP 前缀
+ (NSString *)deviceIpPrefix;

+ (NSDictionary *)getIPAddresses;

+ (NSData *)deviceHostData;

+ (BOOL)checkSameNat:(NSString *)targetHost nativeHost:(NSString *)nativeHost;

#pragma mark -

+ (NSString *)deviceUUID;

// 获取设备类型
+ (NSString *)deviceModel;

// 获取系统版本
+ (NSString *)deviceVersion;

/// 获取屏幕尺寸
+ (CGSize)deviceSize;

/// 获取屏幕分辨率
+ (CGSize)deviceResolution;

+ (BOOL)deviceIsFullScreen;


@end

@interface WXCastFPSTool : NSObject

- (void)start:(void(^)(NSInteger))block;

- (void)end;

@end

@interface WXCastMemoryTool : NSObject

//当前app内存使用量
+ (NSInteger)useMemoryForApp;

//设备总的内存
+ (NSInteger)totalMemoryForDevice;

@end

NS_ASSUME_NONNULL_END
