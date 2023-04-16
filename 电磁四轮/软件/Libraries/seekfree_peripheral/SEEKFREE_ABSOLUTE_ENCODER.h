/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		绝对式编码器
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看LPC546XX_config.h文件内版本宏定义
 * @Software 		MDK FOR C251 V5.60a
 * @Target core		LPC54606J512BD100
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-01-13
 * @note		
					接线定义：
					------------------------------------ 
					模块管脚            单片机管脚
					SCK    			    查看SEEKFREE_ABSOLUTE_ENCODER.H文件ABS_ENCODER_SPI_SCK_PIN 宏定义
					MISO         	    查看SEEKFREE_ABSOLUTE_ENCODER.H文件ABS_ENCODER_SPI_MISO_PIN宏定义
					MOSI                查看SEEKFREE_ABSOLUTE_ENCODER.H文件ABS_ENCODER_SPI_MOSI_PIN宏定义
					CS                  查看SEEKFREE_ABSOLUTE_ENCODER.H文件ABS_ENCODER_SPI_PCS_PIN  宏定义
					------------------------------------  
 ********************************************************************************************************************/

#ifndef _SEEKFREE_ABSOLUTE_ENCODER_H
#define _SEEKFREE_ABSOLUTE_ENCODER_H


#include "common.h"

//------------------------软件SPI--------------------------//
#define ABS_ENCODER_SCK_PIN   P27   //接模块 SCLK
#define ABS_ENCODER_MISO_PIN  P26  	//接模块 MISO
#define ABS_ENCODER_MOSI_PIN  P25   //接模块 MOSI
#define ABS_ENCODER_CSN_PIN   P24   //接模块 CS
     
#define ABS_ENCODER_SCK(x)  ABS_ENCODER_SCK_PIN  = x
#define ABS_ENCODER_MISO    ABS_ENCODER_MISO_PIN
#define ABS_ENCODER_MOSI(x) ABS_ENCODER_MOSI_PIN = x
#define ABS_ENCODER_CSN(x)  ABS_ENCODER_CSN_PIN  = x



//------------------------硬件SPI--------------------------//
#define ABS_ENCODER_SPI_NUM	SPI_CH3

#define ABS_ENCODER_SPI_SCK_PIN   	SPI_CH3_SCLK_P43   	//接模块 SCLK
#define ABS_ENCODER_SPI_MISO_PIN  	SPI_CH3_SCLK_P43  		//接模块 MISO
#define ABS_ENCODER_SPI_MOSI_PIN  	SPI_CH3_SCLK_P43   	//接模块 MOSI
#define ABS_ENCODER_SPI_CS_PIN   	P22    				//接模块 CS

#define ABS_ENCODER_SPI_CSN(x)  	ABS_ENCODER_SPI_CS_PIN = x


//角度传感器参数
#define ABS_ENCODER_SPI_W       0x80
#define ABS_ENCODER_SPI_R       0x40


#define ZERO_L_REG              0x00
#define ZERO_H_REG              0x01
#define DIR_REG                 0X09


void   encoder_init_simspi(void);
uint16 encoder_angle_simspi(void);

void   encoder_init_spi(void);
uint16 encoder_angle_spi(void);


#endif

