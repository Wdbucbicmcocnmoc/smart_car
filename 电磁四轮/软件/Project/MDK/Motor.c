#include "headfile.h"
#include "myfile.h"

//编码器采集回来的数值
int16 templ_pluse = 0;
int16 tempr_pluse = 0;
uint8 lost_flag = 0;
//期望速度
int16 exp_speed_r = 0;
int16 exp_speed_l = 0;
int base = 150;
int base_fork = 140, base_straight = 130, base_bend = 150, base_loop = 140, base_ramp = 110; //三岔、直道、弯道、圆环调速
//期望与实际的误差
float L_err[3] = {0, 0, 0};
float R_err[3] = {0, 0, 0};
//电机pid参数
// float KP_L=100,KD_L=137,KI_L=41;
// float KP_R=100,KD_R=137,KI_R=41;
// float KP_L = 53, KD_L = 41, KI_L = 20.5;
// float KP_R = 53, KD_R = 41, KI_R = 20.5;
float KP_L = 80, KD_L = 139, KI_L = 48;
float KP_R = 80, KD_R = 139, KI_R = 48;
//电机输出占空比
int32 L_duty = 0, R_duty = 0;
int16 L_sum = 0;
int16 R_sum = 0;
int flag_0 = 0;
//系数
int k = 14;
//实际速度
int16 L_speed, R_speed;
//
int8 number = 1;
/*******************************************************************************
 * 函 数 名       :motor_control()
 * 函数功能		   : 电机驱动函数
 * 输    入       : 无
 * 输    出    	 : 无
 *******************************************************************************/
void motor_control()
{
	if (P36 == 0)
	{
		delay_ms(20);
		if (P36 == 0)
		{
			delay_ms(500);
			flag_0 = 1;
		}
	}

	if (flag_0 == 1)
	{
		if (L_duty > 0)
		{
			pwm_duty(PWMA_CH3P_P64, 0);
			pwm_duty(PWMA_CH4P_P66, (uint32)L_duty); //控制正转
		}
		else if (L_duty < 0)
		{
			pwm_duty(PWMA_CH3P_P64, (uint32)(-L_duty)); //控制反转
			pwm_duty(PWMA_CH4P_P66, 0);
		}
		if (R_duty > 0)
		{
			pwm_duty(PWMA_CH1P_P60, (uint32)(R_duty));
			pwm_duty(PWMA_CH2P_P62, 0);
		}
		else if (R_duty < 0)
		{
			pwm_duty(PWMA_CH2P_P62, (uint32)(-R_duty));
			pwm_duty(PWMA_CH1P_P60, 0);
		}
	}
}
/*******************************************************************************
 * 函 数 名       :encode()
 * 函数功能		 	 : 编码器测速函数
 * 输    入       : 无
 * 输    出    	 : 无
 *******************************************************************************/
void encode()
{
	templ_pluse = ctimer_count_read(SPEEDL_PLUSE);
	tempr_pluse = ctimer_count_read(SPEEDR_PLUSE);

	if (SPEEDL_DIR == 1)
	{
		templ_pluse = -templ_pluse;
	}
	if (SPEEDR_DIR == 1)
	{
		tempr_pluse = -tempr_pluse;
	}

	L_speed = templ_pluse; //右轮速度
	R_speed = tempr_pluse; //左轮速度
	//计数器清零
	ctimer_count_clean(SPEEDL_PLUSE);
	ctimer_count_clean(SPEEDR_PLUSE);
	road_L += (templ_pluse * 2 * (3.14159265) * 0.032) / 2250;
	road_R -= (tempr_pluse * 2 * (3.14159265) * 0.032) / 2250;
	road_sum = (road_L + road_R) / 2;
}

/*******************************************************************************
 * 函 数 名       :motor_CHA()
 * 函数功能		   :差速
 * 输    入       : 无
 * 输    出    	 : 无
 *******************************************************************************/
