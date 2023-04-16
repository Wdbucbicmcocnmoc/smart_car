/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2016,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		SEEKFREE_TSL1401.c
 * @brief      		红孩儿(线阵CCD)函数库
 * @company	   		成都逐飞科技有限公司
 * @author     		Go For It(1325536866)
 * @version    		v1.0
 * @Software 		IAR 7.2 or MDK 5.17
 * @Target core		MK60DN512VLL10
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2016-02-25
 * @note	
					TSL1401接线定义：
					------------------------------------ 
					    模块管脚       	单片机管脚
					    CCD_AO	   		查看SEEKFREE_TSL1401.h文件中的AD_CHANNEL 宏定义
					    CCD_CLK	   		查看SEEKFREE_TSL1401.h文件中的CCD_CLK_PIN宏定义
					    CCD_SI	   		查看SEEKFREE_TSL1401.h文件中的CCD_SI_PIN 宏定义
					------------------------------------ 
 ********************************************************************************************************************/

#ifndef _TSL1401_c
#define _TSL1401_c

#include "common.h"
#include "zf_uart.h"
#include "board.h"



#define CCD_CLK_PIN   	P33               	//CCD CLK引脚定义
#define CCD_SI_PIN    	P32               	//CCD SI 引脚定义
#define AD_CHANNEL 		ADC_P14             //定义AD采集通道 ADC_P05
//#define AD_CHANNEL_CH2  ADC_P13             //定义AD采集通道2 ADC_P13
#define EXPOSURE_TIME  	10                  //定义CCD曝光时间 单位MS
#define PIT_TIMER_CH	TIM_4				//使用周期中断定时器4
#define AD_RESOLUTION	ADC_12BIT			//AD转换12位
	


#define CCD_CLK(x)      CCD_CLK_PIN = x 
#define CCD_SI(x)       CCD_SI_PIN  = x


extern uint16 ccd_data[128];                   //CCD数据
//extern uint16 ccd_data_ch2[128];                   //CCD数据通道2

extern uint8 tsl1401_finish_flag;

void ccd_init(void);
void ccd_collect(void);
void ccd_send_data(UARTN_enum uart_n ,uint16 *dat);

#endif