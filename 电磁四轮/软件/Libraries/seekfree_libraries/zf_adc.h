/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		adc
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#ifndef __ZF_ADC_H
#define __ZF_ADC_H

#include "common.h"

//此枚举定义不允许用户修改
typedef enum
{
    ADC_P10 = 0     , 
    ADC_P11         , 
    ADC_P12         ,	//STC16F没有这个引脚，仅做站位使用
	ADC_P13         , 
    ADC_P14         , 
	ADC_P15         , 
	ADC_P16         , 
	ADC_P17         , 
	
	ADC_P00         , 
	ADC_P01         , 
	ADC_P02        	, 
	ADC_P03        	, 
	ADC_P04        	, 
	ADC_P05        	, 
	ADC_P06        	, 
	ADC_POWR = 0x0f	, //内部AD 1.19V
} ADCN_enum;

//此枚举定义不允许用户修改
typedef enum
{
	ADC_SYSclk_DIV_2 = 0,
	ADC_SYSclk_DIV_4,
	ADC_SYSclk_DIV_6,
	ADC_SYSclk_DIV_8,
	ADC_SYSclk_DIV_10,
	ADC_SYSclk_DIV_12,
	ADC_SYSclk_DIV_14,
	ADC_SYSclk_DIV_16,
	ADC_SYSclk_DIV_18,
	ADC_SYSclk_DIV_20,
	ADC_SYSclk_DIV_22,
	ADC_SYSclk_DIV_24,
	ADC_SYSclk_DIV_26,
	ADC_SYSclk_DIV_28,
	ADC_SYSclk_DIV_30,
	ADC_SYSclk_DIV_32,
} ADC_SPEED_enum;


//此枚举定义不允许用户修改
typedef enum    // 枚举ADC通道
{

    ADC_12BIT=0,    //12位分辨率
	ADC_11BIT,		//11位分辨率
	ADC_10BIT,		//10位分辨率
	ADC_9BIT,    	//9位分辨率
	ADC_8BIT,     	//8位分辨率

}ADCRES_enum;

void adc_init(ADCN_enum adcn,ADC_SPEED_enum speed);
uint16 adc_once(ADCN_enum adcn,ADCRES_enum resolution);
//uint16 adc_mean_filter(ADCN_enum adcn, uint8 count);


#endif