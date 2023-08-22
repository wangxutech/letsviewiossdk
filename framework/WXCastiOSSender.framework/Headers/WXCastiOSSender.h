#import <Foundation/Foundation.h>
#import <WXCastiOSSender/WXCastiOSSenderBroadcast.h>
#import <WXMirrorCore/WXMirrorDevice.h>

//! Project version number for WXCastiOSSender.
FOUNDATION_EXPORT double WXCastiOSSenderVersionNumber;

//! Project version string for WXCastiOSSender.
FOUNDATION_EXPORT const unsigned char WXCastiOSSenderVersionString[];

@protocol WXCastiOSSenderDelegate;

typedef NS_ENUM(NSInteger, WXCastiOSSenderServiceState) {
    WXCastiOSSenderServiceStateStop,                        // 连接服务器关闭
    WXCastiOSSenderServiceStateStart,                       // 连接服务器开启
    WXCastiOSSenderServiceStateReconnect,                   // 连接服务器重连中
};

/// 服务错误码
typedef NS_ENUM(NSInteger,  WXCastiOSSenderError) {
    WXCastiOSSenderErrorUnknow                     = 1000,  // 未知错误
    WXCastiOSSenderErrorRegistFail                 = 1010,  // 激活异常
    WXCastiOSSenderErrorListenerTimeout            = 2011,  // 直连投屏超时
    WXCastiOSSenderErrorCastSearchFail             = 3011,  // 投屏码投屏通信失败
    WXCastiOSSenderErrorCastSearchRefuse           = 3012,  // 投屏码投屏被拒绝
    WXCastiOSSenderErrorCastSystemLow              = 3013,  // 录屏模块开启异常，系统版本低，需要手动开启
    WXCastiOSSenderErrorCastChannelDisconnect      = 3014,  // 开始录制前连接已经断开
};

@interface WXCastiOSSender : NSObject

/// 代理
@property (nonatomic, weak) id<WXCastiOSSenderDelegate> delegate;

/// 录屏应用是否开启
@property (nonatomic, assign) BOOL isBroadcastOpen;

/// 是否需要在应用进入后台时主动断开服务器
/// 默认未开启
@property (nonatomic, assign) BOOL backgroundReconnect;

/// Activate
/// @param name 设备名称
/// @param appId 申请 SDK 的 appId
/// @param appSecret 申请 SDK 的 appSecret (格式 xxxxx-xxxxx-xxxxx-xxxxx)
+ (void)registWithDeviceName:(NSString *_Nonnull)name appId:(NSString *_Nonnull)appId appSecret:(NSString *_Nonnull)appSecret registResult:(void (^_Nullable)(BOOL success))registResultBlock;

/// 配置录屏扩展信息
/// @param extensionBundleId 录屏应用的 bundleid
/// @param groupId           应用配置的 appgroup
- (void)configReplayKit:(NSString *_Nonnull)extensionBundleId appGroup:(NSString *_Nonnull)groupId;

/// 开启连接服务
/// @param port  连接通信端口，用于与接收端建立连接
/// @param block 开启服务回调
- (void)startMirrorService:(int)port result:(void (^_Nullable)(BOOL))block;

/// 关闭连接服务
- (void)stopMirrorService;


/// 开启server后，开始发送设备信号，连接周边设备
/// @param port 进行广播搜索时需要配置，采用其他方式搜索。需要与接收端保持一致
/// @param backport 备用端口，如果不使用可以设置为0
- (void)startSearch:(int)port backPort:(int)backport;


/// 开启server后，开始发送设备信号，连接周边设备
/// @param port 进行广播搜索时需要配置，采用其他方式搜索。需要与接收端保持一致
/// @param backport 备用端口，如果不使用可以设置为0
/// @param name 进行bonjour广播搜索时需要配置，如果不使用可以设置为nil
- (void)startSearch:(int)port backPort:(int)backport bonjour:(NSString *_Nullable)name;


/// 结束发送设备信号
- (void)stopSearch;


/// 开启录屏扩展，输出录屏数据
/// 会打开录屏应用的扩展。只支持到 iOS 12.0 ，低版本的系统需要在调用后提示用户自己从系统录屏处开启功能
- (void)openBroadcast;

