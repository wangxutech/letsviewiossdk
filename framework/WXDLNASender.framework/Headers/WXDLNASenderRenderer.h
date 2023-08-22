/*
 *******************       播放控制       ******************
 
 */
#import <UIKit/UIKit.h>
#import <WXDLNASender/WXDLNASenderDevice.h>
#import <WXDLNASender/WXDLNASenderObjects.h>

@class WXDLNASenderRenderer;

// 响应解析回调协议
@protocol WXDLNASenderResponseDelegate <NSObject>

@optional

/// 播放内容更新
- (void)dlnaRenderer:(WXDLNASenderRenderer *_Nonnull)renderer onMediaChange:(WXDLNASenderMediaInfo *_Nonnull)mediaInfo;

/// 播放状态变更
- (void)dlnaRenderer:(WXDLNASenderRenderer *_Nonnull)renderer onStateChange:(WXDLNASenderRendererState)state;

/// 播放速度变更
- (void)dlnaRenderer:(WXDLNASenderRenderer *_Nonnull)renderer onPlaySpeedChange:(NSString *_Nonnull)speed;

/// 播放进度变更
- (void)dlnaRenderer:(WXDLNASenderRenderer *_Nonnull)renderer onPositionChange:(WXDLNASenderAVPositionInfo *_Nonnull)info;

/// 音频信息变更
- (void)dlnaRenderer:(WXDLNASenderRenderer *_Nonnull)renderer onVolumeResponse:(NSString *_Nonnull)volume isMute:(BOOL)mute;

/// 通信异常报错
- (void)dlnaRenderer:(WXDLNASenderRenderer *_Nonnull)renderer onError:(NSError *_Nonnull)error;

/// 指令回调
- (void)dlnaRenderer:(WXDLNASenderRenderer *_Nonnull)renderer onFunction:(NSString *_Nonnull)function result:(BOOL)result;

@end

NS_ASSUME_NONNULL_BEGIN

@interface WXDLNASenderRenderer : NSObject

@property (nonatomic, strong, readonly) WXDLNASenderDevice *device;

@property (nonatomic, assign, readonly) WXDLNASenderRendererState renderState;

@property (nonatomic, weak) id<WXDLNASenderResponseDelegate>delegate;

/// 初始化
/// @param device 搜索得到的WXDLNASenderDevice
- (instancetype)initWithUPnPDevice:(WXDLNASenderDevice *_Nonnull)device;

/// 设置单个播放信息
/// 成功设置后会收到回调 -onMediaChange
/// 调用 play 来开启播放
/// @param mediaInfo 多媒体信息
- (void)setAVTransport:(WXDLNASenderMediaInfo *)mediaInfo;

/// 播放
- (void)play;

/// 暂停
- (void)pause;

/// 结束
- (void)stop;

/// 跳转进度
/// @param relTime 进度时间(单位秒)
- (void)seek:(float)relTime;

/// 快进/快退
/// @param isForward true:快进,false:快退
/// @param relTime   调整时间（单位秒）
- (void)seek:(BOOL)isForward interval:(int)relTime;

/// 设置音频值
/// @param value 0-100
- (void)setVolume:(int)value;

/// 静音，需要接收端支持
/// @param mute true=静音 false=解除
- (void)setMute:(BOOL)mute;

/// 切换不同清晰度的播放源
- (void)changeResolution:(WXDLNASenderMediaResolution)type;

/****************    播放状态刷新    ****************/

/// 设置播放状态回调，播放进度回调, 会轮询接收端状态
/// @param interval 默认1s回调一次，如果不需要实时进度和状态回调设置为0
- (void)setRequestInterval:(float)interval;

/// 获取音量
- (void)getVolume;

/// 获取音量，不走 -onVolumeResponse 回调
- (void)getVolumeResponse:(void(^)(int volume))response;

/// 获取静音状态
- (void)getMute;

/// 获取播放进度
- (void)getPositionInfo;

/// 获取播放状态
- (void)getTransportInfo;


/****************    配置播放列表    ****************/

/// 清空播放列表
- (void)clearMediaList;

/// 添加播放列表
/// @param mediaList 播放列表信息
- (void)addMediaList:(NSArray <WXDLNASenderMediaInfo *>*_Nonnull)mediaList;

/// 播放指定视频
/// @param uuid 视频标志符
- (void)playMediaInList:(NSString *_Nonnull)uuid;

/// 播放下一个
- (void)playNextInList;

/// 播放上一个
- (void)playPreviewInList;

@end

NS_ASSUME_NONNULL_END
