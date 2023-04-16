/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-11-15
 * @note		
					接线定义：
					------------------------------------ 
					1.14寸IPS模块管脚       单片机管脚
					SCL                 	查看SEEKFREE_IPS114_SPI.h文件内的IPS114_SCL		宏定义     硬件SPI引脚不可随意切换
					SDA                 	查看SEEKFREE_IPS114_SPI.h文件内的IPS114_SDA		宏定义     硬件SPI引脚不可随意切换
					RES                 	查看SEEKFREE_IPS114_SPI.h文件内的IPS114_REST_PIN宏定义    
					DC                  	查看SEEKFREE_IPS114_SPI.h文件内的IPS114_DC_PIN	宏定义  
					CS                  	查看SEEKFREE_IPS114_SPI.h文件内的IPS114_CS		宏定义     硬件SPI引脚不可随意切换
					BL  					查看SEEKFREE_IPS114_SPI.h文件内的IPS114_BL_PIN	宏定义
					
					电源引脚
					VCC 3.3V电源
					GND 电源地
					最大分辨率135*240
					------------------------------------ 
 ********************************************************************************************************************/
 


#ifndef _SEEKFREE_IPS114_H
#define _SEEKFREE_IPS114_H

#include "common.h"
#include "board.h"

//--------------------软件SPI--------------------


#define	IPS114_SCL_SIMSPI_PIN 		P25		//定义SPI_SCK引脚
#define	IPS114_SDA_SIMSPI_PIN		P23   	//定义SPI_MOSI引脚
#define IPS114_REST_SIMSPI_PIN  	P20
#define IPS114_DC_SIMSPI_PIN 	 	P21   	//液晶命令位引脚定义
#define IPS114_CS_SIMSPI_PIN    	P22   	//定义SPI_CS引脚
#define IPS114_BL_SIMSPI_PIN    	P27     //液晶背光引脚定义 
	


#define IPS114_SCL_SIMSPI(x)	   (IPS114_SCL_SIMSPI_PIN = x)
#define IPS114_SDA_SIMSPI(x)	   (IPS114_SDA_SIMSPI_PIN = x)
#define IPS114_REST_SIMSPI(x)      (IPS114_REST_SIMSPI_PIN = x)
#define IPS114_DC_SIMSPI(x)        (IPS114_DC_SIMSPI_PIN = x)
#define IPS114_CS_SIMSPI(x)        (IPS114_CS_SIMSPI_PIN = x)
#define IPS114_BL_SIMSPI(x)        (IPS114_BL_SIMSPI_PIN = x)


//--------------------硬件SPI--------------------


#define IPS114_SPIN_PIN     SPI_CH2           //定义使用的SPI号
#define	IPS114_SCL_PIN 		SPI_CH2_SCLK_P25	//定义SPI_SCK引脚
#define	IPS114_SDA_PIN		SPI_CH2_MOSI_P23   //定义SPI_MOSI引脚
#define	IPS114_SDA_IN_PIN	SPI_CH2_MISO_P24   //定义SPI_MISO引脚  IPS屏幕没有MISO引脚，但是这里任然需要定义，在spi的初始化时需要使用
#define IPS114_REST_PIN  	P20
#define IPS114_DC_PIN 	 	P21   	//液晶命令位引脚定义
#define IPS114_CS_PIN    	P22   	//定义SPI_CS引脚
#define IPS114_BL_PIN    	P27     //液晶背光引脚定义 


#define IPS114_REST(x)      (IPS114_REST_PIN = x)
#define IPS114_DC(x)        (IPS114_DC_PIN = x)
#define IPS114_CS(x)        (IPS114_CS_PIN = x)
#define IPS114_BL(x)        (IPS114_BL_PIN = x)

//-----------------------------------------------    


//-------常用颜色在SEEKFREE_FONT.h文件中定义----------
//#define RED          	    0xF800	//红色
//#define BLUE         	    0x001F  //蓝色
//#define YELLOW       	    0xFFE0	//黄色
//#define GREEN        	    0x07E0	//绿色
//#define WHITE        	    0xFFFF	//白色
//#define BLACK        	    0x0000	//黑色 
//#define GRAY  			0X8430 	//灰色
//#define BROWN 			0XBC40 	//棕色
//#define PURPLE    		0XF81F	//紫色
//#define PINK    		    0XFE19	//粉色


//定义写字笔的颜色
#define IPS114_PENCOLOR    RED

//定义背景颜色
#define IPS114_BGCOLOR     WHITE



#define IPS114_W   135
#define IPS114_H   240

//定义显示方向
//0 竖屏模式
//1 竖屏模式  旋转180
//2 横屏模式
//3 横屏模式  旋转180
#define IPS114_DISPLAY_DIR 3

#if (0==IPS114_DISPLAY_DIR || 1==IPS114_DISPLAY_DIR)
#define	IPS114_X_MAX	IPS114_W	//液晶X方宽度
#define IPS114_Y_MAX	IPS114_H    //液晶Y方宽度
     
#elif (2==IPS114_DISPLAY_DIR || 3==IPS114_DISPLAY_DIR)
#define	IPS114_X_MAX	IPS114_H	//液晶X方宽度
#define IPS114_Y_MAX	IPS114_W    //液晶Y方宽度
     
#else
#error "IPS114_DISPLAY_DIR 定义错误"
     
#endif

//--------------------软件SPI--------------------

void ips114_init_simspi(void);
void ips114_clear_simspi(uint16 color);
void ips114_drawpoint_simspi(uint16 x,uint16 y,uint16 color);
void ips114_showchar_simspi(uint16 x,uint16 y,const int8 dat);
void ips114_showstr_simspi(uint16 x,uint16 y,const int8 dat[]);
void ips114_showint8_simspi(uint16 x,uint16 y,int8 dat);
void ips114_showuint8_simspi(uint16 x,uint16 y,uint8 dat);
void ips114_showint16_simspi(uint16 x,uint16 y,int16 dat);
void ips114_showuint16_simspi(uint16 x,uint16 y,uint16 dat);
void ips114_showint32_simspi(uint16 x,uint16 y,int32 dat,uint8 num);
void ips114_showfloat_simspi(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum);

//--------------------硬件SPI--------------------

void ips114_init(void);
void ips114_clear(uint16 color);
void ips114_drawpoint(uint16 x,uint16 y,uint16 color);
void ips114_showchar(uint16 x,uint16 y,const int8 dat);
void ips114_showstr(uint16 x,uint16 y,const int8 dat[]);
void ips114_showint8(uint16 x,uint16 y,int8 dat);
void ips114_showuint8(uint16 x,uint16 y,uint8 dat);
void ips114_showint16(uint16 x,uint16 y,int16 dat);
void ips114_showuint16(uint16 x,uint16 y,uint16 dat);
void ips114_showint32(uint16 x,uint16 y,int32 dat,uint8 num);
void ips114_showfloat(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum);


//-----------------------------------------------    


#endif
