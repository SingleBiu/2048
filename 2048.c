/*
 * @Author: SingleBiu
 * @Date: 2021-05-21 12:01:15
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-07-09 16:18:15
 * @Description: file content
 */


#include <stdio.h>
#include <stdlib.h>
#include "2048.h"
#include "bmp.h"
#include "lcd.h"
#include "ts.h"

int value_max = 0; //最高分
int value = 0; //分数


int matrix_2048[number][number] = 
{
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
};
//游戏主循环

int matrix_2048_copy[number][number];
int get_zero_num(void)
{
	int i, j;
	int n = 0;

	for (i = 0; i < number ; i++)
	{
		for (j = 0; j < number ;j++)
		{
			if (matrix_2048[i][j] == 0)
			{
				n++;
			}
		}
	}
	return n;
}


//在二维数组matrix_2048的随机的空白位置上
//填充一个随机的数字 
void fill_a_number(void)
{
	int i, j;
	int n =0;
	int zero_num = get_zero_num();
	if (zero_num == 0)
	{
		return ;
	}
	int pos; //第pos个0的位置为填充位置
	pos =	random() % zero_num  + 1 ; //[1, zero_num]
	for (i = 0; i < number ; i++)
	{
		for (j = 0; j < number; j++)
		{
			if (matrix_2048[i][j] == 0)
			{
				n++;
				if (n == pos)
				{
					//定义一个数组来用于随机出现2,4,8
					int num[4]={2,2,4,8};
					pos = random()%4;
					matrix_2048[i][j] =num[pos];
					return ;
				}
			}
		}
	}

}
//画棋盘矩阵
void draw_matrix(void)
{
	int i,j;
	int x=0;
	int y=0;
	for (i = 0; i < number;i++)
	{
		y=Size*i+space*i+startx0;
		for(j=0;j<number;j++)
		{
			x=Size*j+space*j+statry0;
			if (matrix_2048[i][j] == 0)
			lcd_draw_rectanle(x,y, Size, Size,0xffffff);
			else
			{
				char filename[256];
				sprintf(filename, "color_x80_%d.bmp", matrix_2048[i][j]);				
				bmp_display(filename, x, y);
			}
		}
	}	
}
void Change_up(int a)
{
	int i;
	int b[number];
	for(i=0;i<number;i++)
	{
		b[i]=matrix_2048[i][a];
	}
	int j = 1;
	int k = 0;
	for (; j < 4; j++) 
	{  
		//找出k第一个不为0的块，之后分为三种情况
		if (b[j] > 0) 
		{
			//移动
			 if (b[k] == 0) 
			{ 
				b[k] = b[j];
	            b[j] = 0;
			}
			 //合并
			else if (b[k] == b[j])
			{
				b[k] = 2 * b[k];
				b[j] = 0;
				k = k + 1;

				value += 2;
			}
			 //碰撞
			else
			{ 
				b[k + 1] = b[j];
				if (j != k + 1) 
				{ 
					b[j] = 0;
				}
				k = k + 1;
			}
		}
	}
	for(i=0;i<number;i++)
	{
		matrix_2048[i][a]=b[i];
	}
}
void Change_down(int a)
{
	int i;
	int b[number];
	for(i=0;i<number;i++)
	{
		b[i]=matrix_2048[i][a];
	}
	int j = 2;
	int k =3;
	for (; j>=0; j--) 
	{  
		//找出k第一个不为0的块，之后分为三种情况
		if (b[j] > 0) 
		{
			//移动
			 if (b[k] == 0) 
			{ 
				b[k] = b[j];
	            b[j] = 0;
			}
			 //合并
			else if (b[k] == b[j])
			{
				b[k] = 2 * b[k];
				b[j] = 0;
				k = k - 1;

				value += 2;
			}
			 //碰撞
			else
			{ 
				b[k - 1] = b[j];
				if (j != k - 1) 
				{ 
					b[j] = 0;
				}
				k = k - 1;
			}
		}
	}
	for(i=0;i<number;i++)
	{
		matrix_2048[i][a]=b[i];
	}
}
void Change_left(int a)
{
	int i;
	int b[number];
	for(i=0;i<number;i++)
	{
		b[i]=matrix_2048[a][i];
	}
	int j = 1;
	int k = 0;
	for (; j < 4; j++) 
	{  
		//找出k第一个不为0的块，之后分为三种情况
		if (b[j] > 0) 
		{
			//移动
			 if (b[k] == 0) 
			{ 
				b[k] = b[j];
	            b[j] = 0;
			}
			 //合并
			else if (b[k] == b[j])
			{
				b[k] = 2 * b[k];
				b[j] = 0;
				k = k + 1;

				value += 2;
			}
			 //碰撞
			else
			{ 
				b[k + 1] = b[j];
				if (j != k + 1) 
				{ 
					b[j] = 0;
				}
				k = k + 1;
			}
		}
	}
	for(i=0;i<number;i++)
	{
		matrix_2048[a][i]=b[i];
	}
}
void Change_right(int a)
{
	int i;
	int b[number];
	for(i=0;i<number;i++)
	{
		b[i]=matrix_2048[a][i];
	}
	int j = 2;
	int k =3;
	for (; j>=0; j--) 
	{  
		//找出k第一个不为0的块，之后分为三种情况
		if (b[j] > 0) 
		{
			//移动
			 if (b[k] == 0) 
			{ 
				b[k] = b[j];
	            b[j] = 0;
			}
			 //合并
			else if (b[k] == b[j])
			{
				b[k] = 2 * b[k];
				b[j] = 0;
				k = k - 1;

				value += 2;
			}
			 //碰撞
			else
			{ 
				b[k - 1] = b[j];
				if (j != k - 1) 
				{ 
					b[j] = 0;
				}
				k = k - 1;
			}
		}
	}
	for(i=0;i<number;i++)
	{
		matrix_2048[a][i]=b[i];
	}
}

