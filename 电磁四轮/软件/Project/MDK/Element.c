#include "headfile.h"
#include "myfile.h"

extern uint8 out_ku;

int8 element_model = 0, element_sum = 0;
int order[] = {3};
int templet[] = {3};
int Tab_straight = 11, Tab_BIsland_Left = 801, Tab_BIsland_Right = 802, Tab_Fork = 3, Tab_ramp = 20;
int Tab_SIsland_Left = 501,Tab_SIsland_Right = 502;
void Element_key()    //模板匹配
{
    int t;
    if (P63 == 0)
        element_model = 1;
    else
        element_model = 0;
    if (out_ku == 1)
    {
        if (element_model == 0)
        {
            element_sum = sizeof(order) / sizeof(order[0]);
            for (t = element_sum - 1; t >= 0; t--)
            {
                order[t] = 0;
            }
            Tab_Fork = 0, Tab_BIsland_Left = 0, Tab_BIsland_Right = 0, Tab_SIsland_Left = 0, Tab_SIsland_Right = 0;
            element_model = 2;
        }
        else if (element_model == 1)
        {
            Tab_Fork = 3, Tab_BIsland_Left = 801, Tab_BIsland_Right = 802,Tab_SIsland_Left = 501, Tab_SIsland_Right = 502;
            element_sum = sizeof(order) / sizeof(order[0]);
            for (t = 0; t < element_sum; t++)
            {
                order[t] = templet[t];
            }
            element_model = 2;
        }
    }
}