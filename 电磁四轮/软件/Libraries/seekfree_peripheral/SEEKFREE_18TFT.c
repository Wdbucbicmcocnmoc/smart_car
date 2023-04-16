/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		TFT
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2018-05-24
 * @note		
					接线定义：
					------------------------------------ 
					模块管脚            单片机管脚
					SCL                 查看TFT_SCL宏定义的引脚     硬件SPI引脚不可随意切换
					SDA                 查看TFT_SDA宏定义的引脚     硬件SPI引脚不可随意切换
					RES                 查看REST_PIN宏定义的引脚    
					DC                  查看DC_PIN宏定义的引脚  
					CS                  查看TFT_CS宏定义的引脚      硬件SPI引脚不可随意切换
					
					电源引脚
					BL  3.3V电源（背光控制引脚，也可以接PWM来控制亮度）
					VCC 3.3V电源
					GND 电源地
					最大分辨率128*160
					------------------------------------ 

 ********************************************************************************************************************/





#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_FONT.h"
#include "SEEKFREE_PRINTF.h"
#include "zf_spi.h"
#include "zf_delay.h"

//-------------------------------------------------------------------------------------------------------------------
//  以下函数是使用软件SPI通信，相比较硬件SPI，软件SPI引脚更加灵活，可以使用任意普通IO
//-------------------------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeIndex_simspi(uint8 dat)			//写命令
{	
	uint8 i=8;
	
    TFT_CS_SIMSPI(0);
	TFT_DC_SIMSPI(0);
	TFT_SCL_SIMSPI(0);
	
	while(i--)
	{
		if(dat&0x80){TFT_SDA_SIMSPI(1);}
		else{TFT_SDA_SIMSPI(0);}
		TFT_SCL_SIMSPI(1);
		
		TFT_SCL_SIMSPI(0);
		dat<<=1;
	}	
    TFT_CS_SIMSPI(1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeData_simspi(uint8 dat)			//写数据
{
    uint8 i=8;
	
    TFT_CS_SIMSPI(0);
	TFT_DC_SIMSPI(1);
	TFT_SCL_SIMSPI(0);
	while(i--)
	{
	  	if(dat&0x80){TFT_SDA_SIMSPI(1);}
	  	else{TFT_SDA_SIMSPI(0);}
	  	TFT_SCL_SIMSPI(1);
		
	  	TFT_SCL_SIMSPI(0);
	  	dat<<=1;
	}
    TFT_CS_SIMSPI(1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeData_16bit_simspi(uint16 dat)	//向液晶屏写一个16位数据
{
	uint8 i=16;
	
    TFT_CS_SIMSPI(0);
    TFT_DC_SIMSPI(1);
    TFT_SCL_SIMSPI(0);
	
	while(i--)
	{
	  	if(dat&0x8000){TFT_SDA_SIMSPI(1);}
	  	else{TFT_SDA_SIMSPI(0);}
	  	TFT_SCL_SIMSPI(1);
		
	  	TFT_SCL_SIMSPI(0);
	  	dat<<=1;
	}
	
    TFT_CS_SIMSPI(1);

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶坐标设置
//  @param      x_start     	坐标x方向的起点
//  @param      y_start     	坐标y方向的起点
//  @param      x_end       	坐标x方向的终点
//  @param      y_end       	坐标y方向的终点
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_set_region(0,0,10,10);// x、y的起点都是0，终点都是10
//-------------------------------------------------------------------------------------------------------------------
void lcd_set_region_simspi(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end)
{	

    
#if (0 == TFT_DISPLAY_DIR || 1 == TFT_DISPLAY_DIR)
    lcd_writeIndex_simspi(0x2a);
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(x_start+2));
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(x_end+2));

	lcd_writeIndex_simspi(0x2b);
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(y_start+1));
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(y_end+1));	

#elif(2 == TFT_DISPLAY_DIR || 3 == TFT_DISPLAY_DIR)
    lcd_writeIndex_simspi(0x2a);
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(x_start+1);
	lcd_writeData_simspi(0x0);
	lcd_writeData_simspi((uint8)(x_end+1)));

	lcd_writeIndex_simspi(0x2b);
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(y_start+2));
	lcd_writeData_simspi(0x00);
	lcd_writeData_simspi((uint8)(y_end+2));	

