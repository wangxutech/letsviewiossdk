/*
 *******************       UPnP设备       ******************
 
 功能描述
 - 描述设备信息
 - 记录设备服务
 
 */

#import <Foundation/Foundation.h>
@class WXDLNASenderService;

NS_ASSUME_NONNULL_BEGIN

@interface WXDLNASenderDevice : NSObject

/// 唯一设备名称
@property (nonatomic, copy) NSString *uuid;

/// 对于用户的简短描述
@property (nonatomic, copy) NSString *friendlyName;

/// 型号名称
@property (nonatomic, copy) NSString *modelName;

/// 设备类型
@property (nonatomic, copy) NSString *deviceType;

/// 设备 IP 地址
@property (nonatomic, copy) NSString *host;

/// 投屏端口
@property (nonatomic, strong) NSNumber *port;

@property (nonatomic, copy) NSString *scheme;

/// 服务
@property (nonatomic, strong) WXDLNASenderService *AVTransport;
@property (nonatomic, strong) WXDLNASenderService *RenderingControl;

@property (nonatomic, copy) NSString *usn;

@property (nonatomic, assign) BOOL connectCheck;

@end

NS_ASSUME_NONNULL_END
