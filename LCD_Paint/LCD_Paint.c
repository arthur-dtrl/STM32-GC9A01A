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
void LCD_DrawImage(GC9A01A* lcd,uint16_t x, uint16_t y,uint16_t w,uint16_t h,const uint16_t* img){
	uint16_t *p = (uint16_t*)img;
	GC9A01A_SetWindow(lcd, x, y, w, h);
	for(uint16_t i = 0; i < w; i++){
		for(uint16_t j = 0; j < h; j++){
			GC9A01A_WriteData_Word(lcd,*p++);
		}
	}
}
inline void LCD_Fill(GC9A01A *lcd, uint16_t col){
	GC9A01A_FillWindow(lcd,0,0,lcd->width,lcd->height,col);
}
inline void LCD_FillWindow(GC9A01A *lcd,uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t col){
	GC9A01A_FillWindow(lcd,x1,y1,w,h,col);
}
