//
//  EsLivingDetectionManager.h
//  EsLivingDetection
//
//  Created by ReidLee on 2020/12/23.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "EsLivingDetectResult.h"
#import "EsLivingConfig.h"
#import "EsLivingViewStyle.h"
#import "EsLivingConfig.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 活体检测管理类
 */
@interface EsLivingDetectionManager : NSObject

/**
 * 初始化引擎，此方法建议提前调用，比较耗时
 * 如果没有提前调用将在调用 verifyInit 接口 自动调用InitEngine 接口
 */
+ (void) InitEngine;

/**
 * 认证初始化
 * @param livingType 认证类型
 * @return 初始化结果
 */
+ (EsLivingDetectResult*) verifyInit:(int) livingType;

/**
 * 开始执行活体检测
 * @param token 认证token
 * @param viewController 父容器
 * @param callback 认证结果回调代码块
 */
+ (void) startDetect: (NSString*) token viewController:(UIViewController*)viewController callback:(EsLivingDetectCallback) callback;

/**
 * 开始执行活体检测
 * @param token 认证token
 * @param viewController 父容器
 * @param callback 认证结果回调代码块
 * @param type 1: 使用nav 方式进行页面跳转 2:使用modal跳转
 */
+ (void) startDetect2: (NSString*) token viewController:(UIViewController*)viewController callback:(EsLivingDetectCallback) callback windowSwitchType:(NSInteger)type;

/**
 * 获取活体界面样式实例
 * @return EsLivingViewStyle 活体检测界面样式实例
 */
+(EsLivingViewStyle *)LivingViewStyleInstance;

/**
 * 获取活体配置实例
 * @return EsLivingConfig 活体检测配置实例
 */
+(EsLivingConfig *)LivingConfigInstance;

/**
 * 通过获取活体检测录制的视频数据
 * @param token 活体检测对应的token
 * @return .mov 格式的视频数据
 */
+(NSData *)GetLdtVideo:(NSString *)token;

/**
 * 获取指定token 对应视频的文件路径
 * @param token 活体检测对应的token
 * @return 文件的路径
 */
+(NSString *)GetLdtVideoFilePath:(NSString *)token;

/**
 * 获取活体检测的视频存放根路径
 * @return 文件的路径
 */
+(NSString *)GetLdtVideoRootDirectory;

/**
 * 获取当前SDK版本号
 * @return 版本号
 */
+(NSString *)getSdkVersion;

/**
 * 开启ocr 人脸认证
 * @param viewController 当前viewController
 * @param type ocr类型 1: 使用
 */
+ (void) startOcrFaceAuth : (UIViewController*)viewController token:(NSString *)token callback:(EsLivingDetectCallback) callback;

@end

NS_ASSUME_NONNULL_END
