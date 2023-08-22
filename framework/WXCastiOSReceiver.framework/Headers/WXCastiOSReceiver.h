#import <Foundation/Foundation.h>
//! Project version number for WXCastiOSReceiver.
FOUNDATION_EXPORT double WXCastiOSReceiverVersionNumber;

//! Project version string for WXCastiOSReceiver.
FOUNDATION_EXPORT const unsigned char WXCastiOSReceiverVersionString[];

NS_ASSUME_NONNULL_BEGIN
@protocol WXCastiOSReceiverDelegate;
@import UIKit;
@class WXMirrorDevice;

@interface WXCastiOSReceiver : NSObject

/// 代理
@property (nonatomic, weak) id<WXCastiOSReceiverDelegate> delegate;

/// udp发现的设备
@property (nonatomic, strong) NSMutableArray <WXMirrorDevice*>*findDevices;

/// 发送安卓反控数据
/// 默认不开启
@property (nonatomic, assign) BOOL touchEnable;

/// 反控手势-滑动是否开启
/// 默认关闭，若打开，则反控只响应点击手势
@property (nonatomic, assign) BOOL touchPanDisable;

/// IP直连后是否直接投屏
/// 默认不开启
/// 开启后接收到直连消息后会直接开启投屏
/// 不开启接收到IP直连消息后只会建立通信通道，不会开启连接
@property (nonatomic, assign) BOOL listenerCastEnable;

/// 投屏心跳超时时间
/// 默认不开启
@property (nonatomic, assign) int timeout;


/// Activate
/// @param name 设备名称
/// @param appId 申请 SDK 的 appId
/// @param appSecret 申请 SDK 的 appSecret (格式 xxxxx-xxxxx-xxxxx-xxxxx)
+ (void)registWithDeviceName:(NSString *_Nonnull)name appId:(NSString *_Nonnull)appId appSecret:(NSString *_Nonnull)appSecret registResult:(void (^_Nullable)(BOOL success))registResultBlock;

/// 配置应用版本参数
/// 可选，与其他设备通信时被识别
- (void)configDeviceInfo:(int)version;


/// 获取投屏码
/// @param needValid 接收投屏时是否要校验投屏码一致
- (NSString *)getCastCode:(BOOL)needValid;

/// 开启通信服务，支持最新的投屏码投屏
- (void)startService:(void (^_Nullable)(BOOL))result;

/// 关闭服务
- (void)stopService;

/****************    搜索连接    ****************/
/// 开启搜索
/// @param port 进行udp广播搜索时需要配置，如果不使用可以设置为0，采用其他方式搜索
- (void)startSearch:(int)port;

/// 开启搜索
/// @param port 进行udp广播搜索时需要配置，如果不使用可以设置为0，采用其他方式搜索
/// @param name 进行bonjour广播搜索时需要配置，如果不使用可以设置为nil
- (void)startSearch:(int)port bonjour:(NSString *_Nullable)name;

/// 暂停搜索
- (void)stopSearch;

/// 自己手动连接设备
/// @param device 设备信息
- (void)addCustomDevice:(WXMirrorDevice *)device;

/// 断开与所有设备的通信连接
- (void)closeConnections;

/// 发送自定义消息
/// @param msg 消息内容
/// @param host 目标设备ip
/// @param completionHandler 发送结果回调 0=success 1=fail
- (void)sendCustomMsg:(NSString *)msg toDevice:(NSString *)host completionHandler:(nullable void (^)(int status))completionHandler;

/****************    接收投屏相关    ****************/

/// 接收到投屏后配置显示用的控件
/// @param view 显示用的控件
/// @param host 投屏设备IP
- (BOOL)configVideoCancasView:(UIView *)view deviceHost:(NSString *)host;

/// 画面变换
/// @param type 0=重置 1=水平镜像 2=竖直镜像 3=顺时针旋转 4=逆时针旋转
/// @param host 目标设备IP
- (void)displayViewTransform:(int)type deviceHost:(NSString *)host;

/// 关闭投屏
/// @param host 目标设备IP。如果传 nil，会关闭当前所有的投屏
- (void)closeMirror:(NSString *_Nullable)host;


/// 主动拉取投屏
/// port 为发射端服务器的连接通信端口
- (void)mirrorToDevice:(NSString *_Nullable)host port:(int)port;

/// 获取投屏设备信息
/// - Parameter host: 设备IP地址
- (WXMirrorDevice *_Nullable)getDeviceInfo:(NSString *)host;

@end

/****************    Error Code    ****************/

/// 搜索服务错误码
typedef NS_ENUM(NSInteger,  WXCastiOSReceiverError) {
    WXCastiOSReceiverErrorUnknow                     = 1000,    // 未知错误
    WXCastiOSReceiverErrorRegistFail                 = 1010,    // 激活异常
    WXCastiOSReceiverErrorOnlyOneDevice              = 1021,    // 只能接收一台投屏设备
};

@protocol WXCastiOSReceiverDelegate <NSObject>

@optional
/// 连接到移动设备
- (void)wxCastiOSReceiverConnectDevice:(WXMirrorDevice *)device;

/// 与移动设备断开连接
- (void)wxCastiOSReceiverDisconnectDevice:(WXMirrorDevice *)device;

/// 回调-开始接收安卓投屏
/// @param host 投屏设备IP
- (void)wxCastiOSReceiverStartMirror:(nonnull NSString *)host customMsg:(NSString* _Nullable)msg;

/// 回调-视频信息
/// 连接上视频数据和屏幕旋转时会传递
/// @param dimensions 画面长宽
/// @param rotation   画面方向 0=竖屏 1=横屏
- (void)wxCastiOSReceiverOnVideo:(nonnull NSString *)host info:(CGSize)dimensions rotation:(int)rotation;

/// 回调-设备信息
/// 连接上视频时返回设备的原始画面尺寸
/// @param dimensions 设备屏幕尺寸
- (void)wxCastiOSReceiverOnVideoDevice:(nonnull NSString *)host info:(CGSize)dimensions;

/// 回调-给出视频源数据 H264
/// 连接上视频数据和屏幕旋转时会传递 sps+pps 数据以及新的关键帧
/// @param data h264数据
- (void)wxCastiOSReceiverOnVideo:(nonnull NSString *)host data:(NSData *)data;

/// 回调-关闭了投屏
/// @param host 投屏设备IP
/// @param code 断开原因 默认为0，正常断开 1=网络
- (void)wxCastiOSReceiverCloseMirror:(nonnull NSString *)host code:(int)code;

/// 回调-接收自定义消息
/// @param msg 消息内容
/// @param host 发射端ip
- (void)wxCastiOSReceiverReceive:(nonnull NSString *)msg fromDevice:(nonnull NSString *)host name:(nonnull NSString *)name;

/// 回调-收到错误提示
- (void)wxCastiOSReceiverOnError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
