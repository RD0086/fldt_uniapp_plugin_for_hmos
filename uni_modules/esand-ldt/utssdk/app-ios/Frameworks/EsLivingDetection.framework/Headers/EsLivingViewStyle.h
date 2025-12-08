//
//  NSObject+EsLivingViewStyle.h
//  EsLivingDetection
//
//  Created by 张泽龙 on 2021/11/24.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * 活体检测界面配置类
 */
@interface EsLivingViewStyle :NSObject

/**
 * 获取默认初始化样式实例
 */
- (instancetype)initWithStyleType:(int)styleType;

/**
 * 设置页面背景颜色
 * @param color 如 #FFFFFF
 */
-(instancetype)setBackGroundColor:(NSString *) color;

/**
 * 设置进度条前渐变色
 * @param color 如 #FFFFFF
 */
-(instancetype)setProgressStaGradient:(NSString *) color;

/**
 * 设置进度条后渐变色
 * @param color 如 #FFFFFF
 */
-(instancetype)setProgressEndGradient:(NSString *) color;

/**
 * 设置进度条背景颜色
 * @param color 如 #FFFFFF
 */
-(instancetype)setProgressBgColor:(NSString *) color;

/**
 * 设置进度条边框颜色
 * @param color 如 #FFFFFF
 */
-(instancetype)setProgressBorderColor:(NSString *) color;

/**
 * 设置文本颜色
 * @param color 如 #FFFFFF
 */
-(instancetype)setTextColor:(NSString *) color;

/**
 * 设置进度条的宽度
 * @param width 如 5
 */
-(instancetype)setProgressWidth:(float) width;

/**
 * 设置退出按钮的颜色
 * @param color 如 #FFFFFF
 */
-(instancetype)setExitBtnColor:(NSString *) color;

/**
 * 设置未激活的活体检测标签颜色
 * @param color 如 #FFFFFF
 */
-(instancetype)setLdtLabelNormalColor:(NSString *) color;

/**
 * 设置运行中的活体检测标签颜色
 * @param color 如 #FFFFFF
 */
-(instancetype)setLdtLabelProcessColor:(NSString *) color;

/**
 * 设置活体检测完成时的标签颜色
 * @param color 如 #FFFFFF
 */
-(instancetype)setLdtLabelCompleteColor:(NSString *) color;

/**
 * 获取页面背景颜色
 */
-(UIColor *)getBackGroundColor;

/**
 * 获取进度条前渐变色
 */
-(UIColor *)getProgressStaGradient;

/**
 * 获取进度条后渐变色
 */
-(UIColor *)getProgressEndGradient;

/**
 * 获取进度条背景色
 */
-(UIColor *)getProgressBgColor;

/**
 * 获取进度条边框颜色
 */
-(UIColor *)getProgressBorderColor;

/**
 * 获取文本颜色
 */
-(UIColor *)getTextColor;

/**
 * 获取进度条宽度
 */
-(float)getProgressWidth;

/**
 * 获取退出按钮的颜色
 */
-(UIColor *)getExitLabelColor;

/**
 * 获取活体检测类型文字激活时的颜色
 */
-(UIColor *)getLdtLabelNormalColor;

/**
 * 获取活体检测类型文件没有激活时的颜色
 */
-(UIColor *)getLdtLabelProcessColor;

/**
 * 获取活体检测类型文件没有激活时的颜色
 */
-(UIColor *)getLdtLabelCompleteColor;

@end

NS_ASSUME_NONNULL_END