#endif
    
    lcd_writeIndex_simspi(0x2c);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶清屏函数
//  @param      color     		颜色设置
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_clear(YELLOW);// 全屏设置为黄色
//-------------------------------------------------------------------------------------------------------------------
void lcd_clear_simspi(int color)
{
 	uint8 i,j;
	lcd_set_region_simspi(0,0,TFT_X_MAX-1,TFT_Y_MAX-1);
 	for (i=0;i<TFT_Y_MAX;i++)
    	for (j=0;j<TFT_X_MAX;j++)
        	lcd_writeData_16bit_simspi(color);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶初始化
//  @return     void
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_init_simspi(void)
{	
	
	
    TFT_REST_SIMSPI(0);
    delay_ms(10);
    TFT_REST_SIMSPI(1);
    delay_ms(120);
    lcd_writeIndex_simspi(0x11);
    delay_ms(120);

    lcd_writeIndex_simspi(0xB1); 
    lcd_writeData_simspi(0x01); 
    lcd_writeData_simspi(0x2C); 
    lcd_writeData_simspi(0x2D); 
    
    lcd_writeIndex_simspi(0xB2); 
    lcd_writeData_simspi(0x01); 
    lcd_writeData_simspi(0x2C); 
    lcd_writeData_simspi(0x2D); 
    
    lcd_writeIndex_simspi(0xB3); 
    lcd_writeData_simspi(0x01); 
    lcd_writeData_simspi(0x2C); 
    lcd_writeData_simspi(0x2D); 
    lcd_writeData_simspi(0x01); 
    lcd_writeData_simspi(0x2C); 
    lcd_writeData_simspi(0x2D); 
    
    lcd_writeIndex_simspi(0xB4);
    lcd_writeData_simspi(0x07); 

    lcd_writeIndex_simspi(0xC0); 
    lcd_writeData_simspi(0xA2); 
    lcd_writeData_simspi(0x02); 
    lcd_writeData_simspi(0x84); 
    lcd_writeIndex_simspi(0xC1); 
    lcd_writeData_simspi(0xC5); 
    
    lcd_writeIndex_simspi(0xC2); 
    lcd_writeData_simspi(0x0A); 
    lcd_writeData_simspi(0x00); 
    
    lcd_writeIndex_simspi(0xC3); 
    lcd_writeData_simspi(0x8A); 
    lcd_writeData_simspi(0x2A); 
    lcd_writeIndex_simspi(0xC4); 
    lcd_writeData_simspi(0x8A); 
    lcd_writeData_simspi(0xEE); 
    
    lcd_writeIndex_simspi(0xC5);
    lcd_writeData_simspi(0x0E); 
    
    lcd_writeIndex_simspi(0x36);
    switch(TFT_DISPLAY_DIR)//y x v
    {
        case 0: lcd_writeData_simspi(1<<7 | 1<<6 | 0<<5);  break;  //竖屏模式
        case 1: lcd_writeData_simspi(0<<7 | 0<<6 | 0<<5);  break;  //竖屏模式  旋转180
        case 2: lcd_writeData_simspi(1<<7 | 0<<6 | 1<<5);  break;  //横屏模式
        case 3: lcd_writeData_simspi(0<<7 | 1<<6 | 1<<5);  break;  //横屏模式  旋转180
    }

    lcd_writeIndex_simspi(0xe0); 
    lcd_writeData_simspi(0x0f); 
    lcd_writeData_simspi(0x1a); 
    lcd_writeData_simspi(0x0f); 
    lcd_writeData_simspi(0x18); 
    lcd_writeData_simspi(0x2f); 
    lcd_writeData_simspi(0x28); 
    lcd_writeData_simspi(0x20); 
    lcd_writeData_simspi(0x22); 
    lcd_writeData_simspi(0x1f); 
    lcd_writeData_simspi(0x1b); 
    lcd_writeData_simspi(0x23); 
    lcd_writeData_simspi(0x37); 
    lcd_writeData_simspi(0x00); 	
    lcd_writeData_simspi(0x07); 
    lcd_writeData_simspi(0x02); 
    lcd_writeData_simspi(0x10); 
    
    lcd_writeIndex_simspi(0xe1); 
    lcd_writeData_simspi(0x0f); 
    lcd_writeData_simspi(0x1b); 
    lcd_writeData_simspi(0x0f); 
    lcd_writeData_simspi(0x17); 
    lcd_writeData_simspi(0x33); 
    lcd_writeData_simspi(0x2c); 
    lcd_writeData_simspi(0x29); 
    lcd_writeData_simspi(0x2e); 
    lcd_writeData_simspi(0x30); 
    lcd_writeData_simspi(0x30); 
    lcd_writeData_simspi(0x39); 
    lcd_writeData_simspi(0x3f); 
    lcd_writeData_simspi(0x00); 
    lcd_writeData_simspi(0x07); 
    lcd_writeData_simspi(0x03); 
    lcd_writeData_simspi(0x10);  
    
    lcd_writeIndex_simspi(0x2a);
    lcd_writeData_simspi(0x00);
    lcd_writeData_simspi(0x00+2);
    lcd_writeData_simspi(0x00);
    lcd_writeData_simspi(0x80+2);
    
    lcd_writeIndex_simspi(0x2b);
    lcd_writeData_simspi(0x00);
    lcd_writeData_simspi(0x00+3);
    lcd_writeData_simspi(0x00);
    lcd_writeData_simspi(0x80+3);
    
    lcd_writeIndex_simspi(0xF0); 
    lcd_writeData_simspi(0x01); 
    lcd_writeIndex_simspi(0xF6);
    lcd_writeData_simspi(0x00); 
    
    lcd_writeIndex_simspi(0x3A);
    lcd_writeData_simspi(0x05); 
    lcd_writeIndex_simspi(0x29);

    lcd_clear_simspi(WHITE);//全白
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶画点
//  @param      x     	        坐标x方向的起点
//  @param      y     	        坐标y方向的起点
//  @param      dat       	    需要显示的颜色
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_drawpoint(0,0,RED);  //坐标0,0画一个红色的点
//-------------------------------------------------------------------------------------------------------------------
void lcd_drawpoint_simspi(uint16 x,uint16 y,uint16 color)
{
    lcd_set_region_simspi(x,y,x,y);
    lcd_writeData_16bit_simspi(color);
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示字符
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的字符
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showchar(0,0,'x');//坐标0,0写一个字符x
//-------------------------------------------------------------------------------------------------------------------
void lcd_showchar_simspi(uint16 x,uint16 y,const int8 dat)
{
	uint8 i,j;
	uint8 temp;
    
	for(i=0; i<16; i++)
	{
		lcd_set_region_simspi(x,y+i,x+7,y+i);
		temp = tft_ascii[dat-32][i];//减32因为是取模是从空格开始取得 空格在ascii中序号是32
		for(j=0; j<8; j++)
		{
			if(temp&0x01)	lcd_writeData_16bit_simspi(TFT_PENCOLOR);
			else			lcd_writeData_16bit_simspi(TFT_BGCOLOR);
			temp>>=1;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示字符串
//  @param      x     	        坐标x方向的起点  参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点  参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的字符串
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showstr(0,0,"seekfree");
//-------------------------------------------------------------------------------------------------------------------
void lcd_showstr_simspi(uint16 x,uint16 y,const int8 dat[])
{
	uint16 j;
	
	j = 0;
	while(dat[j] != '\0')
	{
		lcd_showchar_simspi(x+8*j,y*16,dat[j]);
		j++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示8位有符号
//  @param      x     	        坐标x方向的起点  参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点  参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型int8
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showint8(0,0,x);//x为int8类型
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint8_simspi(uint16 x,uint16 y,int8 dat)
{
	uint8 a[3];
	uint8 i;
	if(dat<0)
	{
		lcd_showchar_simspi(x,y*16,'-');
		dat = -dat;
	}
	else	lcd_showchar_simspi(x,y*16,' ');
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		lcd_showchar_simspi((uint8)(x+(8*(i+1))), (uint8)(y*16),(int8)('0' + a[i]));
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示8位无符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint8
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint8(0,0,x);//x为uint8类型
//-------------------------------------------------------------------------------------------------------------------
void lcd_showuint8_simspi(uint16 x,uint16 y,uint8 dat)
{
	uint8 a[3];
	uint8 i;
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		lcd_showchar_simspi((uint8)(x+(8*(i+1))), (uint8)(y*16),(int8)('0' + a[i]));
		i++;
	}
	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示16位有符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型int16
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showint16(0,0,x);//x为int16类型
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint16_simspi(uint16 x,uint16 y,int16 dat)
{
	uint8 a[5];
	uint8 i;
	if(dat<0)
	{
		lcd_showchar_simspi(x,y*16,'-');
		dat = -dat;
	}
	else	lcd_showchar_simspi(x,y*16,' ');

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		lcd_showchar_simspi((uint8)(x+(8*(i+1))), (uint8)(y*16),(int8)('0' + a[i]));
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示16位无符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint16
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint16(0,0,x);//x为uint16类型
//-------------------------------------------------------------------------------------------------------------------
void lcd_showuint16_simspi(uint16 x,uint16 y,uint16 dat)
{
	uint8 a[5];
	uint8 i;

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		lcd_showchar_simspi((uint8)(x+(8*(i+1))), (uint8)(y*16),(int8)('0' + a[i]));
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示32位有符号(去除整数部分无效的0)
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint32
//  @param      num       	    需要显示的位数 最高10位  不包含正负号
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint32(0,0,x,3);//x可以为int32 uint16 int16 uint8 int8类型
//  Sample usage:               负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint32_simspi(uint16 x,uint16 y,int32 dat,uint8 num)
{
    int8    buff[34];
    uint8   length;
    
    if(10<num)      num = 10;
    
    num++;
    if(0>dat)   length = zf_sprintf( &buff[0],"%d",dat);//负数
    else
    {
        buff[0] = ' ';
        length = zf_sprintf( &buff[1],"%d",dat);
        length++;
    }
    while(length < num)
    {
        buff[length] = ' ';
        length++;
    }
    buff[num] = '\0';

    lcd_showstr_simspi(x, y, buff);	//显示数字
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示浮点数(去除整数部分无效的0)
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型float或double
//  @param      num       	    整数位显示长度   最高10位  
//  @param      pointnum        小数位显示长度   最高6位
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showfloat(0,0,x,2,3);//显示浮点数   整数显示2位   小数显示三位
//  @note                       特别注意当发现小数部分显示的值与你写入的值不一样的时候，
//                              可能是由于浮点数精度丢失问题导致的，这并不是显示函数的问题，
//                              有关问题的详情，请自行百度学习   浮点数精度丢失问题。
//                              负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void lcd_showfloat_simspi(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum)
{
    uint8   length;
	int8    buff[34];
	int8    start,end,point;

	if(6<pointnum)  pointnum = 6;
    if(10<num)      num = 10;
        
    if(0>dat)   length = zf_sprintf( &buff[0],"%f",dat);//负数
    else
    {
        length = zf_sprintf( &buff[1],"%f",dat);
        length++;
    }
    point = length - 7;         //计算小数点位置
    start = point - num - 1;    //计算起始位
    end = point + pointnum + 1; //计算结束位
    while(0>start)//整数位不够  末尾应该填充空格
    {
        buff[end] = ' ';
        end++;
        start++;
    }
    
    if(0>dat)   buff[start] = '-';
    else        buff[start] = ' ';
    
    buff[end] = '\0';

    lcd_showstr_simspi(x, y, buff);	//显示数字
}


//-------------------------------------------------------------------------------------------------------------------
//  以下函数是使用硬件SPI通信，相比较软件IIC，速度比软件IIC快。
//-------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeIndex(uint8 dat)			//写命令
{	
	
    TFT_CS(0);
	TFT_DC(0);
	spi_mosi(dat);
    TFT_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writeData(uint8 dat)			//写数据
{
    TFT_CS(0);
	TFT_DC(1);
	spi_mosi(dat);
    TFT_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      内部调用，用户无需关心
//  @param      void 		    
//  @return     				
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_writedata_16bit(uint16 dat)	//向液晶屏写一个16位数据
{

    uint8 dat1[2];
    dat1[0] = dat >> 8;
    dat1[1] = (uint8)dat;
	
    TFT_CS(0);
    TFT_DC(1);
	spi_mosi(dat1[0]);
	spi_mosi(dat1[1]);
    TFT_CS(1);

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶坐标设置
//  @param      x_start     	坐标x方向的起点
//  @param      y_start     	坐标y方向的起点
//  @param      x_end       	坐标x方向的终点
//  @param      y_end       	坐标y方向的终点
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_set_region(0,0,10,10);// x、y的起点都是0，终点都是10
//-------------------------------------------------------------------------------------------------------------------
void lcd_set_region(unsigned int x_start,unsigned int y_start,unsigned int x_end,unsigned int y_end)
{	

    
#if (0 == TFT_DISPLAY_DIR || 1 == TFT_DISPLAY_DIR)
    lcd_writeIndex(0x2a);
	lcd_writeData(0x00);
	lcd_writeData((uint8)(x_start+2));
	lcd_writeData(0x00);
	lcd_writeData((uint8)(x_end+2));

	lcd_writeIndex(0x2b);
	lcd_writeData(0x00);
	lcd_writeData((uint8)(y_start+1));
	lcd_writeData(0x00);
	lcd_writeData((uint8)(y_end+1));	

#elif(2 == TFT_DISPLAY_DIR || 3 == TFT_DISPLAY_DIR)
    lcd_writeIndex(0x2a);
	lcd_writeData(0x00);
	lcd_writeData((uint8)(x_start+1));
	lcd_writeData(0x0);
	lcd_writeData((uint8)(x_end+1));

	lcd_writeIndex(0x2b);
	lcd_writeData(0x00);
	lcd_writeData((uint8)(y_start+2));
	lcd_writeData(0x00);
	lcd_writeData((uint8)(y_end+2));	

#endif
    
    lcd_writeIndex(0x2c);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶清屏函数
//  @param      color     		颜色设置
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_clear(YELLOW);// 全屏设置为黄色
//-------------------------------------------------------------------------------------------------------------------
void lcd_clear(int color)
{
 	uint8 i,j;
	lcd_set_region(0,0,TFT_X_MAX-1,TFT_Y_MAX-1);
 	for (i=0;i<TFT_Y_MAX;i++)
    	for (j=0;j<TFT_X_MAX;j++)
        	lcd_writedata_16bit(color);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶初始化
//  @return     void
//  @since      v1.0
//  Sample usage:               
//-------------------------------------------------------------------------------------------------------------------
void lcd_init(void)
{	
	spi_init(TFT_SPIN, TFT_SCL_PIN, TFT_SDA_PIN, TFT_SDA_IN_PIN, 0, MASTER, SPI_SYSclk_DIV_4);

    TFT_REST(0);
    delay_ms(10);
    TFT_REST(1);
    delay_ms(120);
    lcd_writeIndex(0x11);
    delay_ms(120);

    lcd_writeIndex(0xB1); 
    lcd_writeData(0x01); 
    lcd_writeData(0x2C); 
    lcd_writeData(0x2D); 
    
    lcd_writeIndex(0xB2); 
    lcd_writeData(0x01); 
    lcd_writeData(0x2C); 
    lcd_writeData(0x2D); 
    
    lcd_writeIndex(0xB3); 
    lcd_writeData(0x01); 
    lcd_writeData(0x2C); 
    lcd_writeData(0x2D); 
    lcd_writeData(0x01); 
    lcd_writeData(0x2C); 
    lcd_writeData(0x2D); 
    
    lcd_writeIndex(0xB4);
    lcd_writeData(0x07); 

    lcd_writeIndex(0xC0); 
    lcd_writeData(0xA2); 
    lcd_writeData(0x02); 
    lcd_writeData(0x84); 
    lcd_writeIndex(0xC1); 
    lcd_writeData(0xC5); 
    
    lcd_writeIndex(0xC2); 
    lcd_writeData(0x0A); 
    lcd_writeData(0x00); 
    
    lcd_writeIndex(0xC3); 
    lcd_writeData(0x8A); 
    lcd_writeData(0x2A); 
    lcd_writeIndex(0xC4); 
    lcd_writeData(0x8A); 
    lcd_writeData(0xEE); 
    
    lcd_writeIndex(0xC5);
    lcd_writeData(0x0E); 
    
    lcd_writeIndex(0x36);
	
	#if(0 == TFT_DISPLAY_DIR)
		lcd_writeData(1<<7 | 1<<6 | 0<<5);
	#elif(1 == TFT_DISPLAY_DIR)
		lcd_writeData(0<<7 | 0<<6 | 0<<5);
	#elif(2 == TFT_DISPLAY_DIR)
		lcd_writeData(1<<7 | 0<<6 | 1<<5);
	#else
		lcd_writeData(0<<7 | 1<<6 | 1<<5);
	#endif
	
    lcd_writeIndex(0xe0); 
    lcd_writeData(0x0f); 
    lcd_writeData(0x1a); 
    lcd_writeData(0x0f); 
    lcd_writeData(0x18); 
    lcd_writeData(0x2f); 
    lcd_writeData(0x28); 
    lcd_writeData(0x20); 
    lcd_writeData(0x22); 
    lcd_writeData(0x1f); 
    lcd_writeData(0x1b); 
    lcd_writeData(0x23); 
    lcd_writeData(0x37); 
    lcd_writeData(0x00); 	
    lcd_writeData(0x07); 
    lcd_writeData(0x02); 
    lcd_writeData(0x10); 
    
    lcd_writeIndex(0xe1); 
    lcd_writeData(0x0f); 
    lcd_writeData(0x1b); 
    lcd_writeData(0x0f); 
    lcd_writeData(0x17); 
    lcd_writeData(0x33); 
    lcd_writeData(0x2c); 
    lcd_writeData(0x29); 
    lcd_writeData(0x2e); 
    lcd_writeData(0x30); 
    lcd_writeData(0x30); 
    lcd_writeData(0x39); 
    lcd_writeData(0x3f); 
    lcd_writeData(0x00); 
    lcd_writeData(0x07); 
    lcd_writeData(0x03); 
    lcd_writeData(0x10);  
    
    lcd_writeIndex(0x2a);
    lcd_writeData(0x00);
    lcd_writeData(0x00+2);
    lcd_writeData(0x00);
    lcd_writeData(0x80+2);
    
    lcd_writeIndex(0x2b);
    lcd_writeData(0x00);
    lcd_writeData(0x00+3);
    lcd_writeData(0x00);
    lcd_writeData(0x80+3);
    
    lcd_writeIndex(0xF0); 
    lcd_writeData(0x01); 
    lcd_writeIndex(0xF6);
    lcd_writeData(0x00); 
    
    lcd_writeIndex(0x3A);
    lcd_writeData(0x05); 
    lcd_writeIndex(0x29);

    lcd_clear(WHITE);//全白
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶画点
//  @param      x     	        坐标x方向的起点
//  @param      y     	        坐标y方向的起点
//  @param      dat       	    需要显示的颜色
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_drawpoint(0,0,RED);  //坐标0,0画一个红色的点
//-------------------------------------------------------------------------------------------------------------------
void lcd_drawpoint(uint16 x,uint16 y,uint16 color)
{
    lcd_set_region(x,y,x,y);
    lcd_writedata_16bit(color);
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示字符
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的字符
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showchar(0,0,'x');//坐标0,0写一个字符x
//-------------------------------------------------------------------------------------------------------------------
void lcd_showchar(uint16 x,uint16 y,const int8 dat)
{
	uint8 i,j;
	uint8 temp;
    
	for(i=0; i<16; i++)
	{
		lcd_set_region(x,y+i,x+7,y+i);
		temp = tft_ascii[dat-32][i];//减32因为是取模是从空格开始取得 空格在ascii中序号是32
		for(j=0; j<8; j++)
		{
			if(temp&0x01)	lcd_writedata_16bit(TFT_PENCOLOR);
			else			lcd_writedata_16bit(TFT_BGCOLOR);
			temp>>=1;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示字符串
//  @param      x     	        坐标x方向的起点  参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点  参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的字符串
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showstr(0,0,"seekfree");
//-------------------------------------------------------------------------------------------------------------------
void lcd_showstr(uint16 x,uint16 y,const int8 dat[])
{
	uint16 j;
	
	j = 0;
	while(dat[j] != '\0')
	{
		lcd_showchar(x+8*j,y*16,dat[j]);
		j++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示8位有符号
//  @param      x     	        坐标x方向的起点  参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点  参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型int8
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showint8(0,0,x);//x为int8类型
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint8(uint16 x,uint16 y,int8 dat)
{
	uint8 a[3];
	uint8 i;
	if(dat<0)
	{
		lcd_showchar(x,y*16,'-');
		dat = -dat;
	}
	else	lcd_showchar(x,y*16,' ');
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		lcd_showchar((uint8)(x+(8*(i+1))), (uint8)(y*16),(int8)('0' + a[i]));
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示8位无符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint8
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint8(0,0,x);//x为uint8类型
//-------------------------------------------------------------------------------------------------------------------
void lcd_showuint8(uint16 x,uint16 y,uint8 dat)
{
	uint8 a[3];
	uint8 i;
	
	a[0] = dat/100;
	a[1] = dat/10%10;
	a[2] = dat%10;
	i = 0;
	while(i<3)
	{
		lcd_showchar((uint8)(x+(8*(i+1))), (uint8)(y*16),(int8)('0' + a[i]));
		i++;
	}
	
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示16位有符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型int16
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showint16(0,0,x);//x为int16类型
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint16(uint16 x,uint16 y,int16 dat)
{
	uint8 a[5];
	uint8 i;
	if(dat<0)
	{
		lcd_showchar(x,y*16,'-');
		dat = -dat;
	}
	else	lcd_showchar(x,y*16,' ');

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		lcd_showchar((uint8)(x+(8*(i+1))), (uint8)(y*16),(int8)('0' + a[i]));
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示16位无符号
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint16
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint16(0,0,x);//x为uint16类型
//-------------------------------------------------------------------------------------------------------------------
void lcd_showuint16(uint16 x,uint16 y,uint16 dat)
{
	uint8 a[5];
	uint8 i;

	a[0] = dat/10000;
	a[1] = dat/1000%10;
	a[2] = dat/100%10;
	a[3] = dat/10%10;
	a[4] = dat%10;
	
	i = 0;
	while(i<5)
	{
		lcd_showchar((uint8)(x+(8*(i+1))), (uint8)(y*16),(int8)('0' + a[i]));
		i++;
	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示32位有符号(去除整数部分无效的0)
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型uint32
//  @param      num       	    需要显示的位数 最高10位  不包含正负号
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showuint32(0,0,x,3);//x可以为int32 uint16 int16 uint8 int8类型
//  Sample usage:               负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void lcd_showint32(uint16 x,uint16 y,int32 dat,uint8 num)
{
    int8    buff[34];
    uint8   length;
    
    if(10<num)      num = 10;
    
    num++;
    if(0>dat)   length = zf_sprintf( &buff[0],"%d",dat);//负数
    else
    {
        buff[0] = ' ';
        length = zf_sprintf( &buff[1],"%d",dat);
        length++;
    }
    while(length < num)
    {
        buff[length] = ' ';
        length++;
    }
    buff[num] = '\0';

    lcd_showstr(x, y, buff);	//显示数字
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      液晶显示浮点数(去除整数部分无效的0)
//  @param      x     	        坐标x方向的起点 参数范围 0 -（TFT_X_MAX-1）
//  @param      y     	        坐标y方向的起点 参数范围 0 -（TFT_Y_MAX/16-1）
//  @param      dat       	    需要显示的变量，数据类型float或double
//  @param      num       	    整数位显示长度   最高10位  
//  @param      pointnum        小数位显示长度   最高6位
//  @return     void
//  @since      v1.0
//  Sample usage:               lcd_showfloat(0,0,x,2,3);//显示浮点数   整数显示2位   小数显示三位
//  @note                       特别注意当发现小数部分显示的值与你写入的值不一样的时候，
//                              可能是由于浮点数精度丢失问题导致的，这并不是显示函数的问题，
//                              有关问题的详情，请自行百度学习   浮点数精度丢失问题。
//                              负数会显示一个 ‘-’号   正数显示一个空格
//-------------------------------------------------------------------------------------------------------------------
void lcd_showfloat(uint16 x,uint16 y,double dat,uint8 num,uint8 pointnum)
{
    uint8   length;
	int8    buff[34];
	int8    start,end,point;

	if(6<pointnum)  pointnum = 6;
    if(10<num)      num = 10;
        
    if(0>dat)   length = zf_sprintf( &buff[0],"%f",dat);//负数
    else
    {
        length = zf_sprintf( &buff[1],"%f",dat);
        length++;
    }
    point = length - 7;         //计算小数点位置
    start = point - num - 1;    //计算起始位
    end = point + pointnum + 1; //计算结束位
    while(0>start)//整数位不够  末尾应该填充空格
    {
        buff[end] = ' ';
        end++;
        start++;
    }
    
    if(0>dat)   buff[start] = '-';
    else        buff[start] = ' ';
    
    buff[end] = '\0';

    lcd_showstr(x, y, buff);	//显示数字
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      显示40*40 QQ图片
//  @param      *p     			图像数组地址
//  @return     void
//  @since      v1.0
//  Sample usage:          
//-------------------------------------------------------------------------------------------------------------------
void showimage(const unsigned char *p) 
{
  	int i,j,k; 
	unsigned char picH,picL;
	lcd_clear(WHITE); //清屏  
	
	for(k=0;k<4;k++)
	{
	   	for(j=0;j<3;j++)
		{	
			lcd_set_region(40*j,40*k,40*j+39,40*k+39);		//坐标设置
		    for(i=0;i<40*40;i++)
			 {	
			 	picL=*(p+i*2);	//数据低位在前
				picH=*(p+i*2+1);				
				lcd_writedata_16bit(picH<<8|picL);  						
			 }	
		 }
	}		
}
