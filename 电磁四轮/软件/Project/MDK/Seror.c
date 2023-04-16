/*    	每日一拜 好过省赛             天天参拜 稳过国赛        */
/* \\ \\ \\ \\ \\ \\ \\ || || || || || || // // // // // // // //
\\ \\ \\ \\ \\ \\ \\        _ooOoo_          // // // // // // //
\\ \\ \\ \\ \\ \\          o8888888o            // // // // // //
\\ \\ \\ \\ \\             88" . "88               // // // // //
\\ \\ \\ \\                (| -_- |)                  // // // //
\\ \\ \\                   O\  =  /O                     // // //
\\ \\                   ____/`---'\____                     // //
\\                    .'  \\|     |//  `.                      //
==                   /  \\|||  :  |||//  \                     ==
==                  /  _||||| -:- |||||-  \                    ==
==                  |   | \\\  -  /// |   |                    ==
==                  | \_|  ''\---/''  |   |                    ==
==                  \  .-\__  `-`  ___/-. /                    ==
==                ___`. .'  /--.--\  `. . ___                  ==
==              ."" '<  `.___\_<|>_/___.'  >'"".               ==
==            | | :  `- \`.;`\ _ /`;.`/ - ` : | |              \\
//            \  \ `-.   \_ __\ /__ _/   .-` /  /              \\
//      ========`-.____`-.___\_____/___.-`____.-'========      \\
//                           `=---='                           \\
// //   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  \\ \\
// // //      佛祖保佑      永无BUG      永不修改        \\ \\ \\
// // // // // // || || || || || || || || || || \\ \\ \\ \\ \\ */


#include "headfile.h"
#include "myfile.h"

//舵机极限值
int16 S3010_mid = 702;       //定义舵机中值
int16 S3010_Left_Max = 780;  //左边极限值，即舵机到这里不能再打了
int16 S3010_Right_Max = 620; //右边道理同左边

float Error = 0, Error_last = 0, Error_angle_out = 0, Steer_duty = 0; //[Error-差别和 angle_out-角度 Steer_duty-最终舵机输出占空比]
float Kp = 1.2, Kd = 2;                                               //差比和用的kp,kd;
//新分区用到的
float error_value = 0, error_value_old = 0, lor = 0, lor_last = 0, reduce = 0, plus = 0, spaceflag = 95, ratio = 0, ad_referens = 100, abserror = 0, rp = 0;
float Difference_error = 0; //误差的误差
uint8 space_flag = 0;     
//三岔标志位
int8 three_on = 0, three_in_L = 0, three_in_R = 0, numbe = 1; //分别是 识别到三岔 进入到三岔里 出三岔 计数
//圆环标志位
int8 Island_Left=0;
int8 Island_Right=0;
int Island_time = 0;
uint8 Huan_finish_count = 0; //环计数//Duan
//十字标志位
int8 shizi = 0;
float shizi_p = 1.2, shizi_d = 3.0;
//直道pd
float zhidao_p = 1.20, zhidao_d = 4.0;
//圆环PD
float ruhuan_p = 3.2, ruhuan_d = 2.8;
float chuhuan_p = 3.8, chuhuan_d = 2.3;
float huanz_p = 1.5, huanz_d = 8;

int SL_In_xishu = 470, SL_Out_xishu = 15; //左小环入环系数、出环系数，左大环入环系数、出环偏置值
int SR_In_xishu = 470, SR_Out_xishu = 15; //右小环入环系数、出环系数，右大环入环系数、出环偏置值
//编码器积分路程用到的变量
float road_L = 0, road_R = 0, road_sum = 0;
//差比和用的系数
short a = 55; //空间2区
short b = 400;
float error_heng = 0, error_xie = 0;
//出入库标志位
int8 library = 1;      //控制出库打角，也可用拨码控
uint8 out_garage = 0, out_ku = 0;
int cnt = 0, ruku_time = 60;
int16 yaw_ruku = 0;
float ruku_lucheng = 0;
int16 yaw_chuku = 0;
uint8 inku = 0;
//陀螺仪
int16 yaw_error = 0;

//偏航角运用
int16 yaw_angle = 0, yaw_fork = 0;
int16 yaw_different = 0;


//三岔pid
float cha_zuo_p = 1, cha_zuo_d = 8.0; // 780
float cha_you_p = 1.2, cha_you_d = 8.0;
int fork_time = 0;
//坡道变量
int8 Ramp = 0;
int16 pitch_poing = 0;
int ramp_time = 0;  //坡道定时


uint8 Po_finish_count = 0;

//模板匹配用的
int8 rank = 0;

/*********************************************
 *函数：区域解算函数（旧）
 *函数名：Position_Jud()
 *备注：
 *日期：
 *修改日期：
 *********************************************/
