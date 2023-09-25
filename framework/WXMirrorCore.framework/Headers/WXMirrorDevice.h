//
//  WXMirrorDevice.h
//  WXMirrorCore
//
//  Created by Mosca on 2022/7/5.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface WXMirrorDevice : NSObject <NSCoding, NSSecureCoding>

/// 设备名称
@property (nonatomic, copy) NSString *name;

/// 设备标识符
@property (nonatomic, copy) NSString *uuid;

/// 设备类型 pc： 0  mac ：1  ios ： 2  Android : 3    TV : 4
@property (nonatomic, assign) int type;

/// 设备型号
@property (nonatomic, copy) NSString *model;

/// 设备 IP
@property (nonatomic, copy) NSString *host;

/// 设备端口号
@property (nonatomic, assign) NSInteger port;

/// 投屏端口号
@property (nonatomic, assign) NSInteger mirrorPort;

/// 软件版本号
@property (nonatomic, assign) NSInteger version;

@property (nonatomic, assign) int width;
@property (nonatomic, assign) int height;




@property (nonatomic, copy) NSString *serverDate;

@property (nonatomic, copy) NSString *mark;

@property (nonatomic, assign) NSInteger features;

@end

NS_ASSUME_NONNULL_END