/// 检测录屏扩展是否开启
/// 录屏扩展可能会被系统关闭，例如熄屏，此时发送不了回调。通过主动检测确认
- (void)checkBroadcast:(void (^_Nullable)(BOOL open))block;

/// 关闭录屏扩展，会关闭所有投屏
/// @param showAlert true=展示直播弹窗 false=直接关闭
- (void)closeBroadcast:(BOOL)showAlert;


/// 投屏到设备
/// 需要先开启录屏 -openBroadcast ，之后再调用！
/// @param host 目标设备IP地址
/// @return 0=发送投屏消息失败 1=发送投屏消息成功 2=直连广播发起成功 -1=请先配置录屏参数 -2=请先开启录屏
- (int)mirrorToDeivce:(NSString * _Nonnull)host;

/// 投屏到设备
/// 需要先开启录屏 -openBroadcast ，之后再调用！
/// @param msg 携带自定义消息
- (int)mirrorToDeivce:(NSString * _Nonnull)host withCustomMsg:(NSString *_Nonnull)msg;

/// 暂停投屏画面
/// @param pause true=暂停 false=开始
- (void)pauseVideo:(BOOL)pause;

/// 暂停投屏声音
/// 需要开通投射音频权限
- (void)pauseAudio:(BOOL)pause;

/// 关闭投屏
/// @param host 目标设备IP。如果传 nil，会关闭当前所有的投屏
- (void)stopMirror:(NSString * _Nonnull)host;


/// 发送自定义消息
/// @param msg 消息内容
/// @param host 目标设备ip
/// @param completionHandler 发送结果回调 0=success 1=fail
- (void)sendCustomMsg:(NSString *_Nonnull)msg toDevice:(NSString *_Nonnull)host completionHandler:(nullable void (^)(int status))completionHandler;


/// 投屏码投屏
/// 12以上设备内部自动开启录屏
/// @param code 目标设备投屏码
- (BOOL)castTo:(NSString *_Nonnull)code;

/// 解析投屏码
- (NSString *_Nonnull)checkCastCode:(NSString *_Nonnull)code;

@end

@protocol WXCastiOSSenderDelegate <NSObject>
@optional

/// 连接到设备
/// @param device 设备信息
- (void)wxCastiOSSenderConnectDevice:(WXMirrorDevice *_Nonnull)device;

/// 与设备断开
/// @param device 设备信息
- (void)wxCastiOSSenderDisconnectDevice:(WXMirrorDevice *_Nonnull)device;

/// 收到投屏的邀请
/// @param device 设备信息
- (void)wxCastiOSSenderReceiveCastRequestFromDevice:(WXMirrorDevice *_Nonnull)device;

/// 录屏应用开启
/// @param code 2=录屏开启成功，内部自动连接 1=录屏开启成功，需要手动调用mirrorTo连接 0=录屏服务开启失败
- (void)wxCastiOSSenderBroadCastOpen:(int)code;

/// 录制应用关闭
- (void)wxCastiOSSenderBroadCastClose;

/// 开启投屏连接
- (void)wxCastiOSSenderMirrorConnect:(nonnull NSString *)host;

/// 关闭投屏连接
- (void)wxCastiOSSenderMirrorDisconnect:(nonnull NSString *)host;

/// 回调-接收自定义消息
/// @param msg 消息内容
/// @param host 发射端ip
- (void)wxCastiOSSenderReceive:(nonnull NSString *)msg fromDevice:(nonnull NSString *)host;

/// 连接服务器状态变更
- (void)wxCastiOSSenderServiceStateChange:(WXCastiOSSenderServiceState)state;

/// 回调-收到错误提示
- (void)wxCastiOSSenderOnError:(nonnull NSError *)error;

/// 回调-投屏码投屏连接成功
/// 此时已经通信完毕，12及以上设备内部会自动开启录屏应用，旧系统需要手动调用录屏
- (void)wxCastiOSSenderOnCastLink:(WXMirrorDevice *_Nonnull)device;

@end
