#include "headfile.h"
#include "myfile.h"

uint8 numm = 1;  //�����˵� ��������ѡ�����
uint8 num = 1;   //һ���˵� ��������ѡ�����
uint8 nummm = 1; //�����˵� ��������ѡ�����
uint8 nux;

void menu() //�˵�������ʾ����
{
  oled_p6x8str(5, num, "#");
  oled_p6x8str(60, 0, "MENU");
  oled_p6x8str(30, 1, "ADC_SHOW");
  oled_p6x8str(30, 2, "xunjiflag");
  oled_p6x8str(30, 3, "MOTRO_PID");
  oled_p6x8str(30, 4, "MOTRO_Ctro");
  oled_p6x8str(30, 5, "DUOJI_Ctro");
  oled_p6x8str(30, 6, "yuanshi_ADC");
}
void xunjiflag()
{
  while (1)
  {
    //
    oled_p6x8str(10, 1, "spaceflag");
    oled_p6x8str(10, 2, "wan_xishu");
    oled_p6x8str(10, 3, "zhi_xishu");
    // oled_p6x8str(5, 4, "jifenjuli");
    oled_p6x8str(10, 4, "o_library");
    oled_p6x8str(10, 5, "ruku_time");
    oled_p6x8str(10, 6, "out_ku");
    // oled_p6x8str(10, 6, "out_ku");
    oled_p6x8str(10, 7, "po_order");
    oled_int16(80, 1, spaceflag);     //���������ֵ
    oled_int16(80, 2, a);             //�����ȺͷŴ�ϵ��
    oled_int16(80, 3, b);             //ֱ����ȺͷŴ�ϵ��
    // oled_printf_float(60, 4, Int_length, 2, 3);
    oled_int16(80, 4, library);
    oled_int16(80, 5, ruku_time);
    oled_int16(80, 6, out_ku);
    oled_int16(80, 7, Po_control_order);
    if (numm == 0)
    {
      oled_p6x8str(5, 0, "#");
    }
    if (P37 == 0)
    {
      delay_ms(20);
      if (P37 == 0)
      {
        while (P37 == 0)
          ;
        numm = numm + 1;
        if (numm > 7)
        {
          numm = 0;
          oled_p6x8str(5, 7, " ");
        }
        nux = numm - 1;
        oled_p6x8str(5, numm, "#");
        oled_p6x8str(5, nux, " ");
      }
    }

    if (P70 == 0)
    {
      delay_ms(30);
      if (P70 == 0)
      {
        while (P70 == 0)
          ;
        switch (numm)
        {
       
        case 1:
          spaceflag = spaceflag + 1;
          break;
        case 2:
          a += 1;
          break;
        case 3:
          b += 1;
          break;
        // case 4:
        //   Int_length += 0.1;
        //   break;
        // case 5:
        //   Int_length += 0.01;
        //   break;
        // case 6:
        //   Int_length += 0.001;
        //   break;
        case 4:
          library += 1;
          break;
        case 5:
          ruku_time += 2;
          break;
        case 6:
          out_ku = 0;
          break;
          case 7:
          Po_control_order = 1;
          break;
        default:
          break;
        }
      }
    }
    if (P72 == 0)
    {
      delay_ms(30);
      if (P72 == 0)
      {
        while (P72 == 0)
          ;
        switch (numm)
        {
       
        case 1:
          spaceflag = spaceflag - 1;
          break;
        case 2:
          a -= 1;
          break;
        case 3:
          b -= 1;
          break;
          // case 4:
          //   Int_length -= 0.1;
          //   break;
          // case 5:
          //   Int_length -= 0.01;
          //   break;
          // case 6:
          //   Int_length -= 0.001;
          //   break;
        case 4:
          library -= 1;
          break;
        case 5:
          ruku_time -= 2;
          break;
        case 6:
          out_ku = 1;
          break;
        case 7:
        Po_control_order = 2;
        break;
        default:
          break;
        }
      }
    }
    if (P54 == 0)
    {
      delay_ms(20);
      if (P54 == 0)
      {
        while (P54 == 0)
          ;
        menu();
        oled_fill(0x00);
        break;
      }
    }
  }
}
void ADC_SHOW() //�����ʾ����
{
  while (1)
  {
    Read_ADC();
    oled_int16(10, 0, GUI_AD[0]);
    oled_int16(10, 1, GUI_AD[1]);
    oled_int16(10, 2, GUI_AD[2]);
    oled_int16(10, 3, GUI_AD[3]);
    oled_int16(10, 4, GUI_AD[4]);
    oled_int16(10, 5, GUI_AD[5]);
    oled_int16(10, 6, GUI_AD[6]);

    oled_int16(50, 0, GUI_AD[7]);
    oled_int16(50, 1, GUI_AD[8]);
    oled_int16(50, 2, GUI_AD[9]);
    oled_int16(50, 3, GUI_AD[10]);
    oled_int16(50, 4, GUI_AD[11]);
    oled_int16(50, 5, GUI_AD[12]);
    if (P54 == 0)
    {
      delay_ms(20);
      if (P54 == 0)
      {
        while (P54 == 0)
          ;
        menu();
        oled_fill(0x00);
        break;
      }
    }
  }
}
void DUOJI_Ctro() //������ƺ���
{
  while (1)
  {
    //        oled_p6x8str(10,0,"kp_y:");//���һ�p
    //        oled_p6x8str(10,1,"kd_y:");//���һ�d
    //        oled_printf_float(80,0,kp_y,2,3);
    //        oled_printf_float(80,1,kd_y,2,3);
    //			 oled_p6x8str(10,2,"kp_zr");//����p
    //        oled_printf_float(80,2,kp_zr,2,3);
    //        oled_p6x8str(10,3,"kd_zr");//����d
    //         oled_printf_float(80,3,kd_zr,2,3);
    //			 oled_p6x8str(10,4,"kp_yz");//��ѭ��p
    //         oled_printf_float(80,4,kp_yz,2,3);
    //			 oled_p6x8str(10,5,"kd_yz");////��ѭ��d
    //         oled_printf_float(80,5,kd_yz,2,3);
    //			 oled_p6x8str(10,6,"kp_ryc");//����ѭ��p
    //        oled_printf_float(80,6,kp_ryc,2,3);//ADDD_valu[i]
    //			 oled_p6x8str(10,7,"kd_ryc");//����ѭ��d
    //        oled_printf_float(80,7,kd_ryc,2,3);
    //		     oled_p6x8str(5,numm,"#");
    oled_p6x8str(10, 0, "speed_adjust");
    oled_p6x8str(10, 1, "annulus");
    oled_p6x8str(10, 2, "sancha_pd");
    oled_p6x8str(10, 3, "zhidao_pd");
    oled_p6x8str(10, 4, "huan_xishu");
    oled_p6x8str(10, 5, "mid");
    oled_int16(80, 5, S3010_mid);
    if (numm == 0)
    {
      oled_p6x8str(5, 0, "#");
    }
    if (P37 == 0)
    {
      delay_ms(20);
      if (P37 == 0)
      {
        while (P37 == 0)
          ;
        //   oled_fill(0x00);
        numm = numm + 1;
        if (numm > 6)
        {
          numm = 0;
          oled_p6x8str(5, 5, " ");
        }
        nux = numm - 1;
        oled_p6x8str(5, numm, "#");
        oled_p6x8str(5, nux, " ");
      }
    }
    if (P70 == 0)
    {
      delay_ms(30);
      if (P70 == 0)
      {
        while (P70 == 0)
          ;
        oled_fill(0x00);
        switch (numm)
        {
        case 0:
          E_speed();
          break;
        case 1:
          annulus_PD();
          break;
        case 2:
          sancha_pd();
          break;
        case 3:
          zhidao_pd();
          break;
        case 4:
          huan_xishu();
          break;
        case 5:
          S3010_mid += 1;
          pwm_duty(PWMB_CH1_P74, S3010_mid);
          break;
        case 6:
          S3010_mid += 5;
          pwm_duty(PWMB_CH1_P74, S3010_mid);
        default:
          break;
        }
      }
    }
    if (P72 == 0)
    {
      delay_ms(30);
      if (P72 == 0)
      {
        while (P72 == 0)
          ;
        switch (numm)
        {

        case 5:
          S3010_mid -= 1;
          pwm_duty(PWMB_CH1_P74, S3010_mid);
          break;
        case 6:
          S3010_mid -= 5;
          pwm_duty(PWMB_CH1_P74, S3010_mid);
        default:
          break;
        }
      }
    }
    if (P54 == 0)
    {
      delay_ms(20);
      if (P54 == 0)
      {
        while (P54 == 0)
          ;
        oled_fill(0x00);
        menu();
        break;
      }
    }
  }
}

