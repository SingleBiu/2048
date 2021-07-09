/*
 * @Author: SingleBiu
 * @Date: 2021-05-21 12:01:15
 * @LastEditors: SingleBiu
 * @LastEditTime: 2021-07-09 16:17:47
 * @Description: file content
 */

#ifndef  __LCD_H__
#define  __LCD_H__
//打开屏幕
void lcd_open(void);
//关闭屏幕
void lcd_close(void);
//描点
void lcd_draw_point(int x, int y, int color);
//画矩形
void lcd_draw_rectanle(int x0, int y0, int w, int h, int color);
//清屏
void lcd_clear_screen(int color);

void lcd_draw_word(char *ch, int len, int w, int color, int x0, int y0);
void lcd_draw_rect(uint x0, uint y0, uint w, uint h, int color);
void lcd_draw_digit(int value,int x0, int y0, int color);
#endif



