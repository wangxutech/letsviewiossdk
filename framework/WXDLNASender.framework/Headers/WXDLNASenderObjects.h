/*
 *******************       视频控制信息       ******************
 
 功能描述
 - 视频时长信息
 - 视频播放状态信息
 
 */
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// 播放状态
typedef NS_ENUM(NSInteger, WXDLNASenderRendererState) {
    WXDLNASenderRendererStateDefault = 0,                       // 默认状态，不需要处理
    WXDLNASenderRendererStateTRANSITIONING,                     // 正在加载
    WXDLNASenderRendererStatePlaying,                           // 正在播放
    WXDLNASenderRendererStatePause,                             // 暂停播放
    WXDLNASenderRendererStateStop,                              // 主动退出播放
    WXDLNASenderRendererStateComplete,                          // 完成单集播放
    WXDLNASenderRendererStateOccupied,                          // 投屏被打断
};


/// 资源类型
typedef NS_ENUM(NSInteger, WXDLNASenderMediaType) {
    WXDLNASenderMediaTypeUnknown = 0,                           // 未知，内部会根据 Url 判断
    WXDLNASenderMediaTypeVideo,                                 // 视频资源
    WXDLNASenderMediaTypeAudio,                                 // 音频资源
    WXDLNASenderMediaTypeImage,                                 // 图片资源
};

/// 分辨率
typedef NS_ENUM(NSInteger, WXDLNASenderMediaResolution) {
    WXDLNASenderMediaResolutionLOW_HIGH = 1,                    // 流畅
    WXDLNASenderMediaResolutionSTD,                             // 标清
    WXDLNASenderMediaResolutionHIGH,                            // 高清
    WXDLNASenderMediaResolutionHD,                              // 超清
    WXDLNASenderMediaResolutionS_HD,                            // 超高清
};

/// 播放循环模式
typedef NS_ENUM(NSInteger, WXDLNASenderMediaLoopMode) {
    WXDLNASenderMediaLoopModeDefault = 0,                       // 默认，播放完结束
    WXDLNASenderMediaLoopModeCycle,                             // 循环播放
};


@interface WXDLNASenderMediaUrl : NSObject

/// 资源链接
@property (nonatomic, copy) NSString *url;

/// 清晰度
@property (nonatomic, assign) WXDLNASenderMediaResolution resolution;

+ (instancetype)media:(WXDLNASenderMediaResolution)resolution url:(NSString *)url;

@end


@interface WXDLNASenderMediaInfo : NSObject

/// 快速初始化，配置资源
- (instancetype _Nonnull)initWithUrlString:(NSString *_Nonnull)url;

/// 资源标识符
/// 投射播放列表时需要进行设置
@property (nonatomic, copy) NSString *uuid;

/// 资源链接
@property (nonatomic, copy) NSString *url;

/// 资源类型
@property (nonatomic, assign) WXDLNASenderMediaType mediaType;

/// 循环模式
@property (nonatomic, assign) WXDLNASenderMediaLoopMode loopMode;

/// 资源标题
/// 根据业务自定义，可选
@property (nonatomic, copy) NSString *title;

/// 起始位置，单位：秒
@property (nonatomic, assign) int startPosition;

/// 跳过片头，单位：秒
/// 根据业务自定义，可选
@property (nonatomic, assign) int headDuration;

/// 跳过片尾，单位：秒
/// 根据业务自定义，可选
@property (nonatomic, assign) int tailDuration;

/// 过期时间
/// 默认无限制，超过设置的时间后不会在推送该片源到接收端`
@property (nonatomic, strong) NSDate *timeoutDate;

/// 加密 IV 字段，根据业务自定义，在 setAVTransport 前进行配置
@property (nonatomic, copy) NSString *decryptIV;

/// 加密 Key 字段，根据业务自定义，在 setAVTransport 前进行配置
@property (nonatomic, copy) NSString *decryptKey;

/// 播放分辨率，默认为标清
@property (nonatomic, assign) WXDLNASenderMediaResolution resolution;

/// 多分辨率资源设置
@property (nonatomic, strong) NSArray <WXDLNASenderMediaUrl *>*mediaUrls;

/// 自定义标记
@property (nonatomic, copy) NSString *metaData;
@end


@interface WXDLNASenderAVPositionInfo : NSObject
/// 投屏链接
@property (nonatomic, copy)   NSString *trackUri;
/// 投屏链接标识
@property (nonatomic, copy)   NSString *trackMetaData;

/// 目前播放视频时长
@property (nonatomic, assign) float trackDuration;
@property (nonatomic, copy)   NSString *trackDurationString;

/// 真实播放时长
@property (nonatomic, assign) float relTime;
@property (nonatomic, copy)   NSString *relTimeString;

/// 相对播放时长
@property (nonatomic, assign) float absTime;
@property (nonatomic, copy)   NSString *absTimeString;

@end

/****************    Error Code    ****************/

/// 搜索服务错误码
typedef NS_ENUM(NSInteger, WXDLNASenderServerError) {
    WXDLNASenderServerErrorUnknow = 1000,                       // 未知错误
    WXDLNASenderServerErrorRegistFail = 1010,                   // 服务启动失败，激活异常
    WXDLNASenderServerErrorNoNetwork = 1020,                    // 服务启动失败，未连接Wi-Fi
    WXDLNASenderServerErrorStartFail = 1030,                    // 服务启动失败，检查本地网络权限
    WXDLNASenderServerErrorSearch = 1031,                       // 搜索异常
    WXDLNASenderServerErrorDeviceConnectFail = 1040,            // 设备连接异常
};

/// 投屏控制错误码
typedef NS_ENUM(NSInteger, WXDLNASenderRendererError) {
    WXDLNASenderRendererErrorUnknow = 2000,                     // 未知错误
    WXDLNASenderRendererErrorDevice = 2010,                     // 连接设备失败
    WXDLNASenderRendererErrorPushFail = 2020,                   // 推送资源失败
    WXDLNASenderRendererErrorUrlTimeout = 2021,                 // 资源过期
};

NS_ASSUME_NONNULL_END
