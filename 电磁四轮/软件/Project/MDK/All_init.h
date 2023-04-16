#ifndef ALL_INIT_H_
#define ALL_INIT_H_

//蜂鸣器
#define BEEP P77
//定义电机管脚	
//左轮
#define PWM_2 PWMA_CH2P_P62
#define DIR_2 PWMA_CH1P_P60
//右轮
#define DIR_1 PWMA_CH3P_P64
#define PWM_1 PWMA_CH4P_P66
//定义脉冲管脚	
#define SPEEDL_PLUSE   CTIM0_P34//右轮
#define SPEEDR_PLUSE   CTIM3_P04//左轮

#define SPEEDL_DIR     P50//右轮
#define SPEEDR_DIR     P51//左轮

/*舵机*/
#define S3010_CH PWMB_CH1_P74 

//霍尔
#define HALL_PIN P26



void all_init();



#endif