void huan_xishu()
{
  while (1)
  {
    oled_p6x8str(10, 0, "SL_in:");
    oled_int16(80, 0, SL_In_xishu);
    oled_p6x8str(10, 1, "SL_out:");
    oled_int16(80, 1, SL_Out_xishu);
    oled_p6x8str(10, 2, "SR_in:");
    oled_int16(80, 2, SR_In_xishu);
    oled_p6x8str(10, 3, "SR_out:");
    oled_int16(80, 3, SR_Out_xishu);


    if (nummm == 0)
    {
      oled_p6x8str(5, 0, "#");
    }
    if (P37 == 0)
    {
      delay_ms(20);
      if (P37 == 0)
      {
        while (P37 == 0)
          ;
        nummm = nummm + 1;
        if (nummm > 3)
        {
          nummm = 0;
          oled_p6x8str(5, 3, " ");
        }
        nux = nummm - 1;
        oled_p6x8str(5, nummm, "#");
        oled_p6x8str(5, nux, " ");
      }
    }
    if (P70 == 0)
    {
      delay_ms(30);
      if (P70 == 0)
      {
        while (P70 == 0)
          ;
        switch (nummm)
        {

        case 0:
          SL_In_xishu += 1;
          break;
        case 1:
          SL_Out_xishu += 1;
          break;
        case 2:
          SR_In_xishu += 1;
          break;
        case 3:
          SR_Out_xishu += 1;
          break;
        default:
          break;
        }
      }
    }

    if (P72 == 0)
    {
      delay_ms(30);
      if (P72 == 0)
      {
        while (P72 == 0)
          ;
        switch (nummm)
        {
        case 0:
          SL_In_xishu -= 1;
          break;
        case 1:
          SL_Out_xishu -= 1;
          break;
        case 2:
          SR_In_xishu -= 1;
          break;
        case 3:
          SR_Out_xishu -= 1;
          break;
        default:
          break;
        }
      }
    }
    if (P54 == 0)
    {
      delay_ms(20);
      if (P54 == 0)
      {
        while (P54 == 0)
          ;
        oled_fill(0x00);
        break;
      }
    }
  }
}

