/*
 *******************       DLNA 发现服务       ******************
 
 功能描述
 - 搜索局域网查找可连接的设备，生成 WXDLNASenderDevice
 
 开启搜索失败排查流程
 - 是否开启网络连接，正常激活sdk
 - 项目是否正确配置本地网络权限（Privacy - Location When In Use Usage Description）
 - Apple 账号是否申请 Multicast Networking 权限并为 App 配置
 - 项目 entitlements 文件是否配置了参数 com.apple.developer.networking.multicast = true
 
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class WXDLNASenderDevice;
@class WXDLNASenderServer;

@protocol WXDLNASenderServerDelegate <NSObject>

/// 设备列表变更
/// @param devices 所有已搜索到的设备
- (void)dlnaServer:(WXDLNASenderServer *)server onDeviceChange:(NSArray <WXDLNASenderDevice *>*_Nonnull)devices;

/// 搜索服务报错
/// @param error WXDLNASenderServerError
- (void)dlnaServer:(WXDLNASenderServer *)server onError:(NSError *_Nonnull)error;

@end

@interface WXDLNASenderServer : NSObject

@property (nonatomic, weak) id<WXDLNASenderServerDelegate> delegate;

/// 服务运行状态
@property (nonatomic, assign) BOOL isRunning;

/// 超时响应时间
/// 默认为3s
@property (nonatomic, assign) int timeoutInterval;


+ (instancetype _Nonnull)shared;

/// Activate
/// @param appId     appId
/// @param appSecret activation code
+ (void)registWithAppId:(NSString* _Nonnull)appId appSecret:(NSString* _Nonnull)appSecret registResult:(void (^_Nullable)(BOOL success))registResultBlock;

/// 启动搜索服务
/// 发现新设备，检测已有设备是否在线
- (BOOL)start;

/// 停止搜索服务
- (void)stop;

/// 获取已经发现的设备
- (NSArray<WXDLNASenderDevice *> *_Nonnull)getDeviceList;
@end

NS_ASSUME_NONNULL_END
