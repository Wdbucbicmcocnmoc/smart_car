/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		pwm
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#ifndef __ZF_PWM_H
#define __ZF_PWM_H
#include "common.h"


#define PWM_DUTY_MAX 10000



typedef enum
{
	//PWMA和PWMB是两组不同的PWM
	
	//以下是PWMA通道。
	//同一组PWM，同一时刻，只能有同一个PWM输出。
	//例如:PWMA_CH1P_P10 和 PWMA_CH1N_P11不能一起输出。
	PWMA_CH1P_P10 = 0x00,PWMA_CH1N_P11,
	PWMA_CH1P_P20,		 PWMA_CH1N_P21,
	PWMA_CH1P_P60,		 PWMA_CH1N_P61,

	PWMA_CH2P_P12 = 0x10,//该引脚已做 USB 内核电源稳压脚
	PWMA_CH2N_P13,          
	PWMA_CH2P_P22,		 PWMA_CH2N_P23,
	PWMA_CH2P_P62,		 PWMA_CH2N_P63,

	PWMA_CH3P_P14 = 0x20,PWMA_CH3N_P15,
	PWMA_CH3P_P24,		 PWMA_CH3N_P25,
	PWMA_CH3P_P64,		 PWMA_CH3N_P65,

	PWMA_CH4P_P16 = 0x30,PWMA_CH4N_P17,
	PWMA_CH4P_P26,		 PWMA_CH4N_P27,
	PWMA_CH4P_P66,		 PWMA_CH4N_P67,
	PWMA_CH4P_P34,		 PWMA_CH4N_P33,
	
	//以下是PWMB通道。
	//同一组PWM，同一时刻，只能有同一个PWM输出。
	//例如:PWMB_CH1_P20 和 PWMB_CH1_P17 不能同时输出 
	//但是不同的通道可以同一时刻输出。
	//例如:PWMB_CH1_P20 和 PWMB_CH2_P21可以同时输出
	PWMB_CH1_P20 = 0x40,
	PWMB_CH1_P17,
	PWMB_CH1_P00,
	PWMB_CH1_P74,

	PWMB_CH2_P21 = 0x50,
	PWMB_CH2_P54,		//该引脚为复位引脚
	PWMB_CH2_P01,
	PWMB_CH2_P75,

	PWMB_CH3_P22 = 0x60,
	PWMB_CH3_P33,
	PWMB_CH3_P02,
	PWMB_CH3_P76,

	PWMB_CH4_P23 = 0x70,
	PWMB_CH4_P34,
	PWMB_CH4_P03,
	PWMB_CH4_P77,

}PWMCH_enum;


void pwm_init(PWMCH_enum pwmch,uint32 freq, uint32 duty);
void pwm_duty(PWMCH_enum pwmch, uint32 duty);
void pwm_freq(PWMCH_enum pwmch, uint32 freq, uint32 duty);


#endif
