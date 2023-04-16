#include "headfile.h"
#include "myfile.h"

void all_init()
{
    //电机初始化
	pwm_init(PWM_1, 17000, 0);
	pwm_init(PWM_2, 17000, 0); 
	pwm_init(PWMA_CH1P_P60, 17000 , 0);
	pwm_init(PWMA_CH3P_P64, 17000 , 0); 
	//舵机初始化
	pwm_init(S3010_CH, 50,700);    
	/*ADC通道初始化*/
//底下FFC
	adc_init(ADC_P00, ADC_SYSclk_DIV_2);	
	adc_init(ADC_P01, ADC_SYSclk_DIV_2);	
	adc_init(ADC_P02, ADC_SYSclk_DIV_2);	
	adc_init(ADC_P06, ADC_SYSclk_DIV_2);		
	adc_init(ADC_P10, ADC_SYSclk_DIV_2);	

//上面FFC
	adc_init(ADC_P03, ADC_SYSclk_DIV_2);	
	//adc_init(ADC_P04, ADC_SYSclk_DIV_2);	
	adc_init(ADC_P05, ADC_SYSclk_DIV_2);	
	adc_init(ADC_P17, ADC_SYSclk_DIV_2);	
	adc_init(ADC_P16, ADC_SYSclk_DIV_2);	
	adc_init(ADC_P15, ADC_SYSclk_DIV_2);	
	adc_init(ADC_P14, ADC_SYSclk_DIV_2);	
	adc_init(ADC_P13, ADC_SYSclk_DIV_2);	
	adc_init(ADC_P11, ADC_SYSclk_DIV_2);

	
  //陀螺仪
	icm20602_init_simiic();
	simiic_init();

	
	//oled初始化
	oled_init();
	//蜂鸣器
	BEEP=0;
	//编码器所用的定时器
	ctimer_count_init(SPEEDL_PLUSE);	
	ctimer_count_init(SPEEDR_PLUSE);	
	//中断定时器
	pit_timer_ms(TIM_1, 5);

}