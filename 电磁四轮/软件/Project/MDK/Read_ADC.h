#ifndef READ_ADC_H_
#define READ_ADC_H_

//******************电感排布图*******************//

//第一排     /      |    ——     |       \        //

//中间排       ——    /   ——    \     ——          //

//最后排          ——            ——               //
//******************电感排布图*******************//


//中间排和最后排
#define ZLAD  GUI_AD[0]    
#define QLAD  GUI_AD[1]
#define XLAD  GUI_AD[2]   
#define MAD   GUI_AD[3]
#define XRAD  GUI_AD[4]
#define QRAD  GUI_AD[5]
#define ZRAD  GUI_AD[6]

//最前一排
#define FXLAD  GUI_AD[7]
#define FSLAD  GUI_AD[8]
#define FMAD  GUI_AD[9]
#define FSRAD  GUI_AD[10]
#define FXRAD  GUI_AD[11]
#define HAD  GUI_AD[12]


//extern int8 outflag;
void Read_ADC();

extern int Max_Front;
extern int Position_Transit[2];
extern int Position,Position_last;
extern float GUI_AD[13],ADDD_valu[13];


#endif

