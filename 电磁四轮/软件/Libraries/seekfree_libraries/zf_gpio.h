/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		gpio
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/


#ifndef __ZF_GPIO_H
#define __ZF_GPIO_H

#include "common.h"


typedef enum
{
	NOPULL = 0,
    PULLUP = 1,
}PULL_enum;


typedef enum
{
	P0_0 = 0x00, P0_1, P0_2, P0_3, P0_4, P0_5, P0_6, P0_7, 
	P1_0 = 0x10, P1_1, P1_2, P1_3, P1_4, P1_5, P1_6, P1_7, 
	P2_0 = 0x20, P2_1, P2_2, P2_3, P2_4, P2_5, P2_6, P2_7, 
	P3_0 = 0x30, P3_1, P3_2, P3_3, P3_4, P3_5, P3_6, P3_7, 
	P4_0 = 0x40, P4_1, P4_2, P4_3, P4_4, P4_5, P4_6, P4_7, 
	P5_0 = 0x50, P5_1, P5_2, P5_3, P5_4, P5_5, P5_6, P5_7,
	P6_0 = 0x60, P6_1, P6_2, P6_3, P6_4, P6_5, P6_6, P6_7,
	P7_0 = 0x70, P7_1, P7_2, P7_3, P7_4, P7_5, P7_6, P7_7,
	
}PIN_enum;

typedef enum
{
	//pnm1 pnm0
	GPIO = 0,			//准双向口(弱上拉)
	GPO_PP = 1,			//推挽输出
	GPI_IMPEDANCE = 2,	//高阻输入
	GPI_OD = 3,			//开漏输出
}GPIOMODE_enum;






void  gpio_pull_set(PIN_enum pin, PULL_enum pull);
void  gpio_mode(PIN_enum pin, GPIOMODE_enum mode);







#endif
