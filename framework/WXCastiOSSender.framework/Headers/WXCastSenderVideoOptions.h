//
//  WXCastSenderVideoConfiguration.h
//  WXCastiOSSender
//
//  Created by fbs on 2022/7/7.
//

#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(int, WXCastSenderVideoFps) {
    WXCastSenderVideoFps20 = 20,
    WXCastSenderVideoFps30 = 30, // 默认
    WXCastSenderVideoFps60 = 60
};

typedef NS_ENUM(int, WXCastSenderVideoResolution) {
    WXCastSenderVideoResolution480 = 480,
    WXCastSenderVideoResolution540 = 540,
    WXCastSenderVideoResolution720 = 720, // 默认
    WXCastSenderVideoResolution1080 = 1080,
    WXCastSenderVideoResolution2k = 1440 // 需要高清设备
};

typedef NS_ENUM(int, WXCastSenderVideoBitrate) {
    WXCastSenderVideoBitrateLow = 1,
    WXCastSenderVideoBitrateMedium = 2,
    WXCastSenderVideoBitrateHigh = 3, // 默认
    WXCastSenderVideoBitrateUltra = 4
};

typedef NS_ENUM(int, WXCastSenderVideoQuality) {
    WXCastSenderVideoQualityNone = -1,              // 不使用精细配置，内部根据接收端参数配置
    WXCastSenderVideoQualityStandard = 0,           // 标清
    WXCastSenderVideoQualityHD = 1,                 // 高清
    WXCastSenderVideoQualityOrigin = 2,              // 原画
};

@interface WXCastSenderVideoOptions : NSObject

+ (instancetype)defaultOptions;

/// 帧率
@property (nonatomic, assign) WXCastSenderVideoResolution resolution;

/// 分辨率
@property (nonatomic, assign) WXCastSenderVideoFps fps;

/// 码率。越高，则画面越清晰，但占用的数据量更大，会收到网络情况和内存影响
@property (nonatomic, assign) WXCastSenderVideoBitrate bitrate;



/// 视频质量，默认为 none，配置后内部根据接收端参数进行调整
@property (nonatomic, assign) WXCastSenderVideoQuality quality;


// Private -

- (CGSize)videoSize;

- (CGSize)pickMinSizeBetween:(CGSize)targetSize;

- (CGSize)aspectRatioVideoSize:(CGSize)bufferSize targetSize:(CGSize)targetSize;

- (int)caculateVideoBitrate;

+ (void)sampleBufferFromPixelBuffer:(CMSampleBufferRef)inputSampleBuffer  withCGImage:(CGImageRef)imageRef;

+ (CMSampleBufferRef)adjustTime:(CMSampleBufferRef)sample by:(CMTime)offset;

@end

NS_ASSUME_NONNULL_END
