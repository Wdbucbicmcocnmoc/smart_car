/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		绝对式编码器
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看LPC546XX_config.h文件内版本宏定义
 * @Software 		MDK FOR C251 V5.60a
 * @Target core		LPC54606J512BD100
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-01-13
 * @note		
					接线定义：
					------------------------------------ 
					模块管脚            单片机管脚
					SCK    			    查看SEEKFREE_ABSOLUTE_ENCODER.H文件ABS_ENCODER_SPI_SCK_PIN 宏定义
					MISO         	    查看SEEKFREE_ABSOLUTE_ENCODER.H文件ABS_ENCODER_SPI_MISO_PIN宏定义
					MOSI                查看SEEKFREE_ABSOLUTE_ENCODER.H文件ABS_ENCODER_SPI_MOSI_PIN宏定义
					CS                  查看SEEKFREE_ABSOLUTE_ENCODER.H文件ABS_ENCODER_SPI_PCS_PIN  宏定义
					------------------------------------  
 ********************************************************************************************************************/

#include "SEEKFREE_ABSOLUTE_ENCODER.h"
#include "zf_spi.h"
#include "zf_delay.h"


//-------------------------以下为软件SPI--------------------------//
//-------------------------以下为软件SPI--------------------------//
//-------------------------以下为软件SPI--------------------------//

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部使用用户无需关心
//  @param      NULL            	
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
void encoder_delay_us(uint16 x)
{
	delay_us(x);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      通过SPI写一个byte,同时读取一个byte
//  @param      byte        发送的数据    
//  @return     uint8       return 返回status状态
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 simspi_wr_byte(uint8 byte)
{
    uint8 i;
    for(i=0; i<8; i++)
    {
        ABS_ENCODER_MOSI(byte & 0x80);
        byte <<= 1;
        ABS_ENCODER_SCK (0);    
      
        ABS_ENCODER_SCK (1);
		byte |= ABS_ENCODER_MISO;  
    }	
    return(byte);                                      		
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      将val写入cmd对应的寄存器地址,同时返回status字节
//  @param      cmd         命令字
//  @param      val         待写入寄存器的数值
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void simspi_w_reg_byte(uint8 cmd, uint8 val)
{
    ABS_ENCODER_CSN (0);
    cmd |= ABS_ENCODER_SPI_W;
    simspi_wr_byte(cmd);                      	
    simspi_wr_byte(val);                               	
    ABS_ENCODER_CSN (1);                                    	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取cmd所对应的寄存器地址
//  @param      cmd         命令字
//  @param      *val        存储读取的数据地址
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void simspi_r_reg_byte(uint8 cmd, uint8 *val)
{
    ABS_ENCODER_CSN (0);
    cmd |= ABS_ENCODER_SPI_R;
    simspi_wr_byte(cmd);                               	
    *val = simspi_wr_byte(0);                           	
    ABS_ENCODER_CSN (1);                                    	
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      写入一个数据到编码器的寄存器
//  @param      cmd         寄存器地址
//  @param      *val        写入数据的地址
//  @return     uint8       0：程序  1：失败
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 encoder_simspi_w_reg_byte(uint8 cmd, uint8 val)
{
	
    uint8 dat;
    ABS_ENCODER_CSN (0);
    cmd |= ABS_ENCODER_SPI_W;
    simspi_wr_byte(cmd);                      	
    simspi_wr_byte(val);                               	
    ABS_ENCODER_CSN (1);   
    encoder_delay_us(1);
    ABS_ENCODER_CSN (0);
    dat = simspi_wr_byte(0x00);                      	
    simspi_wr_byte(0x00);                               	
    ABS_ENCODER_CSN (1);  
    
    if(val != dat)  return 1;   //写入失败
    return 0;                   //写入成功
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取寄存器
//  @param      cmd         寄存器地址
//  @param      *val        存储读取的数据地址
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void encoder_simspi_r_reg_byte(uint8 cmd, uint8 *val)
{
    ABS_ENCODER_CSN (0);
    cmd |= ABS_ENCODER_SPI_R;
    simspi_wr_byte(cmd);                      	
    simspi_wr_byte(0x00);                               	
    ABS_ENCODER_CSN (1);   
	encoder_delay_us(1);
    ABS_ENCODER_CSN (0);
    *val = simspi_wr_byte(0x00);                      	
    simspi_wr_byte(0x00);                               	
    ABS_ENCODER_CSN (1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      设置零偏
//  @param      zero_position  需要设置的零偏
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void set_zero_position_simspi(uint16 zero_position)
{    
    zero_position = (uint16)(4096 - zero_position);
    zero_position = zero_position << 4;
    encoder_simspi_w_reg_byte(ZERO_L_REG,(uint8)zero_position);//设置零位
    encoder_simspi_w_reg_byte(ZERO_H_REG,(uint8)(zero_position>>8));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      写入一个数据到编码器的寄存器
//  @param      void
//  @return     uint16       返回角度值0-4096 对应0-360°
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint16 encoder_angle_simspi(void)
{
    uint16 angle;

    ABS_ENCODER_CSN (0);
    angle = simspi_wr_byte(0x00);      
    angle <<= 8;                    //存储高八位
    angle |= simspi_wr_byte(0x00);  //存储低八位
    ABS_ENCODER_CSN (1);   
    
    return (angle>>4);              //12位精度，因此右移四位                 
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      编码器自检函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void encoder_self4_check(void)
{
    uint8 val;
    do
    {
        encoder_simspi_r_reg_byte(6,&val);
	
        //卡在这里原因有以下几点
        //1 编码器坏了，如果是新的这样的概率极低
        //2 接线错误或者没有接好
    }while(0x1C != val);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      编码器初始化函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void encoder_init_simspi(void)
{
    encoder_self4_check();					//自检
    
    encoder_simspi_w_reg_byte(DIR_REG,0x00);//设置旋转方向 正转数值变小：0x00   反转数值变大：0x80

    set_zero_position_simspi(0);             //设置零偏
}


//-------------------------以上为软件SPI--------------------------//
//-------------------------以上为软件SPI--------------------------//
//-------------------------以上为软件SPI--------------------------//


//-------------------------以下为硬件SPI--------------------------//
//-------------------------以下为硬件SPI--------------------------//
//-------------------------以下为硬件SPI--------------------------//

//-------------------------------------------------------------------------------------------------------------------
//  @brief      通过SPI写一个byte,同时读取一个byte
//  @param      byte        发送的数据    
//  @return     uint8       return 返回status状态
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 spi_wr_byte(uint8 byte)
{  
	byte = spi_mosi(byte);
	return(byte);   
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      将val写入cmd对应的寄存器地址,同时返回status字节
//  @param      cmd         命令字
//  @param      val         待写入寄存器的数值
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void spi_w_reg_byte(uint8 cmd, uint8 val)
{
    ABS_ENCODER_SPI_CSN (0);
    cmd |= ABS_ENCODER_SPI_W;
    spi_wr_byte(cmd);                      	
    spi_wr_byte(val);                               	
    ABS_ENCODER_SPI_CSN (1);       
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取cmd所对应的寄存器地址
//  @param      cmd         命令字
//  @param      *val        存储读取的数据地址
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void spi_r_reg_byte(uint8 cmd, uint8 *val)
{
    ABS_ENCODER_SPI_CSN (0);
    cmd |= ABS_ENCODER_SPI_R;
    spi_wr_byte(cmd);                               	
    *val = simspi_wr_byte(0);                           	
    ABS_ENCODER_SPI_CSN (1);                                    	
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      写入一个数据到编码器的寄存器
//  @param      cmd         寄存器地址
//  @param      *val        写入数据的地址
//  @return     uint8       0：程序  1：失败
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 encoder_spi_w_reg_byte(uint8 cmd, uint8 val)
{
    uint8 dat;
    ABS_ENCODER_SPI_CSN (0);
    cmd |= ABS_ENCODER_SPI_W;
    spi_wr_byte(cmd);                      	
    spi_wr_byte(val);                               	
    ABS_ENCODER_SPI_CSN (1);   
	encoder_delay_us(1);
    ABS_ENCODER_SPI_CSN (0);
    dat = spi_wr_byte(0x00);                      	
    spi_wr_byte(0x00);                               	
    ABS_ENCODER_SPI_CSN (1);  
    
    if(val != dat)  return 1;   //写入失败
    return 0;                   //写入成功
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取寄存器
//  @param      cmd         寄存器地址
//  @param      *val        存储读取的数据地址
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void encoder_spi_r_reg_byte(uint8 cmd, uint8 *val)
{
    ABS_ENCODER_SPI_CSN (0);
    cmd |= ABS_ENCODER_SPI_R;
    spi_wr_byte(cmd);                      	
    spi_wr_byte(0x00);   

    ABS_ENCODER_SPI_CSN (1);   
	encoder_delay_us(1);
    ABS_ENCODER_SPI_CSN (0);
    *val = spi_wr_byte(0x00);                      	
    spi_wr_byte(0x00);                               	
    ABS_ENCODER_SPI_CSN (1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      设置零偏
//  @param      zero_position  需要设置的零偏
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void set_zero_position_spi(uint16 zero_position)
{    
    zero_position = (uint16)(4096 - zero_position);
    zero_position = zero_position << 4;
    encoder_spi_w_reg_byte(ZERO_L_REG,(uint8)zero_position);//设置零位
    encoder_spi_w_reg_byte(ZERO_H_REG,(uint8)(zero_position>>8));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      写入一个数据到编码器的寄存器
//  @param      void
//  @return     uint16       返回角度值0-4096 对应0-360°
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint16 encoder_angle_spi(void)
{
    uint16 angle;
    ABS_ENCODER_SPI_CSN (0);
    angle = (uint16)spi_wr_byte(0x00);      
    angle <<= 8;                    //存储高八位
    angle |= (uint16)spi_wr_byte(0x00);  //存储低八位
    ABS_ENCODER_SPI_CSN (1);   
    
    return (angle>>4);              //12位精度，因此右移四位                 
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      编码器自检函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void encoder_self5_check(void)
{
	uint8 val;
    do
    {
        encoder_spi_r_reg_byte(6,&val);
        //卡在这里原因有以下几点
        //1 编码器坏了，如果是新的这样的概率极低
        //2 接线错误或者没有接好
    }while(0x1C != val);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      编码器初始化函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void encoder_init_spi(void)
{
	spi_init(ABS_ENCODER_SPI_NUM, ABS_ENCODER_SPI_SCK_PIN, ABS_ENCODER_SPI_MOSI_PIN,ABS_ENCODER_SPI_MISO_PIN, 0, MASTER, SPI_SYSclk_DIV_4);

	encoder_self5_check();
	encoder_spi_w_reg_byte(DIR_REG,0x00);//设置旋转方向 正转数值变小：0x00   反转数值变大：0x80
	set_zero_position_spi(0);                   //设置零偏
}


//-------------------------以上为硬件SPI--------------------------//
//-------------------------以上为硬件SPI--------------------------//
//-------------------------以上为硬件SPI--------------------------//