void sancha_pd()
{
  while (1)
  {
    oled_p6x8str(10, 1, "cha_zuo_p:");
    oled_printf_float(80, 1, cha_zuo_p, 3, 3);
    oled_p6x8str(10, 2, "cha_zuo_d:");
    oled_printf_float(80, 2, cha_zuo_d, 3, 3);
    oled_p6x8str(10, 3, "cha_you_p:");
    oled_printf_float(80, 3, cha_you_p, 3, 3);
    oled_p6x8str(10, 4, "cha_you_d:");
    oled_printf_float(80, 4, cha_you_d, 3, 3);
    
    if (nummm == 0)
    {
      oled_p6x8str(5, 0, "#");
    }
    if (P37 == 0)
    {
      delay_ms(20);
      if (P37 == 0)
      {
        while (P37 == 0)
          ;
        nummm = nummm + 1;
        if (nummm > 7)
        {
          nummm = 0;
          oled_p6x8str(5, 7, " ");
        }
        nux = nummm - 1;
        oled_p6x8str(5, nummm, "#");
        oled_p6x8str(5, nux, " ");
      }
    }
    if (P70 == 0)
    {
      delay_ms(30);
      if (P70 == 0)
      {
        while (P70 == 0)
          ;
        switch (nummm)
        {

         
        case 1:
          cha_zuo_p += 0.1;
          break;
        case 2:
          cha_zuo_d += 0.1;
          break;
        case 3:
          cha_you_p += 0.1;
          break;
        case 4:
          cha_you_d += 0.1;
          break;
       
        default:
          break;
        }
      }
    }

    if (P72 == 0)
    {
      delay_ms(30);
      if (P72 == 0)
      {
        while (P72 == 0)
          ;
        switch (nummm)
        {
        case 1:
          cha_zuo_p -= 0.1;
          break;
        case 2:
          cha_zuo_d -= 0.1;
          break;
        case 3:
          cha_you_p -= 0.1;
          break;
        case 4:
          cha_you_d -= 0.1;
          break;
        default:
          break;
        }
      }
    }
    if (P54 == 0)
    {
      delay_ms(20);
      if (P54 == 0)
      {
        while (P54 == 0)
          ;
        oled_fill(0x00);
        // menu();
        break;
      }
    }
  }
}
void zhidao_pd()
{
  while (1)
  {
    oled_p6x8str(10, 1, "zhidao_p:");
    oled_printf_float(80, 1, zhidao_p, 3, 3);
    oled_p6x8str(10, 2, "zhidao_d:");
    oled_printf_float(80, 2, zhidao_d, 3, 3);
    if (nummm == 0)
    {
      oled_p6x8str(5, 0, "#");
    }
    if (P37 == 0)
    {
      delay_ms(20);
      if (P37 == 0)
      {
        while (P37 == 0)
          ;
        nummm = nummm + 1;
        if (nummm > 7)
        {
          nummm = 0;
          oled_p6x8str(5, 7, " ");
        }
        nux = nummm - 1;
        oled_p6x8str(5, nummm, "#");
        oled_p6x8str(5, nux, " ");
      }
    }
    if (P70 == 0)
    {
      delay_ms(30);
      if (P70 == 0)
      {
        while (P70 == 0)
          ;
        switch (nummm)
        {

          
        case 1:
          zhidao_p += 0.1;
          break;
        case 2:
          zhidao_d += 0.1;
          break;
        default:
          break;
        }
      }
    }

    if (P72 == 0)
    {
      delay_ms(30);
      if (P72 == 0)
      {
        while (P72 == 0)
          ;
        switch (nummm)
        {
          //  case 0:
          //    ruhuan_p-=0.1;
          //    break;
        case 1:
          zhidao_p -= 0.1;
          break;
        case 2:
          zhidao_d -= 0.1;
          break;
          // 			  case 3:
          //  huanz_d-=0.1;
          //  break;
          // 		case 4:
          //  chuhuan_p-=0.1;
          //  break;
        case 5:
          chuhuan_d -= 0.1;
          break;
          //													 case 6:
          //                   kp_ryc-=0.1;
          //                   break;
          //													  case 7:
          //                   kd_ryc-=0.1;
          //                    break;
        default:
          break;
        }
      }
    }
    if (P54 == 0)
    {
      delay_ms(20);
      if (P54 == 0)
      {
        while (P54 == 0)
          ;
        oled_fill(0x00);
        // menu();
        break;
      }
    }
  }
}
void E_speed() //����Ԫ���ٶ�
{
  while (1)
  {
    oled_p6x8str(10, 0, "base_fork:");
    oled_int16(80, 0, base_fork);
    oled_p6x8str(10, 1, "base_loop:");
    oled_int16(80, 1, base_loop);
    oled_p6x8str(10, 2, "base_ramp:");
    oled_int16(80, 2, base_ramp);
    oled_p6x8str(10, 3, "base_stra:");
    oled_int16(80, 3, base_straight);
    if (nummm == 1)
    {
      oled_p6x8str(5, 1, "#");
    }
    if (P37 == 0)
    {
      delay_ms(20);
      if (P37 == 0)
      {
        while (P37 == 0)
          ;
        nummm = nummm + 1;
        if (nummm > 3)
        {
          nummm = 0;
          oled_p6x8str(5, 3, " ");
        }
        nux = nummm - 1;
        oled_p6x8str(5, nummm, "#");
        oled_p6x8str(5, nux, " ");
      }
    }
    if (P70 == 0)
    {
      delay_ms(30);
      if (P70 == 0)
      {
        while (P70 == 0)
          ;
        switch (nummm)
        {
        case 0:
          base_fork += 5;
          break;
        case 1:
          base_loop += 5;
          break;
        case 2:
          base_ramp += 5;
          break;
        case 3:
          base_straight += 5;
          break;
        default:
          break;
        }
      }
    }

    if (P72 == 0)
    {
      delay_ms(30);
      if (P72 == 0)
      {
        while (P72 == 0)
          ;
        switch (nummm)
        {
        case 0:
          base_fork -= 5;
          break;
        case 1:
          base_loop -= 5;
          break;
        case 2:
          base_ramp -= 5;
          break;
        case 3:
          base_straight -= 5;
          break;
        default:
          break;
        }
      }
    }
    if (P54 == 0)
    {
      delay_ms(20);
      if (P54 == 0)
      {
        while (P54 == 0)
          ;
        oled_fill(0x00);
        break;
      }
    }
  }
}

