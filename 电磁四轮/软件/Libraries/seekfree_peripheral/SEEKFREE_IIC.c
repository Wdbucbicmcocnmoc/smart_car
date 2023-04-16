/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		模拟IIC
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看common.h内VERSION宏定义
 * @Software 		MDK FOR C251 V5.60
 * @Target core		LPC54606J512BD100
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 * @note		
					接线定义：
					------------------------------------ 
						SCL                 查看SEEKFREE_IIC文件内的SEEKFREE_SCL宏定义
						SDA                 查看SEEKFREE_IIC文件内的SEEKFREE_SDA宏定义
					------------------------------------ 
 ********************************************************************************************************************/


#include "SEEKFREE_IIC.h"





#define SDA   			SIMIIC_SDA_PIN
#define SDA0()          SIMIIC_SDA_PIN = 0		//IO口输出低电平
#define SDA1()          SIMIIC_SDA_PIN = 1		//IO口输出高电平  
#define SCL0()          SIMIIC_SCL_PIN = 0		//IO口输出低电平
#define SCL1()          SIMIIC_SCL_PIN = 1		//IO口输出高电平


//内部数据定义
uint8 IIC_ad_main; //器件从地址	    
uint8 IIC_ad_sub;  //器件子地址	   
uint8 *IIC_buf;    //发送|接收数据缓冲区	    
uint8 IIC_num;     //发送|接收数据个数	     

#define ack 1      //主应答
#define no_ack 0   //从应答	 

//-------------------------------------------------------------------------------------------------------------------
//  @brief      模拟IIC初始化
//  @return     void						
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void  simiic_init(void)
{
	//GPIO已在board_init()中初始化。
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      模拟IIC延时
//  @return     void						
//  @since      v1.0
//  Sample usage:				如果IIC通讯失败可以尝试增加j的值
//-------------------------------------------------------------------------------------------------------------------
void simiic_delay(void)
{
    uint16 j=0;   
	while(j--);
}


//内部使用，用户无需调用
void simiic_start(void)
{
	SDA1();
	SCL1();
	simiic_delay();
	SDA0();
	simiic_delay();
	SCL0();
}

//内部使用，用户无需调用
void simiic_stop(void)
{
	SDA0();
	SCL0();
	simiic_delay();
	SCL1();
	simiic_delay();
	SDA1();
	simiic_delay();
}

//主应答(包含ack:SDA=0和no_ack:SDA=0)
//内部使用，用户无需调用
void simiic_sendack(unsigned char ack_dat)
{
    SCL0();
	simiic_delay();
	if(ack_dat) SDA0();
    else    	SDA1();

    SCL1();
    simiic_delay();
    SCL0();
    simiic_delay();
}


static int sccb_waitack(void)
{
    SCL0();

	simiic_delay();
	
	SCL1();
    simiic_delay();
	
    if(SDA)           //应答为高电平，异常，通信失败
    {

        SCL0();
        return 0;
    }

    SCL0();
	simiic_delay();
    return 1;
}

//字节发送程序
//发送c(可以是数据也可是地址)，送完后接收从应答
//不考虑从应答位
//内部使用，用户无需调用
void send_ch(uint8 c)
{
	uint8 i = 8;
    while(i--)
    {
        if(c & 0x80)	SDA1();//SDA 输出数据
        else			SDA0();
        c <<= 1;
        simiic_delay();
        SCL1();                //SCL 拉高，采集信号
        simiic_delay();
        SCL0();                //SCL 时钟线拉低
    }
	sccb_waitack();
}

//字节接收程序
//接收器件传来的数据，此程序应配合|主应答函数|使用
//内部使用，用户无需调用
uint8 read_ch(uint8 ack_x)
{
    uint8 i;
    uint8 c;
    c=0;
    SCL0();
    simiic_delay();
    SDA1();             

    for(i=0;i<8;i++)
    {
        simiic_delay();
        SCL0();         //置时钟线为低，准备接收数据位
        simiic_delay();
        SCL1();         //置时钟线为高，使数据线上数据有效
        simiic_delay();
        c<<=1;
        if(SDA) 
        {
            c+=1;   //读数据位，将接收的数据存c
        }
    }

	SCL0();
	simiic_delay();
	simiic_sendack(ack_x);
	
    return c;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      模拟IIC写数据到设备寄存器函数
//  @param      dev_add			设备地址(低七位地址)
//  @param      reg				寄存器地址
//  @param      dat				写入的数据
//  @return     void						
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void simiic_write_reg(uint8 dev_add, uint8 reg, uint8 dat)
{
	simiic_start();
    send_ch( (dev_add<<1) | 0x00);   //发送器件地址加写位
	send_ch( reg );   				 //发送从机寄存器地址
	send_ch( dat );   				 //发送需要写入的数据
	simiic_stop();
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      模拟IIC从设备寄存器读取数据
//  @param      dev_add			设备地址(低七位地址)
//  @param      reg				寄存器地址
//  @param      type			选择通信方式是IIC  还是 SCCB
//  @return     uint8			返回寄存器的数据			
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
uint8 simiic_read_reg(uint8 dev_add, uint8 reg, IIC_type type)
{
	uint8 dat;
	simiic_start();
    send_ch( (dev_add<<1) | 0x00);  //发送器件地址加写位
	send_ch( reg );   				//发送从机寄存器地址
	if(type == SCCB)simiic_stop();
	
	simiic_start();
	send_ch( (dev_add<<1) | 0x01);  //发送器件地址加读位
	dat = read_ch(no_ack);   				//读取数据
	simiic_stop();
	
	return dat;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      模拟IIC读取多字节数据
//  @param      dev_add			设备地址(低七位地址)
//  @param      reg				寄存器地址
//  @param      dat_add			数据保存的地址指针
//  @param      num				读取字节数量
//  @param      type			选择通信方式是IIC  还是 SCCB
//  @return     uint8			返回寄存器的数据			
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void simiic_read_regs(uint8 dev_add, uint8 reg, uint8 *dat_add, uint8 num, IIC_type type)
{
	simiic_start();
    send_ch( (dev_add<<1) | 0x00);  //发送器件地址加写位
	send_ch( reg );   				//发送从机寄存器地址
	if(type == SCCB)simiic_stop();
	
	simiic_start();
	send_ch( (dev_add<<1) | 0x01);  //发送器件地址加读位
    while(--num)
    {
        *dat_add = read_ch(ack); //读取数据
        dat_add++;
    }
    *dat_add = read_ch(no_ack); //读取数据
	simiic_stop();
}



