/*
 * @Author: SingleBiu
 * @Date: 2021-05-21 12:02:09
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-05-21 12:22:23
 * @Description: file content
 */
#ifndef  __TS_H__
#define  __TS_H__
/*
	get_user_input:获取用户移动的方向
	无参数：
		返回值：
		    MOVE_LEFT     //向左
			MOVE_RIGHT   //向右
			 MOVE_UP     //向上
		   MOVE_DOWN    //向下
*/
#define MOVE_UP 1
#define MOVE_DOWN 2
#define MOVE_LEFT 3
#define MOVE_RIGHT 4

int get_user_input();


#endif



