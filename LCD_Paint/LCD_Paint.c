/*
 * LCD_Paint.c
 *
 *  Created on: Apr 11, 2025
 *      Author: arthur
 */
#include "LCD_Paint.h"

inline void LCD_DrawPixel(GC9A01A *lcd, uint16_t x, uint16_t y, uint16_t col){
	GC9A01A_SetWord(lcd, x, y, col);
}
inline void LCD_Fill(GC9A01A *lcd, uint16_t col){
	GC9A01A_FillWindow(lcd,0,0,lcd->width,lcd->height,col);
}
inline void LCD_FillWindow(GC9A01A *lcd,uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t col){
	GC9A01A_FillWindow(lcd,x1,y1,w,h,col);
}
