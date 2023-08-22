//
//  WXCastSoftVideoEncoder.h
//  WXCastFFMpeg
//
//  Created by fbs on 2023/5/25.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol WXCastSoftVideoEncoderDelegate;

@interface WXCastSoftVideoEncoder : NSObject

/// 编码后的画面宽度
@property (nonatomic, assign) int videoWidth;
/// 编码后的画面高度
@property (nonatomic, assign) int videoHeight;

/// 视频编码的帧率（fps）
/// 默认值为 20。用户可以自行设置帧率，建议不要超过 30 帧。
/// 帧率越大，画面越流畅
@property (nonatomic, assign) int videoFps;

/// 视频码率，均值，单位是（Mbps）
/// 码率越高，则画面越清晰，但占用的数据量更大，不利于传输
@property (nonatomic, assign) int videoBitrate;

@property (nonatomic, assign) int rotation;

@property (nonatomic, weak) id<WXCastSoftVideoEncoderDelegate> delegate;

- (void)startRunning;

- (void)encodeSampleBuffer:(CMSampleBufferRef)sampleBuffer;

- (void)reload;

- (void)stopRunning;

@end

@protocol WXCastSoftVideoEncoderDelegate <NSObject>

- (void)wxCastSoftVideo:(WXCastSoftVideoEncoder *)encoder outputData:(NSData *)data;

- (void)wxCastSoftVideoOnVideoInfo:(WXCastSoftVideoEncoder *)encoder;

- (void)wxCastSoftVideo:(WXCastSoftVideoEncoder *)encoder onError:(NSError *)error;

@end
NS_ASSUME_NONNULL_END