int change_matrix(int mv)
{
	int i,j;
	int key =1;
	for (i = 0; i < number; ++i)
	{
		for (j = 0; j < number; ++j)
		{
			matrix_2048_copy[i][j]=matrix_2048[i][j];
		}
	}
	if(mv == MOVE_UP)
	{
		for (j = 0; j < number;j++)
		{
			for(i=0;i<number-1;i++)
			{
				Change_up(j);
			}
			
		}
	}
	if(mv==MOVE_DOWN)
	{
		for (j = 0; j < number;j++)
		{
			for(i=0;i<number-1;i++)
			{
				Change_down(j);
			}
			
		}
	}
	if(mv==MOVE_LEFT)
	{
		for (i = 0; i < number;i++)
		{
			for(j=0;j<number-1;j++)
			{
				Change_left(i);
			}
			
		}
	}
	if(mv==MOVE_RIGHT)
	{
		for (i = 0; i < number;i++)
		{
			for(j=0;j<number-1;j++)
			{
				Change_right(i);
			}
			
		}
	}
	draw_matrix();

	for (i = 0; i < number; ++i)
	{
		for (j = 0; j < number; ++j)
		{
			if(matrix_2048_copy[i][j]!=matrix_2048[i][j])
			{
				return 0;
			}	
		}
	}
	return 1;
}

int game_is_over()
{
    if(get_zero_num()>0)
    {
    	return 0;
    }
	int i,j;
	for (i = 0; i < number; ++i)
	{
		for (j = 0; j < number; ++j)
		{
			if(matrix_2048[i][j]==matrix_2048[i+1][j]&&i!=3)return 0;		
			else if(matrix_2048[i][j]==matrix_2048[i][j+1]&&j!=3)return 0;
			else if(matrix_2048[i][j]==matrix_2048[i-1][j]&&i!=0)return 0;
			else if(matrix_2048[i][j]==matrix_2048[i][j-1]&&j!=0)return 0;
		}
	}
	return 1;
}
void game_2048()
{
	
	//1. 初始化matrix_2048并显示
	int pos;
	pos = random()%3+1;
	int i,j ;
	for(i=0;i<pos;i++)
	{
		fill_a_number();
		draw_matrix();
	}
	//游戏主循环
	while (1)
	{
		// 等待用户输入(手指滑动，或 键盘按键)	
		int mv = get_user_input();
		// 根据用户的输入(左，右，上，下)来变换矩阵		
		// if : 矩阵有变动
		//随机在空白位置上填充1-3个数字
		//在屏幕画矩阵
		// lcd_clear_screen(0x555555);
		lcd_draw_rectanle(0,0,120,480,0x555555);
		change_matrix(mv);

		fill_a_number();	
		draw_matrix();

		lcd_draw_digit(value,0,0,0xffff);
		lcd_draw_digit(value_max,0,100,0xffff);

		// 判断游戏是否结束
		if (game_is_over())
		{
			char filename[256]="game_over_300x150.bmp";
			bmp_display(filename,200, 85);
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					matrix_2048[i][j]=0;
				}
			
			}
			if (value > value_max)
			{
				value_max = value;
			}
			value = 0;
			break;
			
		}
	}
	
}


