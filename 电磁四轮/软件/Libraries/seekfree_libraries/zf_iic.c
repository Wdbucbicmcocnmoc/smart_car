/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		iic
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F2K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/
#pragma warning disable = 47
#include "zf_iic.h"



//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部使用用户无需关心
//  @param      NULL            	
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
void iic_delay_us(uint16 x)	//33.1776Mhz
{
    uint8 i;
    while(x--)
    {
		i = 9;
		while (--i);
    }
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部使用用户无需关心
//  @param      NULL            	
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
uint8 wait(void)
{
    uint16 count = 0;
    uint8 ret = IIC_SEND_OK;
    while (!(I2CMSST & 0x40))
    {
        iic_delay_us(1);
        if(count++ >= 30)//等待超过30us，则退出等待。
        {
            ret = IIC_SEND_FAIL;
            break;
        }
    }
    I2CMSST &= ~0x40;
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部使用用户无需关心
//  @param      NULL            	
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
uint8 start(void)
{
    uint8 ret;
    I2CMSCR = 0x01;                             //发送start命令
    ret = wait();
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部使用用户无需关心
//  @param      NULL            	
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
uint8 send_data(char dat)
{
    uint8 ret;
    I2CTXD = dat;                               //写数据到数据缓冲区
    I2CMSCR = 0x02;                             //发送SEND命令
    ret = wait();
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部使用用户无需关心
//  @param      NULL            	
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
uint8 recv_ack(void)
{
    uint8 ret;
    I2CMSCR = 0x03;                             //发送读ACK命令
    ret = wait();
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部使用用户无需关心
//  @param      NULL            	
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
char recv_data(void)							//接收数据
{
    I2CMSCR = 0x04;                             //发送RECV命令
    wait();
    return I2CRXD;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部使用用户无需关心
//  @param      NULL            	
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
uint8 send_ack(void)
{
	uint8 ret;
    I2CMSST = 0x00;                             //设置ACK信号
    I2CMSCR = 0x05;                             //发送ACK命令
    ret = wait();
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部使用用户无需关心
//  @param      NULL            	
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
void send_nak(void)
{
    I2CMSST = 0x01;                             //设置NAK信号
    I2CMSCR = 0x05;                             //发送ACK命令
    wait();
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部使用用户无需关心
//  @param      NULL            	
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
uint8 stop(void)
{
    uint8 ret;
    I2CMSCR = 0x06;                             //发送stop命令
    ret = wait();
    return ret;
}




//#define UNUSED(expr1, expr2) do { if(scl_pin == sda_pin); } while (0)
//-------------------------------------------------------------------------------------------------------------------
//  @brief      硬件IIC初始化
//  @param      iic_n           选择IIC模块
//  @param      wait_time       I2C总线速度（等待时钟数）控制: 速度设置为等待wait_time*2+1个时钟
//  @return     void
//  Sample usage:              
//-------------------------------------------------------------------------------------------------------------------
void iic_init(IICN_enum iic_n, IIC_PIN_enum scl_pin, IIC_PIN_enum sda_pin, uint32 wait_time)
{
	//UNUSED(scl_pin);
	//__attribute__ ((unused))(sda_pin);
	//UNUSED(scl_pin, sda_pin);

    P_SW2 &= ~(0x03<<4);
    P_SW2 |= 1<<7;	//将EAXFR寄存器置1，这样才能使用特殊功能寄存器为扩展SFR，访问逻辑地址位于 XDATA 区域
    switch(iic_n)
    {
    case IIC_1:
        P_SW2 |= (0x00<<4);	//SCL:P1.5	SDA:P1.4
        break;
    case IIC_2:
        P_SW2 |= (0x01<<4);	//SCL:P2.5	SDA:P2.4
        break;
    case IIC_3:
        P_SW2 |= (0x02<<4);	//SCL:P7.7	SDA:P7.6
        break;
    case IIC_4:
        P_SW2 |= (0x03<<4);	//SCL:P3.2	SDA:P3.3
        break;
    }

    I2CCFG |= 1<<6;		//主机模式
    I2CCFG |= 1<<7;		//使能IIC
    I2CCFG |= wait_time;//速度设置为等待wait_time*2+1个时钟
    I2CMSST = 0x00;		//主机状态寄存器

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      写入一个字节数据到I2C设备指定寄存器地址
//  @param      iic_n       IIC模块(IIC_1,IIC_2,IIC_3,IIC_0)
//  @param      slaveid     从机地址(7位地址)
//  @param      reg         从机寄存器地址
//  @param      dat         需要发送的数据
//  @return                 返回的状态值 0：成功  1：失败
//  @since      v2.0
//  Sample usage:       	iic_write_reg(0x2D, 0x50,2);     //写入数据2到0x50地址，从机地址为0x2D
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_write_reg(uint8 dev_add, uint8 reg, uint8 dat)
{
    if(start() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(send_data((dev_add<<1) | 0x00) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(send_data(reg) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(send_data(dat) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(stop() != IIC_SEND_OK)
        return IIC_SEND_FAIL;


    return IIC_SEND_OK;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取I2C设备指定地址寄存器的数据
//  @param      iic_n        I2C通道号及引脚
//  @param      dev_add     从机地址(7位地址)
//  @param      reg         从机寄存器地址
//  @param      dat         数据地址
//  @return                 读取的寄存器值
//  @since      v1.0
//  Sample usage:       	uint8 value = iic_read_reg(i2c0, 0x2D, 0x50);//读取0x50地址的数据，从机地址为0x2D
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_read_reg(uint8 dev_add, uint8 reg, uint8 *dat)
{
	if(start() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    if(send_data((dev_add<<1) | 0x00) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    if(send_data(reg) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
	
//   if(start() != IIC_SEND_OK)
//        return IIC_SEND_FAIL;
   
    if(send_data((dev_add<<1) | 0x01) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	

    *dat = recv_data(); //读取数据

	
    if(send_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    if(stop() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    return IIC_SEND_OK;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取I2C设备指定地址寄存器的数据
//  @param      iic_n       I2C通道号及引脚
//  @param      dev_add     从机地址(7位地址)
//  @param      reg         从机寄存器地址
//  @param      dat         读取的数据存储的地址
//  @param      num         读取字节数
//  @return     void
//  @since      v1.0
//  Sample usage:       	uint8 value = i2c_read_reg(i2c0, 0x2D, 0x50, 10, buf);//读取0x50地址的数据，从机地址为0x2D开始的10个字节
//-------------------------------------------------------------------------------------------------------------------
uint8 iic_read_reg_bytes(uint8 dev_add, uint8 reg
						, uint8 *dat, uint8 num)
{

	if(start() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    if(send_data((dev_add<<1) | 0x00) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;
	
    if(send_data(reg) != IIC_SEND_OK)
        return IIC_SEND_FAIL;
    if(recv_ack() != IIC_SEND_OK)
        return IIC_SEND_FAIL;

	if(send_data((dev_add<<1) | 0x01) != IIC_SEND_OK)
		return IIC_SEND_FAIL;
	if(recv_ack() != IIC_SEND_OK)
		return IIC_SEND_FAIL;

    while(--num)
    {
        *dat = recv_data(); //读取数据
		if(send_ack() != IIC_SEND_OK)
		{
			return IIC_SEND_FAIL;
		}
        dat++;
    }
	
	*dat = recv_data();
	
	if(send_ack() != IIC_SEND_OK)
		return IIC_SEND_FAIL;
	
	if(stop() != IIC_SEND_OK)
		return IIC_SEND_FAIL;
	
	return IIC_SEND_OK;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      硬件IIC引脚切换函数
//  @param      iic_n       	I2C通道号及引脚
//  @param      scl_pin         选择SCL引脚
//  @param      sda_pin         选择SDA引脚
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void iic_change_pin(IICN_enum iic_n,IIC_PIN_enum scl_pin,IIC_PIN_enum sda_pin)
{
    P_SW2 |= 1<<7;	//将EAXFR寄存器置1，这样才能使用特殊功能寄存器为扩展SFR，访问逻辑地址位于 XDATA 区域
	
	P_SW2 &= ~(0x03<<4);	//清除引脚切换位
    switch(iic_n)	
    {
    case IIC_1:
        P_SW2 |= (0x00<<4);	//SCL:P1.5	SDA:P1.4
        break;
    case IIC_2:
        P_SW2 |= (0x01<<4);	//SCL:P2.5	SDA:P2.4
        break;
    case IIC_3:
        P_SW2 |= (0x02<<4); //SCL:P7.7	SDA:P7.6 STC8H 48脚核心板没有该组引脚。
        break;
    case IIC_4:
        P_SW2 |= (0x03<<4);	//SCL:P3.2	SDA:P3.3
        break;
    }
	
	P_SW2 &= ~(1<<7);

}