void different_chaspeed()
{
	if (lost_flag == 0)
	{
		exp_speed_r = base;
		exp_speed_l = -base;
		if (space_flag == 1)
		{
			if (Error_angle_out > 0 && inku == 0)
			{
				// exp_speed_l = exp_speed_l * (float)(Error_angle_out * (-0.005f) + 0.80f); // && space_flag!=1
				// exp_speed_r = base + Error_angle_out * 0.15;
				exp_speed_l = exp_speed_l * (float)(Error_angle_out * (-0.005f) + 0.8f);
				exp_speed_r = base + (int16)(Error_angle_out * 0.10);
			}
			if (Error_angle_out < 0 && inku == 0) //
			{
				// exp_speed_r = exp_speed_r * (float)(Error_angle_out * (0.005f) + 0.80f); //
				// exp_speed_l = -(base + Error_angle_out * 0.15);
				exp_speed_r = exp_speed_r * (float)(Error_angle_out * (0.005f) + 0.8f);
				exp_speed_l = -(base + (int16)(Error_angle_out * 0.10));
			}
		}
		if (Error_angle_out > 0 && three_on == 0 && inku == 0 && space_flag != 1)
		{
			exp_speed_l = exp_speed_l * (float)(Error_angle_out * (-0.006f) + 0.80f); // && space_flag!=1
			exp_speed_r = base + Error_angle_out * 0.15;
			// exp_speed_l = exp_speed_l * (float)(Error_angle_out * (-0.0045f) + 0.99f);
			// exp_speed_r = base + (int16)(Error_angle_out * 0);
		}
		if (Error_angle_out < 0 && three_on == 0 && inku == 0 && space_flag != 1) //
		{
			exp_speed_r = exp_speed_r * (float)(Error_angle_out * (0.006f) + 0.80f); //
			exp_speed_l = -(base + Error_angle_out * 0.15);
			// exp_speed_l = exp_speed_l * (float)(Error_angle_out * (0.0045f) + 0.99f);
			// exp_speed_r = base + (int16)(Error_angle_out * 0);
		}

		if (Error_angle_out > 0 && (inku == 4 || inku == 3) && inku != 5)
		{
			exp_speed_l = exp_speed_l * (float)(Error_angle_out * (-0.008f) + 0.80f);
			exp_speed_r = base;
		}
		if (Error_angle_out < 0 && (inku == 4 || inku == 3) && inku != 5)
		{
			exp_speed_r = exp_speed_r * (float)(Error_angle_out * (0.008f) + 0.80f);
			exp_speed_l = -(base * 1.3);
		}

		//三岔路口时的差速
		if (Error_angle_out > 0 && three_on == 1 && inku == 0) //
		{
			exp_speed_l = exp_speed_l * (float)(Error_angle_out * (-0.008f) + 0.75f);
			exp_speed_r = base + (85 - MAD) * 0.1; // Error_angle_out * 0.1
		}
		if (Error_angle_out < 0 && three_on == 1 && inku == 0) //
		{
			exp_speed_r = exp_speed_r * (float)(Error_angle_out * (0.03f) + 0.90f);
			exp_speed_l = -(base + Error_angle_out * 0.3);
		}
	}
}

/*******************************************************************************
 * 函 数 名       :motor_pid()
 * 函数功能		 : 电机pid函数
 * 输    入       : 无
 * 输    出    	 : 无
 *******************************************************************************/
void motor_pid()
{
	if (MAD <= 6 && ZLAD <= 6 && ZRAD <= 6 && out_ku != 0 && inku == 0 && chuku_time > 400)
	{
		if ((three_on == 1 || three_in_L == 1 && three_in_R == 1) && fork_time < 200)
			lost_flag = 0;
		else
		{
			lost_flag = 1;
		}
	}

	if (lost_flag == 0)
	{
		different_chaspeed();
	}

	if (lost_flag == 1) 
	{
		base = 0;
		exp_speed_r = 0;
		exp_speed_l = 0;
	}

	//右轮误差
	L_err[2] = L_err[1];
	L_err[1] = L_err[0];
	L_err[0] = exp_speed_r - L_speed;
	//右轮误差累计
	L_sum += L_err[0];

	//左轮误差
	R_err[2] = R_err[1];
	R_err[1] = R_err[0];
	R_err[0] = exp_speed_l - R_speed;
	//左轮误差累计
	R_sum += R_err[0];
	//右轮限幅
	if (L_sum > A) // L_sum>1000 L_sum=1000
		L_sum = A;
	if (L_sum < -A)
		L_sum = -A;
	//左轮限幅
	if (R_sum > A) // L_sum>1000 L_sum=1000
		R_sum = A;
	if (R_sum < -A)
		R_sum = -A;

	L_duty = (int32)(KP_L * L_err[0] + KI_L * L_sum + KD_L * (L_err[0] - L_err[1]));
	R_duty = (int32)(KP_R * R_err[0] + KI_R * R_sum + KD_R * (R_err[0] - R_err[1]));

	if (L_duty > C)
		L_duty = C;
	if (L_duty < -C)
		L_duty = -C;

	if (R_duty > C)
		R_duty = C;
	if (R_duty < -C)
		R_duty = -C;
}

/*******************************************************************************
 * 函 数 名       :huoer()
 * 函数功能		   : 豆豆写的很牛逼的霍尔检测
 * 输    入       : 无
 * 输    出    	 : 无
 *******************************************************************************/
void huoer()
{
	if (HALL_PIN == 0 && number < 24 && out_ku == 1) //&& hall_detection_count<3
	{												 //&& (cha_num == 2 || SLhuan_num == 2 || SRhuan_num == 2)
		number += 1;
		if (number >= 24)
		{
			number = 0;
		}
	}
	if (number >= 5)
	{
		out_ku = 2;
		BEEP = 1;
	}
}


static int16 Ackerman = 380;//数越小，差速越大，最大不要超过410，最小不要180
                if (turn >= 0)
                {
                    L_Motor.exp_speed = (int)(L_except-PWM_decrease) *(1.0-1.0*(tan((float)turn*10*PI/Ackerman)*0.396));
                    R_Motor.exp_speed = (int)(R_except-PWM_decrease) *(1.0+0*(tan((float)turn*10*PI/Ackerman)*0.396));
                   // if(L_Motor.exp_speed<=110)L_Motor.exp_speed=110;
                }
                else if (turn <0) //右弯
                {
                    L_Motor.exp_speed = (int)(L_except-PWM_decrease) *(1.0-0*(tan((float)turn*10*PI/Ackerman)*0.396));
                    R_Motor.exp_speed = (int)(R_except-PWM_decrease) *(1.0+1.0*(tan((float)turn*10*PI/Ackerman)*0.396));
                    //if(R_Motor.exp_speed<=110)L_Motor.exp_speed=110;
                }