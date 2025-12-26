//
//  EsLivingDetection.h
//  EsLivingDetection
//
//  Created by ReidLee on 2020/12/23.
//

#import <Foundation/Foundation.h>
#import "EsLivingDetectionManager.h"

//! Project version number for EsLivingDetection.
FOUNDATION_EXPORT double EsLivingDetectionVersionNumber;

//! Project version string for EsLivingDetection.
FOUNDATION_EXPORT const unsigned char EsLivingDetectionVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <EsLivingDetection/PublicHeader.h>

// 静默活体功能控制宏，默认不支持
// 如需启用静默活体功能，请在编译时定义 ENABLE_SILENT_LIVENESS=1
#ifndef ENABLE_SILENT_LIVENESS
#define ENABLE_SILENT_LIVENESS 0
#endif

// OCR功能控制宏，默认不编译
// 如需启用OCR功能，请在编译时定义 ENABLE_OCR=1
#ifndef ENABLE_OCR
#define ENABLE_OCR 0
#endif
