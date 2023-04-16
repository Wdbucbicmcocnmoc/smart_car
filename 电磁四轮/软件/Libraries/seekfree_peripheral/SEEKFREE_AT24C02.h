/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		虚拟示波器协议
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 * @note		    
 ********************************************************************************************************************/

#ifndef _SEEKFREE_AT24C02_H
#define _SEEKFREE_AT24C02_H

#include "common.h"



									//AT24C02模块支持256个8位数据存储
									//该模块使用的是IIC总线控制
#define AT24C02_DEV_ADDR 0xA0>>1	//IIC写入时的地址字节数据，+1为读取
									//AT24C02的地址是可变地址当A0 = 0 A1 = 0 A2 = 0的时候,
									//设备地址位A0，如果需要修改设备地址，请查看AT24C02手册进行修改

void at24c02_write_byte(uint8 byte_reg, uint8 dat);
uint8 at24c02_read_byte(uint8 byte_reg);
void at24c02_write_bytes(uint8 byte_reg, uint8 *dat_add, uint8 num);
void at24c02_read_bytes(uint8 byte_reg, uint8 *dat_add, uint8 num);

#endif 
