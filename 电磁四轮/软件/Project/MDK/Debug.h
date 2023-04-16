#ifndef __DEBUG_H_
#define __DEBUG_H_

void oled_menu(void);
void menu(void);
void ADC_SHOW(void);
void DUOJI_Ctro(void);
void DUOJI_PD(void);
void MOTRO_Ctro(void);
void xunjiflag(void);//循迹标志
void MOTRO_PID(void);//电机pid
void E_speed();   //三岔
void annulus_PD();  //圆环
void yuanshi_ADC();
void zhidao_pd();
void sancha_pd();
void huan_xishu();
void Set_Island_mode();
#endif