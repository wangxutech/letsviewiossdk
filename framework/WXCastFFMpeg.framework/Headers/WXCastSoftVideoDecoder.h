//
//  WXCastSoftVideoDecoder.h
//  WXCastFFMpeg
//
//  Created by fbs on 2023/5/10.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol WXCastSoftVideoDecoderDelegate <NSObject>

- (void)wxCastSoftVideoOutput:(CMSampleBufferRef)buffer;

- (void)wxCastSoftVideoSizeChange:(CGSize)size;

@end

@interface WXCastSoftVideoDecoder : NSObject

@property (nonatomic, weak) id<WXCastSoftVideoDecoderDelegate> delegate;

/// 视频编码的帧率（fps）
/// 默认值为 20。用户可以自行设置帧率，建议不要超过 30 帧。
/// 帧率越大，画面越流畅
@property (nonatomic, assign) int videoFps;

/// 视频码率，均值，单位是（Mbps）
/// 码率越高，则画面越清晰，但占用的数据量更大，不利于传输
@property (nonatomic, assign) int videoBitrate;

- (void)decodeData:(NSData *)data;

- (void)close;

@end

NS_ASSUME_NONNULL_END
