/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		uart
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/

#include "zf_uart.h"
#include "board.h"
   


uint8 busy[5];				 //接收忙标志位

uint8 uart1_tx_buff[UART1_TX_BUFFER_SIZE];	//发送缓冲
uint8 uart1_rx_buff[UART1_RX_BUFFER_SIZE];	//接收缓冲


//-------------------------------------------------------------------------------------------------------------------
//  @brief      串口初始化
//  @param      uart_n          串口模块号(USART_1,USART_2,USART_3,USART_4)
//  @param      uart_rx_pin     串口接收引脚
//  @param      uart_tx_pin     串口发送引脚
//  @param      baud      		串口波特率
//  @param      tim_n      		使用tim_n作为串口波特率发生器(TIM1-TIM4)
//  @return     NULL          	
//  Sample usage:               uart_init(UART_1, UART1_RX_P30, UART1_TX_P31, 115200, TIM_2);        //初始化串口1 波特率115200 发送引脚使用P31 接收引脚使用P30 ,使用定时器2作为波特率发生器
//  @note                       串口1使用 定时器1或者定时器2 作为波特率发生器。
//								串口2使用 定时器2 			 作为波特率发生器。
//								串口3使用 定时器3或者定时器2 作为波特率发生器。
//								串口4使用 定时器4或者定时器2 作为波特率发生器。
//                              STC16F仅有 定时器0-定时器4，这5个定时器。
//								编码器采集数据也需要定时器作为外部计数。
//								如果不同的串口，使用同一个定时器，串口的波特率以最后一个初始化为准
//-------------------------------------------------------------------------------------------------------------------
void uart_init(UARTN_enum uart_n, UARTPIN_enum uart_rx_pin, UARTPIN_enum uart_tx_pin, uint32 baud, TIMN_enum tim_n)
{
    uint16 brt;

	brt = (uint16)(65536 - (sys_clk/baud/4));


	switch(uart_n)
	{
		case UART_1:
		{
			if(TIM_1 == tim_n)
			{
				SCON |= 0x50;
				TMOD |= 0x00;
				TL1 = brt;
				TH1 = brt >> 8;
				AUXR |= 0x40;
				TR1 = 1;
				busy[1] = 0;
			}
			else if(TIM_2 == tim_n)
			{
				SCON |= 0x50;
				T2L = brt;
				T2H = brt >> 8;
				AUXR |= 0x15;
			}
			P_SW1 &= ~(0x03<<6);
			if((UART1_RX_P30 == uart_rx_pin) && (UART1_TX_P31 == uart_tx_pin))
			{
				P_SW1 |= 0x00;
			}
			else if((UART1_RX_P36 == uart_rx_pin) && (UART1_TX_P37 == uart_tx_pin))
			{
				P_SW1 |= 0x40;
			}
			else if((UART1_RX_P16 == uart_rx_pin) && (UART1_TX_P17 == uart_tx_pin))
			{
				P_SW1 |= 0x80;
			}
			else if((UART1_RX_P43 == uart_rx_pin) && (UART1_TX_P44 == uart_tx_pin))
			{
				P_SW1 |= 0xc0;
			}
			busy[1] = 0;
			ES = 1;
			break;
		}
		
		case UART_2:
		{
			if(TIM_2 == tim_n)
			{
				S2CON |= 0x10;
				T2L = brt;
				T2H = brt >> 8;
				AUXR |= 0x14;
			}
			
			P_SW2 &= ~(0x01<<0);
			if((UART2_RX_P10 == uart_rx_pin) && (UART2_TX_P11 == uart_tx_pin))
			{
				P_SW2 |= 0x00;
			}
			else if((UART2_RX_P46 == uart_rx_pin) && (UART2_TX_P47 == uart_tx_pin))
			{
				P_SW2 |= 0x01;
			}
			
			IE2 |= 0x01 << 0;	//允许串行口2中断
			busy[2] = 0;
			break;
		}
		
		case UART_3:
		{
			if(TIM_2 == tim_n)
			{
				S3CON |= 0x10;
				T2L = brt;
				T2H = brt >> 8;
				AUXR |= 0x14;
			}
			else if(TIM_3 == tim_n)
			{
				S3CON |= 0x50;
				T3L = brt;
				T3H = brt >> 8;
				T4T3M |= 0x0a;
			}
			
			P_SW2 &= ~(0x01<<1);
			if((UART3_RX_P00 == uart_rx_pin) && (UART3_TX_P01 == uart_tx_pin))
			{
				P_SW2 |= 0x00;
			}
			else if((UART3_RX_P50 == uart_rx_pin) && (UART3_TX_P51 == uart_tx_pin))
			{
				P_SW2 |= 0x02;
			}
			
			IE2 |= 0x01<<3;	//允许串行口3中断
			busy[3] = 0;
			break;
		}
		
		case UART_4:
		{
			if(TIM_2 == tim_n)
			{
				S4CON |= 0x10;
				T2L = brt;
				T2H = brt >> 8;
				AUXR |= 0x14;
			}
			else if(TIM_4 == tim_n)
			{
				S4CON |= 0x50;
				T4L = brt;
				T4H = brt >> 8;
				T4T3M |= 0xa0;
			}

			P_SW2 &= ~(0x01<<2);
			if((UART4_RX_P02 == uart_rx_pin) && (UART4_TX_P03 == uart_tx_pin))
			{
				P_SW2 |= 0x00;
			}
			else if((UART4_RX_P52 == uart_rx_pin) && (UART4_TX_P53 == uart_tx_pin))
			{
				P5M0 = 0x00;
				P5M1 = 0x01<<2;//P5.2 需要设置为高阻
				P_SW2 |= 0x04;
			}
			IE2 |= 0x01<<4;	//允许串行口4中断
			busy[4] = 0;
			break;
		}
		
	}

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      串口字节输出
//  @param      uart_n          串口模块号(USART_1,USART_2,USART_3,USART_4)
//  @param      dat             需要发送的字节
//  @return     void        
//  Sample usage:               uart_putchar(UART_1,0xA5);       // 串口1发送0xA5
//-------------------------------------------------------------------------------------------------------------------
void uart_putchar(UARTN_enum uart_n,uint8 dat)
{
	switch(uart_n)
	{
		case UART_1:
			while (busy[1]);
			busy[1] = 1;
			SBUF = dat;
		    break;
		case UART_2:
			while (busy[2]);
			busy[2] = 1;
			S2BUF = dat;
		    break;
		case UART_3:
			while (busy[3]);
			busy[3] = 1;
			S3BUF = dat;
		    break;
		case UART_4:
			while (busy[4]);
			busy[4] = 1;
			S4BUF = dat;
		    break;
	}
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      串口发送数组
//  @param      uart_n          串口模块号(USART_1,USART_2,USART_3,USART_4)
//  @param      *buff           要发送的数组地址
//  @param      len             发送长度
//  @return     void
//  Sample usage:               uart_putbuff(UART_1,&a[0],5);
//-------------------------------------------------------------------------------------------------------------------
void uart_putbuff(UARTN_enum uart_n,uint8 *p,uint16 len)
{
    while(len--)
        uart_putchar(uart_n,*p++);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      串口发送字符串
//  @param      uart_n          串口模块号(USART_1,USART_2,USART_3,USART_4)
//  @param      *str            要发送的字符串地址
//  @return     void
//  Sample usage:               uart_putstr(UART_1,"i lvoe you"); 
//-------------------------------------------------------------------------------------------------------------------
void uart_putstr(UARTN_enum uart_n,uint8 *str)
{
    while(*str)
    {
        uart_putchar(uart_n, *str++);
    }
}
