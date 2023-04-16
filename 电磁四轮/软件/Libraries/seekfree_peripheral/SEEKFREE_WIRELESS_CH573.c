/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             zf_device_wireless_ch573
* @company          成都逐飞科技有限公司
* @author           逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2022-03-02
* @note
********************************************************************************************************************/

#include "SEEKFREE_WIRELESS_CH573.h"
#include "zf_uart.h"
#include "zf_fifo.h"


static  fifo_struct     wireless_ch573_fifo;
static  uint8           wireless_ch573_buffer[WIRELESS_CH573_BUFFER_SIZE];  // 数据存放数组

static          uint8   wireless_ch573_data;


//-------------------------------------------------------------------------------------------------------------------
//  @brief      573转串口模块回调函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
void wireless_ch573_callback(void)
{
    //接到一个字节后单片机将会进入串口中断，通过在此处读取wireless_ch573_data可以取走数据
    wireless_ch573_data = WIRELESS_CH573_DATA_BUF;
    fifo_write_buffer(&wireless_ch573_fifo, &wireless_ch573_data, 1);       // 存入 FIFO
}




//-------------------------------------------------------------------------------------------------------------------
//  @brief      573转串口模块 发送函数
//  @param      buff        需要发送的数据地址
//  @param      len         发送长度
//  @return     uint32      剩余未发送的字节数   
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_ch573_send_buff(uint8 *buff, uint16 len)
{
    while(len>30)
    {
        if(WIRELESS_CH573_RTS_PIN == 1)  
        {
            return len;//模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
        }
        //while(RTS_PIN);  //如果RTS为低电平，则继续发送数据
        uart_putbuff(WIRELESS_CH573_UART,buff,30);

        buff += 30; //地址偏移
        len -= 30;//数量
    }
    
    if(WIRELESS_CH573_RTS_PIN == 1)  
    {
        return len;//模块忙,如果允许当前程序使用while等待 则可以使用后面注释的while等待语句替换本if语句
    }
    //while(WIRELESS_CH573_RTS_PIN);  //如果RTS为低电平，则继续发送数据
    uart_putbuff(WIRELESS_CH573,buff,len);//发送最后的数据
    
    return 0;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      无线转串口模块 读取函数
//  @param      buff            存储的数据地址
//  @param      len             长度
//  @return     uint32          实际读取字节数
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint32 wireless_ch573_read_buff (uint8 *buff, uint32 len)
{
    uint32 data_len = len;
    fifo_read_buffer(&wireless_ch573_fifo, buff, &data_len, FIFO_READ_AND_CLEAN);
    return data_len;
}





//-------------------------------------------------------------------------------------------------------------------
//  @brief      573转串口模块初始化
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       
//-------------------------------------------------------------------------------------------------------------------
void wireless_ch573_init(void)
{
    WIRELESS_CH573_RTS_PIN = 0;
    wireless_type = WIRELESS_CH573;
    //本函数使用的波特率为115200，为573转串口模块的默认波特率，如需其他波特率请自行配置模块并修改串口的波特率
    fifo_init(&wireless_ch573_fifo, wireless_ch573_buffer, WIRELESS_CH573_BUFFER_SIZE);
    uart_init(WIRELESS_CH573_UART, WIRELESS_CH573_UART_RX_PIN, WIRELESS_CH573_UART_TX_PIN, WIRELESS_CH573_UART_BAUD, WIRELESS_CH573_TIMER_N);	//初始化串口    
    
}


