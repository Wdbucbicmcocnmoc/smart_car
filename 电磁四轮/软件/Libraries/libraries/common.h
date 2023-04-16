/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		common
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#ifndef __COMMON_H_
#define __COMMON_H_
#include "STC16Fxx.h"

//数据类型声明
typedef unsigned char   uint8  ;	//  8 bits 
typedef unsigned int  	uint16 ;	// 16 bits 
typedef unsigned long  	uint32 ;	// 32 bits 
								
								
typedef signed char     int8   ;	//  8 bits 
typedef signed int      int16  ;	// 16 bits 
typedef signed long     int32  ;	// 32 bits 
								
								
typedef volatile int8   vint8  ;	//  8 bits 
typedef volatile int16  vint16 ;	// 16 bits 
typedef volatile int32  vint32 ;	// 32 bits 
								
								
typedef volatile uint8  vuint8 ;	//  8 bits 
typedef volatile uint16 vuint16;	// 16 bits 
typedef volatile uint32 vuint32;	// 32 bits 



typedef enum //无线模块
{
    NO_WIRELESS_MODE = 0,   //没有无线模块
    WIRELESS_SI24R1 = 1,    //无线转串口
    WIRELESS_CH9141 = 2,    //蓝牙转串口
    WIRELESS_CH573 = 3,     //无线CH573模块
}WIRELESS_TYPE_enum;

extern WIRELESS_TYPE_enum wireless_type;




#endif