void annulus_PD()
{
  while (1)
  {
    oled_p6x8str(10, 0, "ruh_p:"); //���һ�p
    oled_p6x8str(10, 1, "ruh_d:"); //���һ�d
    oled_printf_float(80, 0, ruhuan_p, 2, 3);
    oled_printf_float(80, 1, ruhuan_d, 2, 3);
    oled_p6x8str(10, 2, "huz_p"); //����p
    oled_printf_float(80, 2, huanz_p, 2, 3);
    oled_p6x8str(10, 3, "huz_d"); //����d
    oled_printf_float(80, 3, huanz_d, 2, 3);
    oled_p6x8str(10, 4, "cuh_p"); //����d
    oled_printf_float(80, 4, chuhuan_p, 2, 3);
    oled_p6x8str(10, 5, "cuh_d"); //����d
    oled_printf_float(80, 5, chuhuan_d, 2, 3);

    if (nummm == 0)
    {
      oled_p6x8str(5, 0, "#");
    }
    if (P37 == 0)
    {
      delay_ms(20);
      if (P37 == 0)
      {
        while (P37 == 0)
          ;
        nummm = nummm + 1;
        if (nummm > 7)
        {
          nummm = 0;
          oled_p6x8str(5, 7, " ");
        }
        nux = nummm - 1;
        oled_p6x8str(5, nummm, "#");
        oled_p6x8str(5, nux, " ");
      }
    }
    if (P70 == 0)
    {
      delay_ms(30);
      if (P70 == 0)
      {
        while (P70 == 0)
          ;
        switch (nummm)
        {

        case 0:
          ruhuan_p += 0.1;
          break;
        case 1:
          ruhuan_d += 0.1;
          break;
        case 2:
          huanz_p += 0.1;
          break;
        case 3:
          huanz_d += 0.1;
          break;
        case 4:
          chuhuan_p += 0.1;
          break;
        case 5:
          chuhuan_d += 0.1;
          break;
        default:
          break;
        }
      }
    }

    if (P72 == 0)
    {
      delay_ms(30);
      if (P72 == 0)
      {
        while (P72 == 0)
          ;
        switch (nummm)
        {
        case 0:
          ruhuan_p -= 0.1;
          break;
        case 1:
          ruhuan_d -= 0.1;
          break;
        case 2:
          huanz_p -= 0.1;
          break;
        case 3:
          huanz_d -= 0.1;
          break;
        case 4:
          chuhuan_p -= 0.1;
          break;
        case 5:
          chuhuan_d -= 0.1;
          break;
        default:
          break;
        }
      }
    }
    if (P54 == 0)
    {
      delay_ms(20);
      if (P54 == 0)
      {
        while (P54 == 0)
          ;
        oled_fill(0x00);
        oled_p6x8str(10, 0, "speed_adjust");
        oled_p6x8str(10, 1, "annulus");
        break;
      }
    }
  }
}

