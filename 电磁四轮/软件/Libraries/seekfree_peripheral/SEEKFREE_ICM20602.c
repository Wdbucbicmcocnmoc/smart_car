/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		ICM20602
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 * @note		
					接线定义：
					------------------------------------ 

					------------------------------------ 
 ********************************************************************************************************************/


#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_IIC.h"
#include "zf_delay.h"
#include "zf_spi.h"

int16 icm_gyro_x,icm_gyro_y,icm_gyro_z;
int16 icm_acc_x,icm_acc_y,icm_acc_z;



//-------------------------------------------------------------------------------------------------------------------
//  以下函数是使用软件IIC通信，相比较硬件IIC，软件IIC引脚更加灵活，可以使用任意普通IO
//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ICM20602自检函数
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void icm20602_self1_check(void)
{
    uint8 dat;
	dat = simiic_read_reg(ICM20602_DEV_ADDR,ICM20602_WHO_AM_I,SIMIIC);
    while(0x12 != dat)   //读取ICM20602 ID
    {
        dat = simiic_read_reg(ICM20602_DEV_ADDR,ICM20602_WHO_AM_I,SIMIIC);
        delay_ms(10);
        //卡在这里原因有以下几点
        //1 ICM20602坏了，如果是新的这样的概率极低
        //2 接线错误或者没有接好
        //3 可能你需要外接上拉电阻，上拉到3.3V
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      软件IIC，初始化ICM20602
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void icm20602_init_simiic(void)
{
    delay_ms(10);  //上电延时

    //检测
    icm20602_self1_check();

    //复位
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_PWR_MGMT_1,0x80);               //复位设备
    delay_ms(2);                                                        //延时
    while(0x80 & simiic_read_reg(ICM20602_DEV_ADDR,ICM20602_PWR_MGMT_1,SIMIIC));//等待复位完成

    //配置参数
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_PWR_MGMT_1,0x01);               //时钟设置
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_PWR_MGMT_2,0x00);               //开启陀螺仪和加速度计
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_CONFIG,0x01);                   //176HZ 1KHZ
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_SMPLRT_DIV,0x07);               //采样速率 SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_GYRO_CONFIG,0x18);              //±2000 dps
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_ACCEL_CONFIG,0x10);             //±8g
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_ACCEL_CONFIG_2,0x03);           //Average 4 samples   44.8HZ   //0x23 Average 16 samples
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602加速度计数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_accdata_simiic(void)
{
    uint8 dat[6];

    simiic_read_regs(ICM20602_DEV_ADDR, ICM20602_ACCEL_XOUT_H, dat, 6, SIMIIC);
    icm_acc_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
    icm_acc_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
    icm_acc_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602陀螺仪数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_gyro_simiic(void)
{
    uint8 dat[6];

    simiic_read_regs(ICM20602_DEV_ADDR, ICM20602_GYRO_XOUT_H, dat, 6, SIMIIC);
    icm_gyro_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
    icm_gyro_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
    icm_gyro_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}




//-------------------------------------------------------------------------------------------------------------------
//  以下函数是使用软件SPI通信，相比较硬件SPI，软件SPI引脚更加灵活，可以使用任意普通IO
//-------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------
//  @brief      通过SPI写一个byte,同时读取一个byte
//  @param      byte        发送的数据    
//  @return     uint8       return 返回status状态
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 icm_simspi_wr_byte(uint8 byte)
{
    uint8 i;
	
    for(i=0; i<8; i++)
    {
        ICM20602_MOSI(byte&0x80);
        byte <<= 1;
		ICM20602_SCK (0);
		
        ICM20602_SCK (1);
		byte |= ICM20602_MISO; 
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
void icm_simspi_w_reg_byte(uint8 cmd, uint8 val)
{
    ICM20602_CSN (0);
    cmd |= ICM20602_SPI_W;
    icm_simspi_wr_byte(cmd);                      	
    icm_simspi_wr_byte(val);                               	
    ICM20602_CSN (1);                                    	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取cmd所对应的寄存器地址
//  @param      cmd         命令字
//  @param      *val        存储读取的数据地址
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void icm_simspi_r_reg_byte(uint8 cmd, uint8 *val)
{
    ICM20602_CSN (0);
    cmd |= ICM20602_SPI_R;
    icm_simspi_wr_byte(cmd);                               	
    *val = icm_simspi_wr_byte(0);                           	
    ICM20602_CSN (1);                                    	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      读取cmd所对应的寄存器地址
//  @param      cmd         命令字
//  @param      *val        存储读取的数据地址
//  @param      num         读取的数量
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void icm_simspi_r_reg_bytes(uint8 cmd, uint8 *val, uint8 num)
{
    uint16 i;
    ICM20602_CSN (0);
    cmd |= ICM20602_SPI_R;
    icm_simspi_wr_byte(cmd);
	
	for(i=0; i<num; i++)	
		val[i] = icm_simspi_wr_byte(0);    

	
    ICM20602_CSN (1);                                    		
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ICM20602自检函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void icm20602_self4_check(void)
{
    uint8 val;
    do
    {
        icm_simspi_r_reg_byte(ICM20602_WHO_AM_I,&val);
		
        //卡在这里原因有以下几点
        //1 ICM20602坏了，如果是新的这样的概率极低
        //2 接线错误或者没有接好
        //3 可能你需要外接上拉电阻，上拉到3.3V
    }while(0x12 != val);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      软件SPI，初始化ICM20602
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void icm20602_init_simspi(void)
{
    uint8 val;

    icm20602_self4_check();//检测
    
    icm_simspi_w_reg_byte(ICM20602_PWR_MGMT_1,0x80);//复位设备
    delay_ms(2);
    do
    {//等待复位成功
        icm_simspi_r_reg_byte(ICM20602_PWR_MGMT_1,&val);
    }while(0x41 != val);
    
    icm_simspi_w_reg_byte(ICM20602_PWR_MGMT_1,     0x01);            //时钟设置
    icm_simspi_w_reg_byte(ICM20602_PWR_MGMT_2,     0x00);            //开启陀螺仪和加速度计
    icm_simspi_w_reg_byte(ICM20602_CONFIG,         0x01);            //176HZ 1KHZ
    icm_simspi_w_reg_byte(ICM20602_SMPLRT_DIV,     0x07);            //采样速率 SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
    icm_simspi_w_reg_byte(ICM20602_GYRO_CONFIG,    0x18);            //±2000 dps
    icm_simspi_w_reg_byte(ICM20602_ACCEL_CONFIG,   0x10);            //±8g
    icm_simspi_w_reg_byte(ICM20602_ACCEL_CONFIG_2, 0x03);            //Average 8 samples   44.8HZ
    
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602加速度计数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_accdata_simspi(void)
{
    uint8 dat[6];

    
    icm_simspi_r_reg_bytes(ICM20602_ACCEL_XOUT_H, dat, 6);
    icm_acc_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
    icm_acc_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
    icm_acc_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602陀螺仪数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_gyro_simspi(void)
{
    uint8 dat[6];
    
    icm_simspi_r_reg_bytes(ICM20602_GYRO_XOUT_H, dat, 6);

    icm_gyro_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
    icm_gyro_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
    icm_gyro_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}
