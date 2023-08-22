#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "WXMirrorCore.h"
#import "WXMirrorLogger.h"
#import "WXMirrorDevice.h"
#import "WXCastDeviceTool.h"

FOUNDATION_EXPORT double WXMirrorCoreVersionNumber;
FOUNDATION_EXPORT const unsigned char WXMirrorCoreVersionString[];

