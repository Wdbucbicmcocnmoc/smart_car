/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2021,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		逐飞科技蓝牙转串口模块
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.33
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2021-08-27
 * @note		
					接线定义：
					------------------------------------ 
					    蓝牙转串口      单片机                        
    					RX              查看SEEKFREE_BLUETOOTH_CH9141.h文件中的BLUETOOTH_CH9141_UART_TX宏定义
    					TX              查看SEEKFREE_BLUETOOTH_CH9141.h文件中的BLUETOOTH_CH9141_UART_RX宏定义
    					RTS             查看SEEKFREE_BLUETOOTH_CH9141.h文件中的BLUETOOTH_CH9141_RTS_PIN宏定义
                        CTS             悬空
    					CMD             悬空或者上拉
					------------------------------------ 
 ********************************************************************************************************************/
#include "stdio.h"
#include "string.h"
#include "board.h"
#include "zf_gpio.h"
#include "zf_uart.h"
#include "zf_nvic.h"
#include "zf_delay.h"
#include "zf_fifo.h"

#include "SEEKFREE_BLUETOOTH_CH9141.h"



static  fifo_struct     bluetooth_ch9141_fifo;
static  uint8           bluetooth_ch9141_buffer[BLUETOOTH_CH9141_BUFFER_SIZE];  // 数据存放数组

static          uint8   bluetooth_ch9141_data;

//-------------------------------------------------------------------------------------------------------------------
//  @brief      蓝牙转串口模块 串口中断回调函数
//  @param      void
//  @return     void
//  Sample usage:
//  @note       该函数在ISR文件 串口中断程序被调用
//-------------------------------------------------------------------------------------------------------------------
void bluetooth_ch9141_uart_callback (void)
{
    // 读取无线串口的数据 并且置位接收标志
    bluetooth_ch9141_data = BLUETOOTH_CH9141_DATA_BUF;
    fifo_write_buffer(&bluetooth_ch9141_fifo, &bluetooth_ch9141_data, 1);       // 存入 FIFO
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      蓝牙转串口模块初始化
//  @param      mode            蓝牙模式 MASTER_MODE(主机)或者SLAVE_MODE(从机)
// @return      uint8           
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 bluetooth_ch9141_init (void)
{
    wireless_type = WIRELESS_CH9141;
    // 本函数使用的波特率为115200 为蓝牙转串口模块的默认波特率 如需其他波特率请使用上位机修改模块参数
    fifo_init(&bluetooth_ch9141_fifo, bluetooth_ch9141_buffer, BLUETOOTH_CH9141_BUFFER_SIZE);
    uart_init(BLUETOOTH_CH9141_INDEX, BLUETOOTH_CH9141_TX_PIN, BLUETOOTH_CH9141_RX_PIN, BLUETOOTH_CH9141_BUAD_RATE, BLUETOOTH_CH9141_TIMER);
    return 0;
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块 发送函数
//  @param      buff            需要发送的数据地址
//  @param      len             发送长度
//  @return     uint32          剩余未发送的字节数
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint32 bluetooth_ch9141_send_buff (uint8 *buff, uint32 len)
{
    uint16 time_count = 0;
    while(len > 30)
    {
        time_count = 0;
        while(BLUETOOTH_CH9141_RTS_PIN && time_count++ < BLUETOOTH_CH9141_TIMEOUT_COUNT)  // 如果RTS为低电平，则继续发送数据
            delay_ms(1);
        if(time_count >= BLUETOOTH_CH9141_TIMEOUT_COUNT)
            return len;                                                         // 模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
        uart_putbuff(BLUETOOTH_CH9141_INDEX, buff, 30);

        buff += 30;                                                             // 地址偏移
        len -= 30;                                                              // 数量
    }

    time_count = 0;
    while(BLUETOOTH_CH9141_RTS_PIN && time_count++ < BLUETOOTH_CH9141_TIMEOUT_COUNT)      // 如果RTS为低电平，则继续发送数据
        delay_ms(1);
    if(time_count >= BLUETOOTH_CH9141_TIMEOUT_COUNT)
        return len;                                                             // 模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
    uart_putbuff(BLUETOOTH_CH9141_INDEX, buff, (uint16)len);                            // 发送最后的数据

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块 读取函数
//  @param      buff            存储的数据地址
//  @param      len             长度
//  @return     uint32          实际读取字节数
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint32 bluetooth_ch9141_read_buff (uint8 *buff, uint32 len)
{
    uint32 data_len = len;
    fifo_read_buffer(&bluetooth_ch9141_fifo, buff, &data_len, FIFO_READ_AND_CLEAN);
    return data_len;
}



