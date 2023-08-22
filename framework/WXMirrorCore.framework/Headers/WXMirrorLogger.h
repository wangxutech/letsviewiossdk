//
//  WXMirrorLogger.h
//  WXMirrorCore
//
//  Created by fanbaoshen on 2021/11/19.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, WXMirrorLogLevel) {
    WXMirrorLogLevelSilent = 0,
    WXMirrorLogLevelError  = 1,
    WXMirrorLogLevelInfo   = 2,
    WXMirrorLogLevelDebug  = 3
};

NS_ASSUME_NONNULL_BEGIN

@interface WXMirrorLogger : NSObject

/// 设置要记录的log级别
/// @param level 要设置的log级别
/// 设置 WXMirrorLogLevelSilent 不会打印和生成新的日志文件
+ (void)initLogger:(WXMirrorLogLevel)level;

/// 获取日志文件夹路径
+ (NSString *_Nullable)getLogFolderPath;


/// 上报日志文件
/// @param email 联系邮件
/// @param message 描述内容
//+ (void)uploadLogs:(NSString *)email message:(NSString *)message response:(void(^_Nullable)(BOOL result, NSString *msg))resultBlock;



/****************    Private    ****************/


/// 打印日志，不受 level 影响
+ (void)log:(NSString *)format, ... NS_FORMAT_FUNCTION(1, 2);

/// 打印日志
/// @param level 日志级别
/// @param format   日志内容 总日志大小限制为：字符串长度30k，条数200
+ (void)level:(WXMirrorLogLevel)level log:(NSString *)format, ... NS_FORMAT_FUNCTION(2, 3);

/// 打印日志
/// @param level  日志级别
/// @param tag    日志模块分类
/// @param format 日志内容 总日志大小限制为：字符串长度30k，条数200
+ (void)level:(WXMirrorLogLevel)level tag:(NSString *)tag log:(NSString *)format, ... NS_FORMAT_FUNCTION(3, 4);

@end

NS_ASSUME_NONNULL_END
