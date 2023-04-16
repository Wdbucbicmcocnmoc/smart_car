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
 * @Software 		MDK5.27
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#include "zf_pwm.h"
#include "board.h"
#include "zf_gpio.h"
#include "zf_uart.h"
#include "stdio.h"


//#pragma warning disable = 208


//捕获比较模式寄存器
const uint32 PWM_CCMR_ADDR[] = {0x7efec8, 0x7efec9, 0x7efeca ,0x7efecb, 
								0x7efee8, 0x7efee9, 0x7efeea, 0x7efeeb};
//捕获比较使能寄存器
const uint32 PWM_CCER_ADDR[] = {0x7efecc, 0x7efecd, 
								0x7efeec ,0x7efeed};
//控制寄存器,高8位地址  低8位地址 + 1即可
const uint32 PWM_CCR_ADDR[] = {0x7efed5, 0x7efed7, 0x7efed9, 0x7efedb,
							   0x7efef5, 0x7efef7, 0x7efef9, 0x7efefb};
	
							   //控制寄存器,高8位地址  低8位地址 + 1即可
const uint32 PWM_ARR_ADDR[] = {0x7efed2,0x7efef2};

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM_gpio初始化（内部使用用户无需关心）
//  @param      pwmch       PWM通道号及引脚
//  @return     void
//  Sample usage:           
//-------------------------------------------------------------------------------------------------------------------
void pwm_set_gpio(PWMCH_enum pwmch)
{
	switch(pwmch)
	{
		case PWMA_CH1P_P10:
		{
			gpio_mode(P1_0,GPO_PP);
			break;
		}
		case PWMA_CH1N_P11:
		{
			gpio_mode(P1_1,GPO_PP);
			break;
		}
		case PWMA_CH1P_P20:
		{
			gpio_mode(P2_0,GPO_PP);
			break;
		}
		case PWMA_CH1N_P21:
		{
			gpio_mode(P2_1,GPO_PP);
			break;
		}
		case PWMA_CH1P_P60:
		{
			gpio_mode(P6_0,GPO_PP);
			break;
		}
		case PWMA_CH1N_P61:
		{
			gpio_mode(P6_1,GPO_PP);
			break;
		}
		
		case PWMA_CH2P_P12:
		{
			gpio_mode(P1_2,GPO_PP);
			break;
		}
		case PWMA_CH2N_P13:
		{
			gpio_mode(P1_3,GPO_PP);
			break;
		}
		case PWMA_CH2P_P22:
		{
			gpio_mode(P2_2,GPO_PP);
			break;
		}
		case PWMA_CH2N_P23:
		{
			gpio_mode(P2_3,GPO_PP);
			break;
		}
		case PWMA_CH2P_P62:
		{
			gpio_mode(P6_2,GPO_PP);
			break;
		}
		case PWMA_CH2N_P63:
		{
			gpio_mode(P6_3,GPO_PP);
			break;
		}
		
		case PWMA_CH3P_P14:
		{
			gpio_mode(P1_4,GPO_PP);
			break;
		}
		case PWMA_CH3N_P15:
		{
			gpio_mode(P1_5,GPO_PP);
			break;
		}
		case PWMA_CH3P_P24:
		{
			gpio_mode(P2_4,GPO_PP);
			break;
		}
		case PWMA_CH3N_P25:
		{
			gpio_mode(P2_5,GPO_PP);
			break;
		}
		case PWMA_CH3P_P64:
		{
			gpio_mode(P6_4,GPO_PP);
			break;
		}
		case PWMA_CH3N_P65:
		{
			gpio_mode(P6_5,GPO_PP);
			break;
		}
		
		
		case PWMA_CH4P_P16:
		{
			gpio_mode(P1_6,GPO_PP);
			break;
		}
		case PWMA_CH4N_P17:
		{
			gpio_mode(P1_7,GPO_PP);
			break;
		}
		case PWMA_CH4P_P26:
		{
			gpio_mode(P2_6,GPO_PP);
			break;
		}
		case PWMA_CH4N_P27:
		{
			gpio_mode(P2_7,GPO_PP);
			break;
		}
		case PWMA_CH4P_P66:
		{
			gpio_mode(P6_6,GPO_PP);
			break;
		}
		case PWMA_CH4N_P67:
		{
			gpio_mode(P6_7,GPO_PP);
			break;
		}
		case PWMA_CH4P_P34:
		{
			gpio_mode(P3_4,GPO_PP);
			break;
		}
		case PWMA_CH4N_P33:
		{
			gpio_mode(P3_3,GPO_PP);
			break;
		}
		
		
		case PWMB_CH1_P20:
		{
			gpio_mode(P2_0,GPO_PP);
			break;
		}
		case PWMB_CH1_P17:
		{
			gpio_mode(P1_7,GPO_PP);
			break;
		}
		case PWMB_CH1_P00:
		{
			gpio_mode(P0_0,GPO_PP);
			break;
		}
		case PWMB_CH1_P74:
		{
			gpio_mode(P7_4,GPO_PP);
			break;
		}
		
		case PWMB_CH2_P21:
		{
			gpio_mode(P2_1,GPO_PP);
			break;
		}
		case PWMB_CH2_P54:
		{
			gpio_mode(P5_4,GPO_PP);
			break;
		}
		case PWMB_CH2_P01:
		{
			gpio_mode(P0_1,GPO_PP);
			break;
		}
		case PWMB_CH2_P75:
		{
			gpio_mode(P7_5,GPO_PP);
			break;
		}

		
		case PWMB_CH3_P22:
		{
			gpio_mode(P2_2,GPO_PP);
			break;
		}
		case PWMB_CH3_P33:
		{
			gpio_mode(P3_3,GPO_PP);
			break;
		}
		case PWMB_CH3_P02:
		{
			gpio_mode(P0_2,GPO_PP);
			break;
		}
		case PWMB_CH3_P76:
		{
			gpio_mode(P7_6,GPO_PP);
			break;
		}

		
		case PWMB_CH4_P23:
		{
			gpio_mode(P2_3,GPO_PP);
			break;
		}
		case PWMB_CH4_P34:
		{
			gpio_mode(P3_4,GPO_PP);
			break;
		}
		case PWMB_CH4_P03:
		{
			gpio_mode(P0_3,GPO_PP);
			break;
		}
		case PWMB_CH4_P77:
		{
			gpio_mode(P7_7,GPO_PP);
			break;
		}
		
	}
	
}
	
		
//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM初始化
//  @param      pwmch       PWM通道号及引脚
//  @param      freq        PWM频率(10Hz-3MHz)
//  @param      duty        PWM占空比
//  @return     void
//  Sample usage:           
//							pwm_init(PWM0_P00, 100, 5000);     //初始化PWM0  使用引脚P0.0  输出PWM频率100HZ   占空比为百分之 5000/PWM_DUTY_MAX*100
//							PWM_DUTY_MAX在zf_pwm.h文件中 默认为10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_init(PWMCH_enum pwmch,uint32 freq, uint32 duty)
{
	
	uint32 match_temp;
	uint32 period_temp; 
	uint16 freq_div = 0;
	
	
	P_SW2 |= 0x80;
	
	//GPIO需要设置为推挽输出
	pwm_set_gpio(pwmch);


	//分频计算，周期计算，占空比计算
	freq_div = (sys_clk / freq) >> 16;							//多少分频
	period_temp = sys_clk / freq ;			
	period_temp = period_temp / (freq_div + 1) - 1;				//周期

	match_temp = period_temp * ((float)duty / PWM_DUTY_MAX);	//占空比

	
	if(PWMB_CH1_P20 <= pwmch)				//PWM5-8
	{
		//通道选择，引脚选择
		PWM2_ENO |= (1 << ((2 * ((pwmch >> 4) - 4))));					//使能通道	
		PWM2_PS |= ((pwmch & 0x03) << ((2 * ((pwmch >> 4) - 4))));		//输出脚选择
		
		// 配置通道输出使能和极性	
		(*(unsigned char volatile far *) (PWM_CCER_ADDR[pwmch>>5])) |= (uint8)(1 << (((pwmch >> 4) & 0x01) * 4));
		
		//设置预分频
		PWM2_PSCRH = (uint8)(freq_div>>8);
		PWM2_PSCRL = (uint8)freq_div;
		
		PWM2_BKR = 0x80; 	//主输出使能 相当于总开关
		PWM2_CR1 = 0x01;	//PWM开始计数
	}
	else
	{
		PWM1_ENO |= (1 << (pwmch & 0x01)) << ((pwmch >> 4) * 2);	//使能通道	
		PWM1_PS  |= ((pwmch & 0x07) >> 1) << ((pwmch >> 4) * 2);    //输出脚选择
		
		// 配置通道输出使能和极性	
		(*(unsigned char volatile far *) (PWM_CCER_ADDR[pwmch>>5])) |= (1 << ((pwmch & 0x01) * 2 + ((pwmch >> 4) & 0x01) * 0x04));

		
		//设置预分频
		PWM1_PSCRH = (uint8)(freq_div>>8);
		PWM1_PSCRL = (uint8)freq_div;

		PWM1_BKR = 0x80; 	// 主输出使能 相当于总开关
		PWM1_CR1 = 0x01;	//PWM开始计数
	}
	
	//周期
	(*(unsigned char volatile far *) (PWM_ARR_ADDR[pwmch>>6])) = (uint8)(period_temp>>8);		//高8位
	(*(unsigned char volatile far *) (PWM_ARR_ADDR[pwmch>>6] + 1)) = (uint8)period_temp;		//低8位

	//设置捕获值|比较值
	(*(unsigned char volatile far *) (PWM_CCR_ADDR[pwmch>>4]))		= match_temp>>8;			//高8位
	(*(unsigned char volatile far *) (PWM_CCR_ADDR[pwmch>>4] + 1))  = (uint8)match_temp;		//低8位
	
	//功能设置
	(*(unsigned char volatile far *) (PWM_CCMR_ADDR[pwmch>>4])) |= 0x06<<4;		//设置为PWM模式1
	(*(unsigned char volatile far *) (PWM_CCMR_ADDR[pwmch>>4])) |= 1<<3;		//开启PWM寄存器的预装载功
	

//	P_SW2 &= 0x7F;

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM占空比设置
//  @param      pwmch       PWM通道号及引脚
//  @param      duty        PWM占空比
//  @return     void
//  Sample usage:           pwm_duty(PWM0_P00, 5000);     //初始化PWM0  使用引脚P0.0  输出PWM频率50HZ   占空比为百分之 5000/PWM_DUTY_MAX*100
//							PWM_DUTY_MAX在fsl_pwm.h文件中 默认为10000
//-------------------------------------------------------------------------------------------------------------------
void pwm_duty(PWMCH_enum pwmch, uint32 duty)
{
	uint32 match_temp;
	uint32 arr = ((*(unsigned char volatile far *) (PWM_ARR_ADDR[pwmch>>6]))<<8) | (*(unsigned char volatile far *) (PWM_ARR_ADDR[pwmch>>6] + 1 ));

//	P_SW2 |= 0x80;

	match_temp = arr * ((float)duty/PWM_DUTY_MAX);				//占空比
							
	
	//设置捕获值|比较值
	(*(unsigned char volatile far *) (PWM_CCR_ADDR[pwmch>>4]))		= match_temp>>8;			//高8位
	(*(unsigned char volatile far *) (PWM_CCR_ADDR[pwmch>>4] + 1))  = (uint8)match_temp;		//低8位

//	P_SW2 &= ~0x80;
	
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      PWM频率设置
//  @param      pwmch       PWM通道号及引脚
//  @param      freq        PWM频率(10Hz-3MHz)
//  @param      duty        PWM占空比
//  @return     void
//  Sample usage:           pwm_freq(PWM0_P00, 50, 5000);     //修改化PWM0  使用引脚P0.0  输出PWM频率50HZ   占空比为百分之 5000/PWM_DUTY_MAX*100
//-------------------------------------------------------------------------------------------------------------------
void pwm_freq(PWMCH_enum pwmch, uint32 freq, uint32 duty)
{
	uint32 match_temp;
    uint32 period_temp; 
	uint16 freq_div = 0;

	

	//分频计算，周期计算，占空比计算
	freq_div = (sys_clk / freq) >> 16;							//多少分频
	period_temp = sys_clk / freq;			
	period_temp = period_temp / (freq_div + 1) - 1;				//周期
	
	match_temp = period_temp * ((float)duty / PWM_DUTY_MAX);	//占空比
	
//	P_SW2 |= 0x80;
	
	if(PWMB_CH1_P20 <= pwmch)				//PWM5-8
	{
		//设置预分频
		PWM2_PSCRH = (uint8)(freq_div>>8);
		PWM2_PSCRL = (uint8)freq_div;
	}
	else
	{
		//设置预分频
		PWM1_PSCRH = (uint8)(freq_div>>8);
		PWM1_PSCRL = (uint8)freq_div;
	}
	
	//周期
	(*(unsigned char volatile far *) (PWM_ARR_ADDR[pwmch>>6])) = (uint8)(period_temp>>8);		//高8位
	(*(unsigned char volatile far *) (PWM_ARR_ADDR[pwmch>>6] + 1)) = (uint8)period_temp;		//低8位
	
		//设置捕获值|比较值
	(*(unsigned char volatile far *) (PWM_CCR_ADDR[pwmch>>4]))		= match_temp>>8;			//高8位
	(*(unsigned char volatile far *) (PWM_CCR_ADDR[pwmch>>4] + 1))  = (uint8)match_temp;		//低8位
	
//	P_SW2 &= ~0x80;
}


