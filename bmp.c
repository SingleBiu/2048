/*
 * @Author: SingleBiu
 * @Date: 2021-05-21 12:02:09
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-07-09 16:18:04
 * @Description: file content
 */


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <math.h>
#include <stdlib.h>

#include "lcd.h"

void bmp_display(const char *filename, int x0, int y0)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		//printf("failed to open %s\n", filename);
		return ;
	}

	int width, height;
	short depth;

	//width
	lseek(fd, 0x12, SEEK_SET);
	read(fd, &width, 4);

	//height
	lseek(fd, 0x16, SEEK_SET);
	read(fd, &height, 4);

	//depth
	lseek(fd, 0x1c, SEEK_SET);
	read(fd, &depth, 2);


	//printf("%d * %d \n", width, height);
	//printf("depth: %d\n", depth);

	if ( !(depth == 24 || depth == 32))
	{
		printf("Sorry, Non-standard Bmp\n");
		return ;
	}


	//
	int total_bytes; //图片中整个像素数组的字节数
	int line_bytes_valid; //每一行所占的像素字节数
	int line_bytes; //一行所占的字节数
	int laizi = 0; //每一行末尾赖子数量
	
	line_bytes_valid = abs(width) * (depth/8) ;

	if (line_bytes_valid % 4)
	{
		laizi = 4 - line_bytes_valid%4; 

	}
	line_bytes = line_bytes_valid + laizi;

	total_bytes = line_bytes * abs(height) ;

	unsigned char *pixel = malloc( total_bytes ); 
	lseek(fd, 54, SEEK_SET );
	read(fd, pixel, total_bytes);

	int i = 0;
	unsigned char a,r,g,b;
	int color ;

	int x, y;


	for (y = 0; y < abs(height); y++)
	{
		//这一行的第x点的解析
		for (x = 0; x < abs(width); x++)
		{
			b = pixel[i++];
			g = pixel[i++];
			r = pixel[i++];

			if (depth == 32)
			{
				a = pixel[i++];
			}
			else
			{
				a = 0;
			}
			color = (a << 24) | (r << 16) | (g << 8) | (b);
			lcd_draw_point( x0 + x,	y0 + abs(height) - 1 - y, color);
		}
		i = i + laizi;

	}
			
	free(pixel);

	close(fd);


}






