void yuanshi_ADC()
{
  while (1)
  {
    Read_ADC();
    oled_int16(10, 0, ADDD_valu[0]);
    oled_int16(10, 1, ADDD_valu[1]);
    oled_int16(10, 2, ADDD_valu[2]);
    oled_int16(10, 3, ADDD_valu[3]);
    oled_int16(10, 4, ADDD_valu[4]);
    oled_int16(10, 5, ADDD_valu[5]);
    oled_int16(10, 6, ADDD_valu[6]);
    oled_int16(10, 7, ADDD_valu[7]);
    oled_int16(50, 0, ADDD_valu[8]);
    oled_int16(50, 1, ADDD_valu[9]);
    oled_int16(50, 2, ADDD_valu[10]);
    oled_int16(50, 3, ADDD_valu[11]);
    if (P54 == 0)
    {
      delay_ms(20);
      if (P54 == 0)
      {
        while (P54 == 0)
          ;
        menu();
        oled_fill(0x00);
        break;
      }
    }
  }
}

void MOTRO_PID() //������ƺ��� ��ʾ�ٶ�
{
  while (1)
  {
    oled_p6x8str(10, 1, "KP_L:");
    oled_printf_float(80, 1, KP_L, 3, 3);
    oled_p6x8str(10, 2, "KD_L:");
    oled_printf_float(80, 2, KD_L, 3, 3);
    oled_p6x8str(10, 3, "KI_L:");
    oled_printf_float(80, 3, KI_L, 3, 3);
    oled_p6x8str(10, 4, "KP_R:");
    oled_printf_float(80, 4, KP_R, 3, 3);
    oled_p6x8str(10, 5, "KD_R:");
    oled_printf_float(80, 5, KD_R, 3, 3);
    oled_p6x8str(10, 6, "KI_R:");
    oled_printf_float(80, 6, KI_R, 3, 3);
    if (num == 1)
    {
      oled_p6x8str(5, num, "#");
    }

    if (P37 == 0)
    {
      delay_ms(20);
      if (P37 == 0)
      {
        while (P37 == 0)
          ;
        num = num + 1;
        if (num > 6)
        {
          num = 1;
          oled_p6x8str(5, 6, " ");
        }
        nux = num - 1;
        oled_p6x8str(5, num, "#");
        oled_p6x8str(5, nux, " ");
      }
    }

    if (P70 == 0)
    {
      delay_ms(20);
      if (P70 == 0)
      {
        while (P70 == 0)
          ;
        switch (num)
        {
        case 1:
          KP_L += 0.5;
          break;
        case 2:
          KD_L += 0.5;
          break;
        case 3:
          KI_L += 0.5;
          break;
        case 4:
          KP_R += 0.5;
          break;
        case 5:
          KD_R += 0.5;
          break;
        case 6:
          KI_R += 0.5;
          break;
        default:
          break;
        }
      }
    }
    if (P72 == 0)
    {
      delay_ms(20);
      if (P72 == 0)
      {
        while (P72 == 0)
          ;
        switch (num)
        {
        case 1:
          KP_L -= 0.5;
          break;
        case 2:
          KD_L -= 0.5;
          break;
        case 3:
          KI_L -= 0.5;
          break;
        case 4:
          KP_R -= 0.5;
          break;
        case 5:
          KD_R -= 0.5;
          break;
        case 6:
          KI_R -= 0.5;
          break;
        default:
          break;
        }
      }
    }
    if (P54 == 0)
    {
      delay_ms(20);
      if (P54 == 0)
      {
        while (P54 == 0)
          ;
        oled_fill(0x00);
        menu();
        break;
      }
    }
  }
}

