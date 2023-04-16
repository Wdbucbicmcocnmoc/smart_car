/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		ctime
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#ifndef __ZF_TIM_H
#define __ZF_TIM_H
#include "common.h"



//此枚举定义不允许用户修改
typedef enum    // 枚举ADC通道
{
    CTIM0_P34=0,    
	CTIM1_P35,    	
	CTIM2_P12,     	
	CTIM3_P04,
	CTIM4_P06,
}CTIMN_enum;


//此枚举定义不允许用户修改
typedef enum    // 枚举ADC通道
{
    TIM_0,    
	TIM_1,    	
	TIM_2,     	
	TIM_3,
	TIM_4,
}TIMN_enum;


#define TIM2_CLEAR_FLAG		AUXINTIF &= ~0x01; 
#define TIM3_CLEAR_FLAG		AUXINTIF &= ~0x02; // 清中断标志
#define TIM4_CLEAR_FLAG		AUXINTIF &= ~0x04; // 清中断标志


void   ctimer_count_init(CTIMN_enum tim_n);
void   ctimer_count_clean(CTIMN_enum tim_n);
uint16 ctimer_count_read(CTIMN_enum tim_n);

void pit_timer_ms(TIMN_enum tim_n,uint16 time_ms);



#endif
