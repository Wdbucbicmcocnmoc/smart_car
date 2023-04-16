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

#ifndef __ZF_UART_H
#define __ZF_UART_H


#include "common.h"
#include "zf_tim.h"

#define UART1_RX_BUFFER_SIZE	100
#define UART1_TX_BUFFER_SIZE	100


#define	UART1_CLEAR_RX_FLAG (SCON  &= ~0x01)
#define	UART2_CLEAR_RX_FLAG (S2CON &= ~0x01)
#define	UART3_CLEAR_RX_FLAG (S3CON &= ~0x01)
#define	UART4_CLEAR_RX_FLAG (S4CON &= ~0x01)

#define	UART1_CLEAR_TX_FLAG (SCON  &= ~0x02)
#define	UART2_CLEAR_TX_FLAG (S2CON &= ~0x02)
#define	UART3_CLEAR_TX_FLAG (S3CON &= ~0x02)
#define	UART4_CLEAR_TX_FLAG (S4CON &= ~0x02)


#define UART1_GET_RX_FLAG   (SCON  & 0x01)
#define UART2_GET_RX_FLAG   (S2CON & 0x01)
#define UART3_GET_RX_FLAG   (S3CON & 0x01)
#define UART4_GET_RX_FLAG   (S4CON & 0x01)
						    
#define UART1_GET_TX_FLAG   (SCON  & 0x02)
#define UART2_GET_TX_FLAG   (S2CON & 0x02)
#define UART3_GET_TX_FLAG   (S3CON & 0x02)
#define UART4_GET_TX_FLAG   (S4CON & 0x02)


//此枚举定义不允许用户修改
typedef enum //枚举串口号
{
    UART_1,
    UART_2,
    UART_3,
    UART_4,
}UARTN_enum;

		
//此枚举定义不允许用户修改
typedef enum //枚举串口引脚
{
	UART1_RX_P30, UART1_TX_P31,		//只能使用同一行的RX和TX引脚号。不允许混用
	UART1_RX_P36, UART1_TX_P37,		//例如:UART1_RX_P30,UART1_TX_P37。这样不行。
	UART1_RX_P16, UART1_TX_P17,
	UART1_RX_P43, UART1_TX_P44,
	
	UART2_RX_P10, UART2_TX_P11,
	UART2_RX_P46, UART2_TX_P47,
	
	UART3_RX_P00, UART3_TX_P01,
	UART3_RX_P50, UART3_TX_P51,
	
	UART4_RX_P02, UART4_TX_P03,
	UART4_RX_P52, UART4_TX_P53,	

	
}UARTPIN_enum;





extern uint8 uart1_tx_buff[UART1_TX_BUFFER_SIZE];	//发送缓冲
extern uint8 uart1_rx_buff[UART1_RX_BUFFER_SIZE];	//接收缓冲
extern uint8 busy[5];


void uart_init(UARTN_enum uart_n, UARTPIN_enum uart_rx_pin, UARTPIN_enum uart_tx_pin, uint32 baud,TIMN_enum tim_n);
void uart_putchar(UARTN_enum uart_n,uint8 dat);
void uart_putstr(UARTN_enum uart_n,uint8 *str);
void uart_putbuff(UARTN_enum uart_n,uint8 *p,uint16 len);

#endif