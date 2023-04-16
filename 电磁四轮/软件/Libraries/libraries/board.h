/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		board
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/



#ifndef __BOARD_H
#define __BOARD_H
#include "common.h"


//不再使用代码调节频率。
//#define FOSC					30000000	//内核频率设置为30Mhz

#define EXTERNAL_CRYSTA_ENABLE 	0			//使用外部晶振，0为不使用，1为使用（建议使用内部晶振）
#define PRINTF_ENABLE			1			//printf使能，0为失能，1为使能
#define ENABLE_IAP 				1			//使能软件一键下载功能，0为失能，1为使能

#define DEBUG_UART 			  	UART_1
#define DEBUG_UART_BAUD 	  	115200
#define DEBUG_UART_RX_PIN  		UART1_RX_P30
#define DEBUG_UART_TX_PIN  		UART1_TX_P31
#define DEBUG_UART_TIM			TIM_2

#if (1==PRINTF_ENABLE)
	char putchar(char c);
#endif

#define SET_P54_RESRT 	  (RSTCFG |= 1<<4)	//设置P54为复位引脚

extern int32 sys_clk;

void board_init(void);
void DisableGlobalIRQ(void);
void EnableGlobalIRQ(void);

#endif

