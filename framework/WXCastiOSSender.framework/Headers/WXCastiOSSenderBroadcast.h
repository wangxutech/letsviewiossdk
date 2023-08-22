//
//  WXCastiOSSenderBroadcast.h
//  WXCastiOSSender
//
//  Created by fbs on 2022/6/23.
//
/*
 *******************       常见问题       ******************
   1.系统有声音在播放但观众端无法听到声音
     系统在做屏幕音频采集时，在从home界面切到有声音播放的App时才会采集声音，从有声音播放的App切换到无声音播放的App时，即使原App还在播放声音系统也不会进行音频采集，此时需要从home界面重新进入到有声音播放的App时系统才会重新采集。
   2.打开麦克风录制时系统播放声音会变小
     这个是属于系统机制：打开麦克风采集时系统音频处于录制模式，会自动将其它的App播放的声音变为听筒模式，中途关闭麦克风采集也不会恢复，只有关闭或重新启动无麦克风录制时才会恢复为扬声器的播放。这个机制不影响App那路声音的录制，即观众端声音听到的声音大小不受影响。
   3.屏幕录制何时自动会停止
     系统在锁屏或有电话打入时，会自动停止屏幕录制，此时SampleHandler里的broadcastFinished函数会被调用，可在此函数发通知提示用户。
   4.采集推流过程中有时屏幕录制会自动停止问题
     通常是因为设置的推流分辨率过高时在做横竖屏切换过程中容易出现。ReplayKit2的直播扩展目前是有50M的内存使用限制，超过此限制系统会直接杀死扩展进程，因此ReplayKit2上建议推流分辨率不高于720P
 */
#import <Foundation/Foundation.h>
#import <ReplayKit/ReplayKit.h>
#import <WXCastiOSSender/WXCastSenderVideoOptions.h>

NS_ASSUME_NONNULL_BEGIN

@interface WXCastiOSSenderBroadcast : NSObject

/// 开始录屏
/// @param groupId 应用配置的appgroup
/// @param sampleHandler 录屏扩展的 SampleHandler 对象
+ (void)startWithGroup:(NSString*)groupId connectSampleHandler:(RPBroadcastSampleHandler *)sampleHandler videoConfiguration:(WXCastSenderVideoOptions *)configuration;

/// 更新视频参数
+ (void)updateVideoOptions:(WXCastSenderVideoOptions *)options;

/// 结束广播
+ (void)stopBroadcast;

/// 传递多媒体数据
+ (void)processSampleBuffer:(CMSampleBufferRef)buffer sampleBufferType:(RPSampleBufferType)type;

@end

NS_ASSUME_NONNULL_END
