#ifndef SEROR_H_
#define SEROR_H_
//
void ZW_judge();
void S3010_Direation_Control();
void caculation();
void dianganzhi_show();
void Three_branch_road();
void Circular_zuo();
void Circular_syou();
void Circular();
float Fuzzy_P(float E, float EC);
float Fuzzy_D(float E, float EC);
void podao();
void show_flag();
void flag_show();
void Out_storage();
void In_ku();
void biaozhiwei_show();
void scene_show();
void cross_ten();
//
extern int16 S3010_mid;
extern int16 S3010_Left_Max;
extern int16 S3010_Right_Max;
extern uint8 space_flag;
extern int gyroscope_time, ramp_time, fork_time, Island_time, chuku_time,ruku_time;
extern int8 Ramp, three_on, three_in_L, three_in_R;
extern int8 Island_Left,Island_Right;
extern float Error,Error_last;
extern float Error_angle_out;
extern float kp;
extern float kd;
extern float ruhuan_p, ruhuan_d;
extern float huanz_p, huanz_d;
extern float chuhuan_p, chuhuan_d;
extern uint8 Huan_finish_count;
extern uint8 Po_finish_count;
extern uint8 out_ku, out_garage;
extern uint8 inku;
extern float road_L, road_R, road_sum;
extern float ad_referens;
extern float spaceflag;
extern short b;
extern short a;
extern float zhidao_p;
extern float zhidao_d;
extern float cha_zuo_p, cha_zuo_d;
extern float cha_you_p, cha_you_d;
extern int8 library;
extern uint8 out_ku;
extern int SL_In_xishu, SL_Out_xishu, BL_In_xishu, BL_Out_xishu;
extern int SR_In_xishu, SR_Out_xishu, BR_In_xishu, BR_Out_xishu;


#endif