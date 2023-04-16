#ifndef MOTOR_H_
#define MOTOR_H_


//累加值限幅
#define A (500)
//占空比限幅
#define C (6000)


void encode();//编码器测速函数
void motor_pid();//电机pid闭环控制
void motor_control();//电机驱动函数
void huoer();
void Set_Island_mode();

extern int flag_0;
extern int base,base_fork,base_bend,base_loop,base_straight,base_ramp;
extern float Error_angle_out;
extern int exp_speed_l;
extern int exp_speed_r;
extern uint8 lost_flag;
extern int16 templ_pluse;
extern int16 tempr_pluse;
extern int8 number;
extern float KP_L, KD_L, KI_L;
extern float KP_R, KD_R, KI_R;

#endif