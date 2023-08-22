/*
 *******************       Airplay 发现服务       ******************
 
 * 注意：需要在 Info.plist 中添加项目
 * 1. Privacy - Local Network Usage Description
 * 2. Bonjour services  添加  _airplay._tcp.
 
 */

#import <Foundation/Foundation.h>
//! Project version number for WXAirplaySender.
FOUNDATION_EXPORT double WXAirplaySenderVersionNumber;

//! Project version string for WXAirplaySender.
FOUNDATION_EXPORT const unsigned char WXAirplaySenderVersionString[];

NS_ASSUME_NONNULL_BEGIN

@protocol WXAirplaySenderDelegate;

@interface WXAirplaySender : NSObject

/// 是否为搜索中
@property (nonatomic, assign, getter=isSearching) BOOL searching;

/// 搜到的设备
@property (nonatomic, strong) NSMutableArray *searchedDevices;

/// 设备过滤
/// 默认为 false ，开启后会显示所有能检索到的 AirPlay 设备。部分设备会有搜索限制，不会在系统的 AirPlay 列表中展示。
@property (nonatomic, assign) BOOL showAll;


/// Activate
/// @param appId     appId
/// @param appSecret activation code
+ (void)registWithAppId:(NSString* _Nonnull)appId appSecret:(NSString* _Nonnull)appSecret registResult:(void (^_Nullable)(BOOL success))registResultBlock;

- (instancetype)initWithDelegate:(id<WXAirplaySenderDelegate>)delegate;

/// 开始搜索设备
- (void)startSearch;

/// 结束搜索设备
- (void)stopSearch;

@end

@interface WXAirplayDevice: NSObject
/// 设备名
@property (nonatomic, copy) NSString *name;
/// 设备IP地址
@property (nonatomic, copy) NSString *host;
/// 设备端口
@property (nonatomic, assign) int port;

@property (nonatomic, strong) NSDictionary *infos;

- (instancetype)initWithInfo:(NSDictionary *)info;

@end

@protocol WXAirplaySenderDelegate <NSObject>

- (void)wxAirplaySenderSearchedDevice:(WXAirplayDevice *)device;

- (void)wxAirplaySenderLostDevice:(WXAirplayDevice *)device;
@end

NS_ASSUME_NONNULL_END