void Position_Jud()
{
    int16 i;
    Read_ADC();
    for (i = 0; i < 7; i += 3)
    {
        if (GUI_AD[Max_Front] < GUI_AD[i] - 5)
            Max_Front = i;
    }

    Position_Transit[0] = 88; //偏离0号传感器时3号传感器的值 //37
    Position_Transit[1] = 88; //偏离5号传感器时3号传感器的值 //45

    if (Max_Front == 0 && MAD <= Position_Transit[0] - 1)
    {
        Position = 0;
    }
    else if (Max_Front == 0 && MAD >= Position_Transit[0] + 1 || Max_Front == 3 && ZLAD - ZRAD > 1)
    {
        Position = 1;
    }
    else if (Max_Front == 6 && MAD >= Position_Transit[1] + 1 || Max_Front == 3 && ZRAD - ZLAD > 1)
    {
        Position = 2;
    }
    else if (Max_Front == 6 && MAD <= Position_Transit[1] - 1)
    {
        Position = 3;
    }
    if (abs(Position - Position_last) == 3) //前排位置防跳变   防止临近赛道干扰
    {
        Position = Position_last;
    }
    else
    {
        Position_last = Position;
    }
}
/*********************************************
 *函数：执行函数
 *函数名：caculation()
 *备注：
 *修改日期：
 *********************************************/
void caculation()
{
    error_heng = (QLAD - QRAD) / (QLAD + QRAD);
    error_xie = (XLAD - XRAD) / (XLAD + XRAD);
    Position_Jud();
    ZW_judge();
    Circular_zuo();
    Circular_syou();
    Three_branch_road();
    podao();
}

/*********************************************
 *函数：分区新算法函数
 *函数名：position_new()
 *备注：2022/05/30
 *修改日期：
 *********************************************/
