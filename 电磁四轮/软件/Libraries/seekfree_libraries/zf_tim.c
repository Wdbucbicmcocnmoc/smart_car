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


#include "zf_tim.h"
#include "board.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      定时器初始化作为外部计数
//  @param      tim_n           选择模块
//  @return     void
//  @since      v1.0
//  Sample usage:               ctimer_count_init(CTIM0_P34);		//初始化定时器0，外部输入为P3.4引脚
//  @note                       串口1使用定时器1作为波特率发生器，
//								串口2使用定时器2作为波特率发生器，
//								串口3使用定时器3作为波特率发生器，
//								串口4使用定时器4作为波特率发生器，
//                              STC16F仅有定时器0-定时器4，这5个定时器。
//								编码器采集数据也需要定时器作为外部计数。
//-------------------------------------------------------------------------------------------------------------------
void ctimer_count_init(CTIMN_enum tim_n)
{

	switch(tim_n)
	{
		case CTIM0_P34:
		{
			TL0 = 0; 
			TH0 = 0; 
			TMOD |= 0x04; //外部计数模式
			TR0 = 1; //启动定时器
			break;
		}
		
		case CTIM1_P35:
		{
			TL1 = 0x00;
			TH1 = 0x00;
			TMOD |= 0x40; // 外部计数模式
			TR1 = 1; // 启动定时器
			break;
		}
		
		case CTIM2_P12:
		{
			T2L = 0x00;
			T2H = 0x00;
			AUXR |= 0x18; // 设置外部计数模式并启动定时器
			break;
		}
		
		case CTIM3_P04:
		{
			T3L = 0; 
			T3H = 0;
			T4T3M |= 0x0c; // 设置外部计数模式并启动定时器
			break;
		}
		
		case CTIM4_P06:
		{
			T4L = 0;
			T4H = 0;
			T4T3M |= 0xc0; // 设置外部计数模式并启动定时器
			break;
		}
	
	}	
} 

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取计数数值
//  @param      countch     计数通道号及引脚
//  @return     uint32      返回计数值
//  Sample usage:           num = ctimer_count_read(CTIM0_P34);     
//-------------------------------------------------------------------------------------------------------------------
uint16 ctimer_count_read(CTIMN_enum tim_n)
{
	uint16 dat = 0;
	
	switch(tim_n)
	{
		case CTIM0_P34:
		{
			dat = (uint16)TH0 << 8;
			dat = ((uint8)TL0) | dat;
			break;
		}
		case CTIM1_P35:
		{
			dat = (uint16)TH1 << 8;
			dat = ((uint8)TL1) | dat;
			break;
		}
		case CTIM2_P12:
		{
			dat = (uint16)T2H << 8;
			dat = ((uint8)T2L) | dat;
			break;
		}
		case CTIM3_P04:
		{
			dat = (uint16)T3H << 8;
			dat = ((uint8)T3L) | dat;	
			break;
		}
		case CTIM4_P06:
		{
			dat = (uint16)T4H << 8;
			dat = ((uint8)T4L) | dat;
			break;
		}
		
	}
	return dat;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      清除计数数值
//  @param      countch     计数通道号及引脚
//  @return     void      
//  Sample usage:           ctimer_count_clean(CTIM0_P34);     
//-------------------------------------------------------------------------------------------------------------------
void ctimer_count_clean(CTIMN_enum tim_n)
{	
	switch(tim_n)
	{
		case CTIM0_P34:
		{
			TR0 = 0;
			TH0 = 0;
			TL0 = 0;
			TR0 = 1;
			break;
		}
		case CTIM1_P35:
		{
			TR1 = 0;
			TH1 = 0;
			TL1 = 0;
			TR1 = 1;
			break;
		}
		case CTIM2_P12:
		{
			AUXR &= ~(1<<4);
			T2H = 0;
			T2L = 0;
			AUXR |= 1<<4;
			break;
		}
		case CTIM3_P04:
		{
			T4T3M &= ~(1<<3);
			T3H = 0;
			T3L = 0;
			T4T3M |= (1<<3);
			break;
		}
		case CTIM4_P06:
		{
			T4T3M &= ~(1<<7);
			T4H = 0;
			T4L = 0;
			T4T3M |= (1<<7);
			break;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      定时器周期中断
//  @param      tim_n      定时器通道号
//  @param      time_ms    时间(ms)
//  @return     void      
//  Sample usage:          pit_timer_ms(TIM_0, 10)
//						   使用定时器0做周期中断，时间10ms一次。
//-------------------------------------------------------------------------------------------------------------------
void pit_timer_ms(TIMN_enum tim_n,uint16 time_ms)
{
	uint16 temp;
	temp = (uint16)65536 - (uint16)(sys_clk / (12 * (1000 / time_ms)));
	
	if(TIM_0 == tim_n)
	{
		TMOD |= 0x00; 	// 模式 0
		TL0 = temp; 	
		TH0 = temp >> 8;
		TR0 = 1; 		// 启动定时器
		ET0 = 1; 		// 使能定时器中断
	}
	else if(TIM_1 == tim_n)
	{
		TMOD |= 0x00; // 模式 0
		TL1 = temp; 	
		TH1 = temp >> 8;
		TR1 = 1; // 启动定时器
		ET1 = 1; // 使能定时器中断
	}
	else if(TIM_2 == tim_n)
	{
		T2L = temp; 	
		T2H = temp >> 8;
		AUXR |= 0x10; // 启动定时器
		IE2 |= 0x04; // 使能定时器中断
	}
	else if(TIM_3 == tim_n)
	{
		T3L = temp; 	
		T3H = temp >> 8;
		T4T3M |= 0x08; // 启动定时器
		IE2 |= 0x20; // 使能定时器中断
	}
	else if(TIM_4 == tim_n)
	{
		T4L = temp; 	
		T4H = temp >> 8;
		T4T3M |= 0x80; // 启动定时器
		IE2 |= 0x40; // 使能定时器中断
	}
}

