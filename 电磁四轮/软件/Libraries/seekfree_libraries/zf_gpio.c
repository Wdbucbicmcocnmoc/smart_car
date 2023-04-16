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


#include "zf_gpio.h"


#define PxPU_BASE_ADDR  0x7EFE10 

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO设置引脚上拉电阻设置
//  @param      pin         选择引脚（P0_0-P7_7）
//  @param      pull        设置上下拉电阻 NOPULL:不设置 PULLUP:上拉
//  @return     void
//  Sample usage:           gpio_pull_set(P0_0,NOPULL);       // 设置P0.0引脚没有上下拉电阻
//-------------------------------------------------------------------------------------------------------------------
void gpio_pull_set(PIN_enum pin, PULL_enum pull)
{
	if(PULLUP == pull)
	{
		(*(unsigned char volatile far *)(PxPU_BASE_ADDR + (pin >> 4))) |= (1<<(pin&0x0F));
	}
	else if(NOPULL == pull)
	{
		(*(unsigned char volatile far *)(PxPU_BASE_ADDR + (pin >> 4))) &= ~(1<<(pin&0x0F));
	}
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO设置引脚模式
//  @param      pin         选择引脚（P0_0-P5_4）
//  @param      mode        引脚模式 GPIO:准双向口, GPO_PP:推挽输出, GPI_IMPEDANCE:高阻输入, GPI_OD:开漏输出
//  @return     void
//  Sample usage:           gpio_mode(P0_0,GPIO);       // 设置P0.0设置为双向IO
//-------------------------------------------------------------------------------------------------------------------
void gpio_mode(PIN_enum pin, GPIOMODE_enum mode)
{
	if(GPIO == mode)
	{
		if(0x00 == (pin&0xF0))	//P0
		{
			P0M1 &= ~(1<<(pin&0xF));
			P0M0 &= ~(1<<(pin&0xF));
		}
		if(0x10 == (pin&0xF0))	//P1
		{
			P1M1 &= ~(1<<(pin&0xF));
			P1M0 &= ~(1<<(pin&0xF));
		}
		if(0x20 == (pin&0xF0))	//P2
		{
			P2M1 &= ~(1<<(pin&0xF));
			P2M0 &= ~(1<<(pin&0xF));
		}
		
		if(0x30 == (pin&0xF0))	//P3
		{
			P3M1 &= ~(1<<(pin&0xF));
			P3M0 &= ~(1<<(pin&0xF));
		}
		if(0x40 == (pin&0xF0))	//P4
		{
			P4M1 &= ~(1<<(pin&0xF));
			P4M0 &= ~(1<<(pin&0xF));
		}
		if(0x50 == (pin&0xF0))	//P5
		{
			P5M1 &= ~(1<<(pin&0xF));
			P5M0 &= ~(1<<(pin&0xF));
		}
		if(0x60 == (pin&0xF0))	//P5
		{
			P6M1 &= ~(1<<(pin&0xF));
			P6M0 &= ~(1<<(pin&0xF));
		}
		if(0x70 == (pin&0xF0))	//P5
		{
			P7M1 &= ~(1<<(pin&0xF));
			P7M0 &= ~(1<<(pin&0xF));
		}
	}
	else if(GPO_PP == mode)
	{
		if(0x00 == (pin&0xF0))	//P0
		{
			P0M1 &= ~(1<<(pin&0xF));
			P0M0 |=  (1<<(pin&0xF));
		}
		if(0x10 == (pin&0xF0))	//P1
		{
			P1M1 &= ~(1<<(pin&0xF));
			P1M0 |=  (1<<(pin&0xF));
		}
		if(0x20 == (pin&0xF0))	//P2
		{
			P2M1 &= ~(1<<(pin&0xF));
			P2M0 |=  (1<<(pin&0xF));
		}
		
		if(0x30 == (pin&0xF0))	//P3
		{
			P3M1 &= ~(1<<(pin&0xF));
			P3M0 |=  (1<<(pin&0xF));
		}
		if(0x40 == (pin&0xF0))	//P4
		{
			P4M1 &= ~(1<<(pin&0xF));
			P4M0 |=  (1<<(pin&0xF));
		}
		if(0x50 == (pin&0xF0))	//P5
		{
			P5M1 &= ~(1<<(pin&0xF));
			P5M0 |=  (1<<(pin&0xF));
		}
		if(0x60 == (pin&0xF0))	//P4
		{
			P6M1 &= ~(1<<(pin&0xF));
			P6M0 |=  (1<<(pin&0xF));
		}
		if(0x70 == (pin&0xF0))	//P5
		{
			P7M1 &= ~(1<<(pin&0xF));
			P7M0 |=  (1<<(pin&0xF));
		}
		
	}
	else if(GPI_IMPEDANCE == mode)
	{
		if(0x00 == (pin&0xF0))	//P0
		{
			P0M1 |=  (1<<(pin&0xF));
			P0M0 &= ~(1<<(pin&0xF));
		}
		if(0x10 == (pin&0xF0))	//P1
		{
			P1M1 |=  (1<<(pin&0xF));
			P1M0 &= ~(1<<(pin&0xF));
		}
		if(0x20 == (pin&0xF0))	//P2
		{
			P2M1 |=  (1<<(pin&0xF));
			P2M0 &= ~(1<<(pin&0xF));
		}
		
		if(0x30 == (pin&0xF0))	//P3
		{
			P3M1 |=  (1<<(pin&0xF));
			P3M0 &= ~(1<<(pin&0xF));
		}
		if(0x40 == (pin&0xF0))	//P4
		{
			P4M1 |=  (1<<(pin&0xF));
			P4M0 &= ~(1<<(pin&0xF));
		}
		if(0x50 == (pin&0xF0))	//P5
		{
			P5M1 |=  (1<<(pin&0xF));
			P5M0 &= ~(1<<(pin&0xF));
		}
		if(0x60 == (pin&0xF0))	//P5
		{
			P6M1 |=  (1<<(pin&0xF));
			P6M0 &= ~(1<<(pin&0xF));
		}
		if(0x70 == (pin&0xF0))	//P5
		{
			P7M1 |=  (1<<(pin&0xF));
			P7M0 &= ~(1<<(pin&0xF));
		}
	}
	else if(GPI_OD == mode)
	{
		if(0x00 == (pin&0xF0))	//P0
		{
			P0M1 |= (1<<(pin&0xF));
			P0M0 |= (1<<(pin&0xF));
		}
		if(0x10 == (pin&0xF0))	//P1
		{
			P1M1 |= (1<<(pin&0xF));
			P1M0 |= (1<<(pin&0xF));
		}
		if(0x20 == (pin&0xF0))	//P2
		{
			P2M1 |= (1<<(pin&0xF));
			P2M0 |= (1<<(pin&0xF));
		}
		
		if(0x30 == (pin&0xF0))	//P3
		{
			P3M1 |= (1<<(pin&0xF));
			P3M0 |= (1<<(pin&0xF));
		}
		if(0x40 == (pin&0xF0))	//P4
		{
			P4M1 |= (1<<(pin&0xF));
			P4M0 |= (1<<(pin&0xF));
		}
		if(0x50 == (pin&0xF0))	//P5
		{
			P5M1 |= (1<<(pin&0xF));
			P5M0 |= (1<<(pin&0xF));
		}
		if(0x60 == (pin&0xF0))	//P5
		{
			P6M1 |= (1<<(pin&0xF));
			P6M0 |= (1<<(pin&0xF));
		}
		if(0x70 == (pin&0xF0))	//P5
		{
			P7M1 |= (1<<(pin&0xF));
			P7M0 |= (1<<(pin&0xF));
		}
	}
}

