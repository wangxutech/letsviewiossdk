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

#import "WXDLNASender.h"
#import "WXDLNASenderDevice.h"
#import "WXDLNASenderRenderer.h"
#import "WXDLNASenderServer.h"
#import "WXDLNASenderObjects.h"

FOUNDATION_EXPORT double WXDLNASenderVersionNumber;
FOUNDATION_EXPORT const unsigned char WXDLNASenderVersionString[];