void position_new()
{
    Read_ADC();
    abserror = abs(ad_referens - MAD);
    ratio = (abserror / ad_referens) * a; // a=50
    Difference_error = error_value - error_value_old;
    if (space_flag == 1 && (Position == 1 || Position == 2))
    {
        // BEEP = 0;
        base = base_straight;
        reduce = sqrt(ZLAD) - sqrt(ZRAD);
        plus = ZLAD + ZRAD + MAD;
        rp = (reduce / plus) * b; // b=420;
        error_value_old = error_value;
        error_value = rp;
        Kp = zhidao_p;
        Kd = zhidao_d;
        Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        yaw_different = 0;
    }
    if (space_flag == 2)
    {
        if (error_heng < -0.23 && error_xie < -0.47)     //右弯
        {
            lor = -1;
            error_value_old = error_value;
            error_value = lor * ratio;
            Kp = Fuzzy_P(error_value, Difference_error);
            Kd = Fuzzy_D(error_value, Difference_error);
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }
        if (error_heng > 0.23 && error_xie > 0.27)      //左弯
        {

            lor = 1;
            error_value_old = error_value;
            error_value = lor * ratio;
            Kp = Fuzzy_P(error_value, Difference_error);
            Kd = Fuzzy_D(error_value, Difference_error);
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }
    }
    if (space_flag == 4)
    {
        /**********************左环*********************/
        if (Island_Left == 2)    //入环
        {
            // base = 170;
            error_value_old = error_value;
            error_value = ((sqrt(ZLAD) * 1.55 - sqrt(ZRAD) * 0.45) * SL_In_xishu) / (ZLAD + ZRAD); // 500
            Kp = ruhuan_p + 0.3;
            Kd = ruhuan_d + 0.3;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
            yaw_error = Yaw - yaw_angle;
        }
        if (Island_Left == 3)   //在环中使用弯道循迹
        {
            // base = 170;
            error_value_old = error_value;
            error_value = ratio;
            // Difference_error = error_value - error_value_old;
            // Kp = Fuzzy_P(error_value, Difference_error);
            // Kd = Fuzzy_D(error_value, Difference_error);
            Kp = huanz_p;
            Kd = huanz_d;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }
        if (Island_Left == 4)    //出环
        {
            BEEP = 0;
            error_value_old = error_value;
            error_value = ratio + SL_Out_xishu;   //我的出环是在弯道循迹的基础上手动加误差值
                                            //也可用电感出环，建议使用短前瞻出环
            // error_value = ((sqrt(ZLAD) * 1.55 - sqrt(ZRAD) * 0.45) * 350) / (ZLAD + ZRAD);
            Kp = chuhuan_p;
            Kd = chuhuan_d;
            // Kp = ruhuan_p - 0.8;
            // Kd = ruhuan_d - 0.6;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }
        //***************右环*****************//
        if (Island_Right == 2)     //入环
        {
            error_value_old = error_value;
            error_value = ((sqrt(ZLAD) * 0.45 - sqrt(ZRAD) * 1.55) * SR_In_xishu) / (ZLAD + ZRAD); // 500
            Kp = ruhuan_p;
            Kd = ruhuan_d;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
            yaw_error = Yaw - yaw_angle;
        }
        if (Island_Right == 3)    //在环中
        {
            // base = 170;
            error_value_old = error_value;
            error_value = -(ratio);
            // Difference_error = error_value - error_value_old;
            // Kp = Fuzzy_P(error_value, Difference_error);
            // Kd = Fuzzy_D(error_value, Difference_error);
            Kp = huanz_p;
            Kd = huanz_d;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }
        if (Island_Right == 4)   //出环
        {
            BEEP = 0;
            error_value_old = error_value;
            error_value = -(ratio + SR_Out_xishu);
            // error_value = ((sqrt(ZLAD) * 0.45 - sqrt(ZRAD) * 1.55) * 350) / (ZLAD + ZRAD);
            // Kp = ruhuan_p - 1.2;
            // Kd = ruhuan_d - 1.2;
            Kp = chuhuan_p;
            Kd = chuhuan_d;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }

       //三岔处理
        if (three_on == 1 && space_flag == 4)    //入岔固定打角
        {
            if (numbe % 2 == 0)
            {
                Error_angle_out = 75;
            }
            else if (numbe % 2 != 0)
            {
                Error_angle_out = -75;
            }
            yaw_different = abs(Yaw - yaw_fork);
        }
        if (three_in_L == 1)     //左岔处理
        {
            BEEP = 0;
            error_value_old = error_value;
            error_value = ((sqrt(XLAD)) * 1.2 - 1.2 * (sqrt(XRAD)) + 0.8 * (sqrt(ZLAD)) - 0.8 * (sqrt(ZRAD))) * 600 / (XLAD + XRAD + ZLAD + ZRAD + MAD);
            Kp = cha_zuo_p;
            Kd = cha_zuo_d;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }
        if (three_in_R == 1)    //右岔处理
        {
            BEEP = 0;
            error_value_old = error_value;
            error_value = ((sqrt(XLAD)) * 1.2 - 1.2 * (sqrt(XRAD)) + 0.8 * (sqrt(ZLAD)) - 0.8 * (sqrt(ZRAD))) * 600 / (XLAD + XRAD + ZLAD + ZRAD + MAD);
            Kp = cha_zuo_p;
            Kd = cha_zuo_d;
            Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        }
    }
    //坡道处理
    if (Ramp == 1)
    {
        base = base_ramp;
    }
   

    //模板匹配需用到的，rank值清"0"才能跑第2圈
    // if (element_sum == rank)
    // {
    //     rank = 0;
    // }
}

/*********************************************
 *函数：模糊pid函数
 *函数名：mohu_pid()
 *备注：要测量 误差值 误差的差值
 *日期：2022/05/30
 *修改日期：
 *********************************************/
float Fuzzy_P(float E, float EC)
{
    /*输入量P语言值特征点*/
    float EFF[7] = {-56, -20, -10, 0, 10, 20, 56};    //Error范围

    /*输入量D语言值特征点*/
    float DFF[7] = {-2.5, -1.5, -0.5, 0, 0.5, 1.5, 2.5};  // 误差变化率范围

    /*输出量U语言值特征点(根据赛道类型选择不同的输出值)*/
    float UFF[7] = {1.7, 1.8, 1.9, 2.0, 2.1, 2.8, 3}; // 1.15 2  2.2 2.4 2.6 2.8 3 4}
    // float UFF[7] = {2.0, 2.1, 2.2, 2.4, 2.8, 2.8, 3};
    int rule[7][7] = {
        {6, 5, 4, 3, 2, 1, 0},                           //规则表，不建议修改
        {5, 4, 3, 2, 1, 0, 1},
        {4, 3, 2, 1, 0, 1, 2},
        {3, 2, 1, 0, 1, 2, 3},
        {2, 1, 0, 1, 2, 3, 4},
        {1, 0, 1, 2, 3, 4, 5},
        {0, 1, 2, 3, 4, 5, 6},
    };

    float U = 0;                                 /*偏差,偏差微分以及输出值的精确量*/
    float PF[2] = {0}, DF[2] = {0}, UF[4] = {0}; //偏差,偏差微分以及输出值的隶属度

    int Pn = 0, Dn = 0, Un[4] = {0};
    float t1 = 0, t2 = 0, t3 = 0, t4 = 0, temp1 = 0, temp2 = 0;
    /*隶属度的确定*/
    /*根据PD的指定语言值获得有效隶属度*/
    if (E > EFF[0] && E < EFF[6])
    {
        if (E <= EFF[1])
        {
            Pn = -2;
            PF[0] = (EFF[1] - E) / (EFF[1] - EFF[0]);
        }
        else if (E <= EFF[2])
        {
            Pn = -1;
            PF[0] = (EFF[2] - E) / (EFF[2] - EFF[1]);
        }
        else if (E <= EFF[3])
        {
            Pn = 0;
            PF[0] = (EFF[3] - E) / (EFF[3] - EFF[2]);
        }
        else if (E <= EFF[4])
        {
            Pn = 1;
            PF[0] = (EFF[4] - E) / (EFF[4] - EFF[3]);
        }
        else if (E <= EFF[5])
        {
            Pn = 2;
            PF[0] = (EFF[5] - E) / (EFF[5] - EFF[4]);
        }
        else if (E <= EFF[6])
        {
            Pn = 3;
            PF[0] = (EFF[6] - E) / (EFF[6] - EFF[5]);
        }
    }

    else if (E <= EFF[0])
    {
        Pn = -2;
        PF[0] = 1;
    }
    else if (E >= EFF[6])
    {
        Pn = 3;
        PF[0] = 0;
    }

    PF[1] = 1 - PF[0];

    //判断D的隶属度
    if (EC > DFF[0] && EC < DFF[6])
    {
        if (EC <= DFF[1])
        {
            Dn = -2;
            DF[0] = (DFF[1] - EC) / (DFF[1] - DFF[0]);
        }
        else if (EC <= DFF[2])
        {
            Dn = -1;
            DF[0] = (DFF[2] - EC) / (DFF[2] - DFF[1]);
        }
        else if (EC <= DFF[3])
        {
            Dn = 0;
            DF[0] = (DFF[3] - EC) / (DFF[3] - DFF[2]);
        }
        else if (EC <= DFF[4])
        {
            Dn = 1;
            DF[0] = (DFF[4] - EC) / (DFF[4] - DFF[3]);
        }
        else if (EC <= DFF[5])
        {
            Dn = 2;
            DF[0] = (DFF[5] - EC) / (DFF[5] - DFF[4]);
        }
        else if (EC <= DFF[6])
        {
            Dn = 3;
            DF[0] = (DFF[6] - EC) / (DFF[6] - DFF[5]);
        }
    }
    //不在给定的区间内
    else if (EC <= DFF[0])
    {
        Dn = -2;
        DF[0] = 1;
    }
    else if (EC >= DFF[6])
    {
        Dn = 3;
        DF[0] = 0;
    }

    DF[1] = 1 - DF[0];

    /*使用误差范围优化后的规则表rule[7][7]*/
    /*输出值使用13个隶属函数,中心值由UFF[7]指定*/
    /*一般都是四个规则有效*/
    Un[0] = rule[Pn + 2][Dn + 2];
    Un[1] = rule[Pn + 3][Dn + 2];
    Un[2] = rule[Pn + 2][Dn + 3];
    Un[3] = rule[Pn + 3][Dn + 3];

    if (PF[0] <= DF[0]) //求小
        UF[0] = PF[0];
    else
        UF[0] = DF[0];
    if (PF[1] <= DF[0])
        UF[1] = PF[1];
    else
        UF[1] = DF[0];
    if (PF[0] <= DF[1])
        UF[2] = PF[0];
    else
        UF[2] = DF[1];
    if (PF[1] <= DF[1])
        UF[3] = PF[1];
    else
        UF[3] = DF[1];
    /*同隶属函数输出语言值求大*/
    if (Un[0] == Un[1])
    {
        if (UF[0] > UF[1])
            UF[1] = 0;
        else
            UF[0] = 0;
    }
    if (Un[0] == Un[2])
    {
        if (UF[0] > UF[2])
            UF[2] = 0;
        else
            UF[0] = 0;
    }
    if (Un[0] == Un[3])
    {
        if (UF[0] > UF[3])
            UF[3] = 0;
        else
            UF[0] = 0;
    }
    if (Un[1] == Un[2])
    {
        if (UF[1] > UF[2])
            UF[2] = 0;
        else
            UF[1] = 0;
    }
    if (Un[1] == Un[3])
    {
        if (UF[1] > UF[3])
            UF[3] = 0;
        else
            UF[1] = 0;
    }
    if (Un[2] == Un[3])
    {
        if (UF[2] > UF[3])
            UF[3] = 0;
        else
            UF[2] = 0;
    }
    t1 = UF[0] * UFF[Un[0]];
    t2 = UF[1] * UFF[Un[1]];
    t3 = UF[2] * UFF[Un[2]];
    t4 = UF[3] * UFF[Un[3]];
    temp1 = t1 + t2 + t3 + t4;
    temp2 = UF[0] + UF[1] + UF[2] + UF[3]; //模糊量输出
    U = temp1 / temp2;
    return U;
}
float Fuzzy_D(float E, float EC)
{
    /*输入量P语言值特征点*/
    float EFF[7] = {-56, -20, -10, 0, 10, 25, 56};
    /*输入量D语言值特征点*/
    float DFF[7] = {-2.5, -1.5, -0.5, 0, 0.5, 1.5, 2};
    /*输出量U语言值特征点(根据赛道类型选择不同的输出值)*/
    float UFF[7] = {2.3, 4.2, 8.2, 7, 6, 5, 4};
    // float UFF[7] = {0.6, 0.9, 1.2, 8, 7, 6, 5};

    int rule[7][7] = {
        {0, 1, 2, 3, 4, 5, 6},
        {1, 2, 3, 4, 5, 6, 5},
        {2, 3, 4, 5, 6, 5, 4},
        {3, 4, 5, 6, 5, 4, 3},
        {4, 5, 6, 5, 4, 3, 2},
        {5, 6, 5, 4, 3, 2, 1},
        {6, 5, 4, 3, 2, 1, 0},
    };

    float U = 0; /*偏差,偏差微分以及输出值的精确量*/
    float PF[2] = {0}, DF[2] = {0}, UF[4] = {0};
    /*偏差,偏差微分以及输出值的隶属度*/
    int Pn = 0, Dn = 0, Un[4] = {0};
    float t1 = 0, t2 = 0, t3 = 0, t4 = 0, temp1 = 0, temp2 = 0;
    /*隶属度的确定*/
    /*根据PD的指定语言值获得有效隶属度*/
    if (E > EFF[0] && E < EFF[6])
    {
        if (E <= EFF[1])
        {
            Pn = -2;
            PF[0] = (EFF[1] - E) / (EFF[1] - EFF[0]);
        }
        else if (E <= EFF[2])
        {
            Pn = -1;
            PF[0] = (EFF[2] - E) / (EFF[2] - EFF[1]);
        }
        else if (E <= EFF[3])
        {
            Pn = 0;
            PF[0] = (EFF[3] - E) / (EFF[3] - EFF[2]);
        }
        else if (E <= EFF[4])
        {
            Pn = 1;
            PF[0] = (EFF[4] - E) / (EFF[4] - EFF[3]);
        }
        else if (E <= EFF[5])
        {
            Pn = 2;
            PF[0] = (EFF[5] - E) / (EFF[5] - EFF[4]);
        }
        else if (E <= EFF[6])
        {
            Pn = 3;
            PF[0] = (EFF[6] - E) / (EFF[6] - EFF[5]);
        }
    }

    else if (E <= EFF[0])
    {
        Pn = -2;
        PF[0] = 1;
    }
    else if (E >= EFF[6])
    {
        Pn = 3;
        PF[0] = 0;
    }

    PF[1] = 1 - PF[0];

    //判断D的隶属度
    if (EC > DFF[0] && EC < DFF[6])
    {
        if (EC <= DFF[1])
        {
            Dn = -2;
            DF[0] = (DFF[1] - EC) / (DFF[1] - DFF[0]);
        }
        else if (EC <= DFF[2])
        {
            Dn = -1;
            DF[0] = (DFF[2] - EC) / (DFF[2] - DFF[1]);
        }
        else if (EC <= DFF[3])
        {
            Dn = 0;
            DF[0] = (DFF[3] - EC) / (DFF[3] - DFF[2]);
        }
        else if (EC <= DFF[4])
        {
            Dn = 1;
            DF[0] = (DFF[4] - EC) / (DFF[4] - DFF[3]);
        }
        else if (EC <= DFF[5])
        {
            Dn = 2;
            DF[0] = (DFF[5] - EC) / (DFF[5] - DFF[4]);
        }
        else if (EC <= DFF[6])
        {
            Dn = 3;
            DF[0] = (DFF[6] - EC) / (DFF[6] - DFF[5]);
        }
    }
    //不在给定的区间内
    else if (EC <= DFF[0])
    {
        Dn = -2;
        DF[0] = 1;
    }
    else if (EC >= DFF[6])
    {
        Dn = 3;
        DF[0] = 0;
    }

    DF[1] = 1 - DF[0];

    /*使用误差范围优化后的规则表rule[7][7]*/
    /*输出值使用13个隶属函数,中心值由UFF[7]指定*/
    /*一般都是四个规则有效*/
    Un[0] = rule[Pn + 2][Dn + 2];
    Un[1] = rule[Pn + 3][Dn + 2];
    Un[2] = rule[Pn + 2][Dn + 3];
    Un[3] = rule[Pn + 3][Dn + 3];

    if (PF[0] <= DF[0]) //求小
        UF[0] = PF[0];
    else
        UF[0] = DF[0];
    if (PF[1] <= DF[0])
        UF[1] = PF[1];
    else
        UF[1] = DF[0];
    if (PF[0] <= DF[1])
        UF[2] = PF[0];
    else
        UF[2] = DF[1];
    if (PF[1] <= DF[1])
        UF[3] = PF[1];
    else
        UF[3] = DF[1];
    /*同隶属函数输出语言值求大*/
    if (Un[0] == Un[1])
    {
        if (UF[0] > UF[1])
            UF[1] = 0;
        else
            UF[0] = 0;
    }
    if (Un[0] == Un[2])
    {
        if (UF[0] > UF[2])
            UF[2] = 0;
        else
            UF[0] = 0;
    }
    if (Un[0] == Un[3])
    {
        if (UF[0] > UF[3])
            UF[3] = 0;
        else
            UF[0] = 0;
    }
    if (Un[1] == Un[2])
    {
        if (UF[1] > UF[2])
            UF[2] = 0;
        else
            UF[1] = 0;
    }
    if (Un[1] == Un[3])
    {
        if (UF[1] > UF[3])
            UF[3] = 0;
        else
            UF[1] = 0;
    }
    if (Un[2] == Un[3])
    {
        if (UF[2] > UF[3])
            UF[3] = 0;
        else
            UF[2] = 0;
    }
    t1 = UF[0] * UFF[Un[0]];
    t2 = UF[1] * UFF[Un[1]];
    t3 = UF[2] * UFF[Un[2]];
    t4 = UF[3] * UFF[Un[3]];
    temp1 = t1 + t2 + t3 + t4;
    temp2 = UF[0] + UF[1] + UF[2] + UF[3]; //模糊量输出
    U = temp1 / temp2;
    return U;
}

/*********************************************
 *函数：直弯道识别函数
 *函数名：ZW_judge()
 *备注：用陀螺仪辅助出环
 *日期：2022/05/30
 *修改日期：
 *********************************************/
void ZW_judge()
{
    if (space_flag != 5 && space_flag != 4 && three_on == 0 && (((error_heng <= 0.23 || error_heng >= -0.23) && (error_xie <= 0.27 || error_xie >= -0.47)) || MAD > spaceflag))
    {
        space_flag = 1;
        // BEEP = 0;
    }
    if (MAD <= spaceflag && (error_heng > 0.23 || error_heng < -0.23) && (error_xie > 0.27 || error_xie < -0.47) && space_flag != 4 && three_on == 0 && space_flag != 5 && Ramp == 0)
    {
        space_flag = 2;
        // BEEP = 1;
    }
}
/*********************************************
 *函数：左小环标志位识别函数函数
 *函数名：Circular_zuo()
 *备注：用陀螺仪辅助出环
 *日期：2022/05/30
 *修改日期：
 *********************************************/

void Circular_zuo()
{
    if (!Po_control_Location && MAD > 165 && MAD <= 250 && QLAD > 130 && Island_Left == 0 && Ramp == 0) 
    {                                                                                                                                                                                                      
        Island_Left = 1;
    }
    //因为不同速度 入环点会不再同一个地方 因此需要分条件判断 MAD<188 || QLAD<98
    // if (Circular_BL1 == 1 && ((((FXLAD > 145 && FXLAD < 230)) && P63 == 1 && P61 == 0) || (P61 == 1 && P63 == 0 && (FXLAD > 140 && FXLAD < 235)) || (P61 == 1 && P63 == 1 && (FXLAD > 140 && FXLAD < 235)) || (P61 == 0 && P63 == 0 && (FXLAD > 135 && FXLAD < 250)))) // 185 || QLAD<97 MAD<188
    // {
    // space_flag = 4;
    //     Circular_BL1 = 0;
    //     Circular_BL2 = 1;
    //     // base = 160;
    //     yaw_angle = Yaw;
    //     BEEP = 0;
    // }
    if (FXLAD > 130 && FXLAD < 235 && MAD > 200 && MAD < 250 && FXLAD > FXRAD && (FSLAD - FSRAD) >= 27 && Island_Left == 1)
    {
        Island_Left = 2;
        space_flag = 4;
        // base = 160;
        yaw_angle = Yaw;
        BEEP = 0;
    }
    if (abs(Yaw - yaw_angle) > 25 && Island_Left == 2)
    {
        Island_Left = 3;
        yaw_error = 0;
        BEEP = 1;
    }
    if (Island_Left == 3 && abs(Yaw - yaw_angle) >= 270) //  XLAD>105
    {
        Island_Left = 4;
        BEEP = 0;
    }
    if (Island_Left == 4 && abs(Yaw - yaw_angle) >= 310) //
    {
        Island_Left = 5;
        yaw_angle = 0;
        three_on = 0;
        three_in_L = 0;
        three_in_R = 0;
        Huan_finish_count++;  // Duan
        if (MAD >= spaceflag) //在一区
        {
            space_flag = 1;
        }
        if (MAD < spaceflag)
        {
            space_flag = 2;
        }
    }
    if (Island_Left == 5 && Island_time > 150)
    {
        Island_Left = 0;
    }
}

void Circular_syou()
{
    if (!Po_control_Location && MAD > 160 && MAD <= 250 && QRAD > 110 && Island_Right == 0 && Ramp == 0) // 185 && Round_Circular_Left == 0
    {
        Island_Right = 1;
    }
    if (MAD > 190 && MAD <= 250 && FXRAD > 115 && FXRAD < 175 && FXRAD > FXLAD && (FSRAD - FSLAD) >= 25 && Island_Right == 1 ) 
    {
        Island_Right = 2;
        yaw_angle = Yaw;
        space_flag = 4;
        BEEP = 0;
    }
    if (abs(Yaw - yaw_angle) > 30 && Island_Right == 2)
    {
        Island_Right = 3;
        yaw_error = 0;
        BEEP = 1;
    }
    if (Island_Right == 3 && abs(Yaw - yaw_angle) >= 270) //  XLAD>105
    {
        Island_Right = 4;
        BEEP = 0;
    }
    if (Island_Right == 4 && abs(Yaw - yaw_angle) >= 330) //
    {
        Island_Right = 5;
        yaw_angle = 0;
        three_on = 0;
        three_in_L = 0;
        three_in_R = 0;
        Huan_finish_count++; // Duan
        if (MAD >= spaceflag) //在一区
        {
            space_flag = 1;
        }
        if (MAD < spaceflag)
        {
            space_flag = 2;
        }
    }

    //定时消环
    if (Island_Right == 5 && Island_time > 150)
    {
        Island_Right = 0;
    }
}

/*********************************************
 *函数：三岔识别函数函数
 *函数名：Three_branch_road()
 *备注：跑车时要把屏幕关掉。
 *日期：2022/05/30
 *修改日期：
 *********************************************/
void Three_branch_road()
{
    if (FXLAD >= 25 && FXLAD <= 70 && FXRAD >= 35 && FXRAD <= 85 && FSLAD >= 15 && FSLAD <= 38 && FMAD >= 40 && FMAD < 100 && QLAD < 70 && QRAD < 80 && three_in_L == 0 && three_in_R == 0 && three_on == 0 && Island_Left == 0 && Island_Right == 0 && Ramp == 0) // order[rank] == Tab_Fork 使用模板匹配时需添加
    {
        three_on = 1;
        space_flag = 4;
        BEEP = 1;
        yaw_fork = Yaw;
        Po_finish_count = 0;   //
        Huan_finish_count = 0; //
        if (numbe % 2 == 0)
        {
            base = 140;
        }
        if (numbe % 2 != 0)
        {
            base = 140;
            // BEEP=1;
        }
    }
    if (yaw_different >= 20 && three_on == 1 && (numbe % 2 == 0)) //消三岔
    {
        three_on = 0;
        three_in_L = 1;
        yaw_different = 0;
        base = base_fork;
    }
    if (yaw_different >= 20 && three_on == 1 && (numbe % 2 != 0)) //消三岔
    {
        three_on = 0;
        three_in_R = 1;
        yaw_different = 0;
        base = base_fork;
    }
    if (three_in_L == 1 && (FXLAD >= 90 || FSLAD >= 91))
    {
        three_in_L = 0;
        three_on = 0;
        base = 100;
        numbe = 1;
        space_flag = 2;
    }
    if (three_in_R == 1 && FXRAD >= 90 && FXLAD < 35)
    {
        three_in_R = 0;
        three_on = 0;
        Ramp = 0;
        base = 130;
        numbe = 0;
        space_flag = 2;
    }
}

/*********************************************
 *函数：坡道识别函数
 *函数名：podao()
 *备注：跑车时要把屏幕关掉。
 *日期：2022/08/11
 *修改日期：
 *********************************************/
void podao()
{
    if (Po_control_order == 0 && Po_control_Location == 0)
    {
        if (Pitch >= 4 && Ramp == 0 && MAD > 60)
        {
            Ramp = 1;
            pitch_poing = Pitch;
            BEEP = 1;
        }
        if (Ramp == 1 && (((Pitch - pitch_poing) <= -10) || ramp_time > 600))
        {
            Ramp = 0;
            BEEP = 0;
        }
    }
    else if (Po_finish_count == 0 && (Po_control_Location == 1 || Po_control_Location == 2))
    {
        if (Ramp == 0 && FMAD > 160)
        {
            Ramp = 1;
            BEEP = 1;
        }
        else if (Ramp == 1 && ramp_time > 600)
        {
            Ramp = 0;
            BEEP = 0;
            Po_finish_count++;
            Po_control_Location = 0;
        }
    }
}

/*********************************************
 *函数：十字识别函数(没用到)
 *函数名：cross_ten()
 *备注：跑车时要把屏幕关掉。
 *日期：2022/08/11
 *修改日期：
 *********************************************/
void cross_ten()
{
    if (shizi == 0 && FSLAD > 60 && FSRAD > 60 && space_flag != 4)
    {
        shizi = 1;
        // base = 185;
        BEEP = 1;
    }
    if (shizi == 1 && FSLAD < 15 && FSRAD < 15)
    {
        shizi = 2;
        // base = 170;
        BEEP = 0;
    }
    if (shizi == 2 && FSLAD > 40 && FSRAD > 40)
    {
        shizi = 3;
        BEEP = 1;
    }
    if (shizi == 3 && FSLAD < 12 && FSRAD < 12)
    {
        shizi = 0;
        // base = 175;
        BEEP = 0;
    }
}

/*********************************************
 *函数：标志位显示函数
 *函数名：ADC_show()
 *备注：跑车时要把屏幕关掉。
 *日期：2022/05/30
 *修改日期：
 *********************************************/
void scene_show()
{
    if (P53 == 0)
    {
        if (P70 == 0) //切换显示时按键刷新屏幕
        {
            delay_ms(10);
            if (P70 == 0)
            {
                while (P70 == 0)
                    ;
                oled_fill(0x00);
            }
        }
        if (P61 == 0)
        {
            dianganzhi_show();
        }
        else if (P61 == 1)
        {
            biaozhiwei_show();
        }
    }

    else if (P53 == 1)
    {
        oled_fill(0x00);
    }
}
void dianganzhi_show()
{
    oled_int16(10, 0, GUI_AD[0]);
    oled_int16(10, 1, GUI_AD[1]);
    oled_int16(10, 2, GUI_AD[2]);
    oled_int16(10, 3, GUI_AD[3]);
    oled_int16(10, 4, GUI_AD[4]);
    oled_int16(10, 5, GUI_AD[5]);
    oled_int16(10, 6, GUI_AD[6]);
    oled_int16(10, 7, GUI_AD[7]);
    oled_int16(50, 0, GUI_AD[8]);
    oled_int16(50, 1, GUI_AD[9]);
    oled_int16(50, 2, GUI_AD[10]);
    oled_int16(50, 3, GUI_AD[11]);
}
void biaozhiwei_show()
{
    oled_p6x8str(0, 0, "SL");

    oled_p6x8str(60, 0, "SR");
    oled_p6x8str(0, 4, "SC");
    oled_p6x8str(60, 4, "Po");
    oled_p6x8str(60, 7, "ZandW");

    oled_int16(10, 0, Island_Left);
    
    oled_int16(80, 0, Island_Right);
   
    oled_int16(10, 4, three_on);
    oled_int16(10, 5, three_in_L);
    oled_int16(10, 6, three_in_R);

    oled_int16(80, 4, Ramp);
    oled_int16(80, 5, pitch_poing);

    oled_int16(80, 7, space_flag);
}

/*********************************************
 *函数：舵机最终打角函数
 *函数名：S3010_Direation_Control()
 *备注：
 *日期：
 *修改日期：
 *********************************************/

void S3010_Direation_Control() //舵机
{
    caculation();
    position_new();
    if (Error_angle_out > 80) //舵机打角限幅
        Error_angle_out = 80;
    if (Error_angle_out < -80)
        Error_angle_out = -80;
    Steer_duty = (Error_angle_out + S3010_mid);
    if (Steer_duty > S3010_Left_Max)
        Steer_duty = S3010_Left_Max; //舵机占空比输出限幅 防止舵机烧
    if (Steer_duty < S3010_Right_Max)
        Steer_duty = S3010_Right_Max;
    pwm_duty(PWMB_CH1_P74, Steer_duty); //舵机打角函数，可以通过改变Steer_duty来得到舵机中值
}

/*********************************************
 *函数：出入库函数
 *函数名：Out_storage()/In_ku()
 *备注：
 *日期：2022.06.16
 *修改日期：
 *********************************************/
void Out_storage()
{
    if (out_ku == 0)
    {
        base = 200;
        if (road_sum >= 0.1 && out_garage == 0)
        {
            yaw_chuku = Yaw;
            base = 220;
            out_garage = 1;
        }
        if (out_garage == 1)
        {
            if (library == 0)
            {
                Error_angle_out = -80;
                exp_speed_r = exp_speed_r * (float)(Error_angle_out * (0.008f) + 0.68f);
                exp_speed_l = -(base);
            }
            else if (library != 0)
            {
                Error_angle_out = 80;
                exp_speed_l = exp_speed_l * (float)(Error_angle_out * (-0.008f) + 0.68f);
                exp_speed_r = base;
            }
            Steer_duty = (Error_angle_out + S3010_mid);
            pwm_duty(PWMB_CH1_P74, Steer_duty);
            if (abs(Yaw - yaw_chuku) >= 50)
            {
                out_ku = 1;
                out_garage = 0;
            }
        }
    }
}
void In_ku()
{
    Read_ADC();
    if (out_ku == 2 && inku == 0)
    {
        ruku_lucheng = road_sum;
        base = 130;
        inku = 1;
        reduce = sqrt(QLAD) - sqrt(QRAD) + sqrt(XLAD) - sqrt(XLAD);
        plus = QLAD + QRAD + MAD + XLAD + XRAD;
        rp = (reduce / plus) * b; // b=420;
        error_value_old = error_value;
        error_value = rp;
        Kp = 1.2;
        Kd = 3.0;
        Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        Steer_duty = (Error_angle_out + S3010_mid);
        pwm_duty(PWMB_CH1_P74, Steer_duty);
    }
    if (inku == 1)
    {
        if (road_sum - ruku_lucheng > 0.25) // 140
        {
            BEEP = 1;
            base = -130;
            ruku_lucheng = 0;
            inku = 2;
        }
    }
    if (inku == 2)
    {
        reduce = sqrt(QLAD) - sqrt(QRAD) + sqrt(XLAD) - sqrt(XLAD);
        plus = QLAD + QRAD + MAD + XLAD + XRAD;
        rp = (reduce / plus) * b; // b=420;
        error_value_old = error_value;
        error_value = rp;
        Kp = 1.2;
        Kd = 3.0;
        Error_angle_out = Kp * error_value + Kd * (error_value - error_value_old);
        Steer_duty = (Error_angle_out + S3010_mid);
        pwm_duty(PWMB_CH1_P74, Steer_duty);
        cnt += 1;
        if (cnt > ruku_time)
        {
            cnt = 0;
            inku = 3;
        }
    }
    if (inku == 3)
    {
        if (library == 0)
        {
            Error_angle_out = -72;
        }
        else if (library != 0)
            Error_angle_out = 72;
        Steer_duty = (Error_angle_out + S3010_mid);
        pwm_duty(PWMB_CH1_P74, Steer_duty);
        base = -200;
        yaw_chuku = Yaw;
        inku = 4;
    }
    if (abs(Yaw - yaw_chuku) >= 65 && inku == 4)
    {
        Steer_duty = (S3010_mid);
        pwm_duty(PWMB_CH1_P74, Steer_duty);
        BEEP = 1;
        ruku_lucheng = road_sum;
        inku = 5;
    }
    if (inku == 5)
    {
        base = -200;
        if ((road_sum - ruku_lucheng) < (-0.6))
        {
            base = 0;
            BEEP = 0;
        }
    }
}
