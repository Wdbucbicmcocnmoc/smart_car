#include "headfile.h"
#include "myfile.h"

float ADD_valu[13][6]; 
float ADDD_valu[13]; 
float AD_valu[13];          
float GUI_AD[13];           //7路adc归一化后的值
float Min_AD[13] = {1, 1, 1, 1, 1,1,1,1,1}; //最小值是1
float Range = 250;  //电感值的范围是0~100
int Max_Front=3;
int Position_Transit[2]={0};
int Position=0,Position_last=0;

/*********************************************
*函数：电感采集与处理函数
*函数名：Read_ADC()
*备注：
*日期：
*修改日期：
*********************************************/

void Read_ADC()
{
    int16 i, j, k, temp;
    float  adc_valu[13][10], ad_sum[13];

    for (i = 0; i < 10; i++)
    {
        //中间一排和后一排
        adc_valu[0][i] = adc_once(ADC_P11, ADC_10BIT);  //最后一排左
        adc_valu[1][i] = adc_once(ADC_P13, ADC_10BIT);  //中间一排左横
        adc_valu[2][i] = adc_once(ADC_P14, ADC_10BIT);  //中间一排左斜
        adc_valu[3][i] = adc_once(ADC_P15, ADC_10BIT);  //中电感
        adc_valu[4][i] = adc_once(ADC_P16, ADC_10BIT);
        adc_valu[5][i] = adc_once(ADC_P17, ADC_10BIT);
        adc_valu[6][i] = adc_once(ADC_P05, ADC_10BIT);  //最后一排右


        adc_valu[7][i] = adc_once(ADC_P10, ADC_10BIT);  //最前一排左斜
		adc_valu[8][i] = adc_once(ADC_P06, ADC_10BIT);  //左竖
        adc_valu[9][i] = adc_once(ADC_P02, ADC_10BIT);  //最前中电感
        adc_valu[10][i] = adc_once(ADC_P01, ADC_10BIT);
        adc_valu[11][i] = adc_once(ADC_P00, ADC_10BIT);

		 adc_valu[12][i] = adc_once(ADC_P03, ADC_10BIT);
    }

   for (i = 0; i < 13; i++)
    {
        for (j = 0; j < 9; j++)    
        {
            for (k = 0; k < 9 - j; k++)
            {
                if (adc_valu[i][k] > adc_valu[i][k + 1])   
                {
                    temp = adc_valu[i][k + 1];
                    adc_valu[i][k + 1] = adc_valu[i][k];
                    adc_valu[i][k] = temp;
                }
            }
        }
    } 
    
      for (i = 0; i < 13; i++) 
    {
        ad_sum[i] = adc_valu[i][3] + adc_valu[i][4] + adc_valu[i][5]+adc_valu[i][6];
        AD_valu[i] = ad_sum[i] / 4;                                
    }
    for(i = 0; i < 13; i++)
    {
      for(j = 0; j < 5; j++)
      {
        ADD_valu[i][j]=ADD_valu[i][j+1];
      }
      ADD_valu[i][j]=AD_valu[i];
    }
    for(i = 0; i < 13; i++)
    {
        ADDD_valu[i]=(ADD_valu[i][0]+ADD_valu[i][1]+ADD_valu[i][2]+ADD_valu[i][3]+ADD_valu[i][4]+ADD_valu[i][5])/6;//????
    }
    for (i = 0; i < 13; i++) 
    {
        GUI_AD[i] = Range * (ADDD_valu[i] - Min_AD[i]) / (250 - Min_AD[i]);
        if (GUI_AD[i] >= Range)
            GUI_AD[i] = Range;
        if (GUI_AD[i] < Min_AD[i])
            GUI_AD[i] = Min_AD[i];
    }
} 