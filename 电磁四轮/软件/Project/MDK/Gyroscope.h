#ifndef GYROSCOPE_H_
#define GYROSCOPE_H_


void Angle_Get();   // 一阶互补滤波函数
void gyroOffset();   //原始数据滤波
void data_change();   //换算单位
void icm_open();
void Angle_add();
float Complementary(float newAngle,float newRate);

extern int16 Yaw, Pitch;
extern float pittch;
#endif