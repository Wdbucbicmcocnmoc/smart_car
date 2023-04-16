#ifndef __KALMAN_CAL_H
#define __KALMAN_CAL_H	 
#include "math.h"
		 				    
//陀螺仪数据计算
void Angle_Cal();
void Kalman_Cal_Pitch(float acc,float gyro);
void Kalman_Cal_Roll(float acc,float gyro);
	
//卡尔曼解算法库
extern short aacx,aacy,aacz;		//加速度传感器原始数据 
extern short gyrox,gyroy,gyroz;	//陀螺仪原始数据 
extern short temperature;			//陀螺仪温度数据
extern float accel_x;	        //X轴加速度值
extern float accel_y;	    	  //Y轴加速度值
extern float accel_z;	        //Z轴加速度值
extern float gyro_x;				  //X轴陀螺仪角速度数据
extern float gyro_y;          //Y轴陀螺仪角速度数据
extern float gyro_z;		 		  //Z轴陀螺仪角速度数据	

extern float pitch_raw;  		   //俯仰角pitch原始数据
extern float pitch_kalman; 	   //pitch滤波后数据
extern float roll_raw;  		   //横滚角roll原始数据
extern float roll_kalman; 		 //roll滤波后数据		
//extern float Angle_x_temp;  		//由加速度计算的x倾斜角度
//extern float Angle_y_temp;  		//由加速度计算的y倾斜角度
//extern float Angle_X_Final; 		//X最终倾斜角度
//extern float Angle_Y_Final; 		//Y最终倾斜角度

// extern rt_int16_t temp;        //温度
// extern rt_int16_t gx,gy,gz;    //三轴加速度
// extern rt_int16_t ax,ay,az;    //三轴角速度
// //判断数据接收是否正常
// extern rt_err_t temp_ret;
// extern rt_err_t a_ret;
// extern rt_err_t g_ret;
								
#endif