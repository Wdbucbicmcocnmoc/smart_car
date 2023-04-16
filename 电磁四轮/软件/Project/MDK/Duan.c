#include "headfile.h"
#include "myfile.h"

int8 Po_control_order = 0;
uint8 Po_control_Location = 0;

void Po_mode_switch()
{
	if (Po_control_order == 0) //不询问坡的位置
	{
		Po_control_Location = 0; //
	}
	else if (Po_control_order == 1) //询问坡是否是作为中间电感第一个可以增加的地方、即他的前面没有环
	{
		if (Huan_finish_count == 0 && Po_finish_count == 0) //环圈数为0
		{
			Po_control_Location = 1;
		}
	}
	else if (Po_control_order == 2) //询问坡是否是作为中间电感第二个可以增加的地方、即在他之前会过一次环
	{
		if (Huan_finish_count == 1 && Po_finish_count == 0) //环圈数为1
		{
			Po_control_Location = 2;
		}
	}
	// else if (Po_control_order==3)  //询问坡是否是作为中间电感第三个可以增加的地方、即在他之前会过两次环
	// {
	// 	if(Huan_finish_count==2 && Po_finish_count==0)
	// 	{
	// 		Po_control_Location = 3;
	// 	}
	// }
}

