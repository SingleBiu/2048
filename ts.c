/*
 * @Author: SingleBiu
 * @Date: 2021-05-21 12:02:09
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-07-09 16:19:23
 * @Description: file content
 */

#include <linux/input.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "ts.h"
#include <math.h>
#include<stdlib.h>


/*
	get_user_input:获取用户移动的方向
	无参数：
		返回值：
		    MOVE_LEFT     //向左
			MOVE_RIGHT   //向右
			MOVE_UP     //向上
		    MOVE_DOWN    //向下
*/
int get_user_input()
{
	// int fd = open("/dev/ubuntu_event", O_RDONLY);
	int fd = open("/dev/input/event0", O_RDONLY);
	if (fd == -1)
	{
		printf("failed to open /dev/input/event0\n");
		return -1;
	}

	int x1 = -1, y1 = -1; //一次滑动过程中的，起点的坐标
	int x2, y2; //一次滑动过程中的，终点的坐标
	struct input_event ev;

	while (1)
	{
		int r = read(fd, &ev, sizeof(ev));
		if (r != sizeof(ev))
		{
			continue;
		}


		//ev是一个x轴坐标事件
		if (ev.type == EV_ABS &&  ev.code == ABS_X)
		{	
			if (x1 == -1)
			{	
				x1 = ev.value ; //就是x轴的坐标值
			}
			x2 = ev.value;
		}

		
		//ev是一个y轴坐标事件
		if (ev.type == EV_ABS &&  ev.code == ABS_Y)
		{	
			if (y1 == -1)
			{	
				y1 = ev.value ; //就是x轴的坐标值
			}
			y2 = ev.value;
		}

		//弹起事件

		if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value == 0)
		{
			int delt_x = abs(x2 - x1);
			int delt_y = abs(y2 - y1);

			if (delt_x > 2 *delt_y)
			{
				close(fd);
				if (x2 > x1)
				{
					return MOVE_RIGHT;
				}
				else
				{
					return MOVE_LEFT;
				}
			}
			else if (delt_y > 2*delt_x)
			{
				close(fd);
				if (y2 > y1)
				{
					return MOVE_DOWN;
				}
				else
				{
					return MOVE_UP;
				}
			}
			else
			{
				x1 = -1;
				y1 = -1;
			}

		}
	}
}