//���ڻ���д���ֶ�pd

void MOTRO_Ctro()
{
  while (1)
  {
    oled_p6x8str(10, 1, "base:");
    oled_int16(80, 1, base);

    if (numm == 1)
    {
      oled_p6x8str(5, numm, "#");
    }

    if (P70 == 0)
    {
      delay_ms(20);
      if (P70 == 0)
      {
        while (P70 == 0)
          ;
        switch (numm)
        {
        case 1:
          base += 1;
          break;
        }
      }
    }
    if (P72 == 0)
    {
      delay_ms(20);
      if (P72 == 0)
      {
        while (P72 == 0)
          ;
        switch (numm)
        {
        case 1:
          base -= 1;
          break;
        }
      }
    }

    if (P54 == 0)
    {
      delay_ms(20);
      if (P54 == 0)
      {
        while (P54 == 0)
          ;
        oled_fill(0x00);
        menu();
        break;
      }
    }
  }
}


void oled_menu() //�˵���������
{

  while (P44 == 0)
  {
    menu();
    if (P37 == 0)
    {
      delay_ms(20);
      if (P37 == 0)
      {
        while (P37 == 0)
          ;
        num = num + 1;
        if (num > 7)
        {
          num = 0;
          oled_p6x8str(5, 7, " ");
        }
        nux = num - 1;
        oled_p6x8str(5, num, "#");
        oled_p6x8str(5, nux, " ");
      }
    }

    if (P70 == 0)
    {
      delay_ms(20);
      if (P70 == 0)
      {
        while (P70 == 0)
          ;
        oled_fill(0x00);
        switch (num)
        {
        case 1:
          ADC_SHOW();
          break;
        case 2:
          xunjiflag();
          break;
        case 3:
          MOTRO_PID();
          break;
        case 4:
          MOTRO_Ctro();
          break;
        case 5:
          DUOJI_Ctro(); // yuanshi_ADC()
          break;
        case 6:
          yuanshi_ADC();
          break;
        default:
          break;
        }
      }
    }
    while (P44 == 1)
    {
      oled_fill(0x00);
      break;
    }
  } 
}