/*
 * LCD_Paint.c
 *
 *  Created on: Apr 11, 2025
 *      Author: arthur
 */
#include "LCD_Paint.h"

/*
 * Function: LCD_DrawPixel
 * ----------------------------
 *   Draw a pixel.
 *
 *   lcd: pointer to lcd object
 *   x: pixel x coordinate
 *   y: pixel y coordinate
 *
 *   returns: None
 */
void LCD_DrawPixel(GC9A01A *lcd, uint16_t x, uint16_t y, uint16_t col){
	GC9A01A_SetWindow(lcd,x,y,1,1);
	GC9A01A_WriteData_Word(lcd,col);
}
/*
 * Function: LCD_DrawLine
 * ----------------------------
 *   Draw a line between two points using Bresenham line algorithm.
 *
 *   lcd: pointer to lcd object
 *   x0: line x start
 *   y0: line y start
 *   x1: line x end
 *   y1: line y end
 *   col: color
 *
 *   returns: None
 */
void LCD_DrawLine(GC9A01A* lcd, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t col){
  int16_t dx = ((x1 - x0 >= 0)? x1 - x0 : x0 - x1);
  int8_t sx = x0 < x1 ? 1 : -1;
  int16_t dy = ((y1 - y0 >= 0)? y0 - y1 : y1 - y0);
  int8_t sy = y0 < y1 ? 1 : -1;
  int16_t err = dx + dy, e2;

  for (;;){
    LCD_DrawPixel(lcd,x0,y0,col);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; }
    if (e2 <= dx) { err += dx; y0 += sy; }
  }
}

/*
 * Function: LCD_DrawImage
 * ----------------------------
 *   Draw an image in a window.
 *
 *   lcd: pointer to lcd object
 *   x: window x start
 *   y: window y start
 *   w: window width
 *   h: window height
 *   img: array containing the image.
 *
 *   returns: None
 */
void LCD_DrawImage(GC9A01A* lcd,uint16_t x, uint16_t y,uint16_t w,uint16_t h,const uint16_t* img){
	uint16_t *p = (uint16_t*)img;
	GC9A01A_SetWindow(lcd, x, y, w, h);
	for(uint16_t i = 0; i < w; i++){
		for(uint16_t j = 0; j < h; j++){
			GC9A01A_WriteData_Word(lcd,*p++);
		}
	}
}
/*
 * Function: LCD_Fill
 * ----------------------------
 *   Fill the display with a color.
 *
 *   lcd: pointer to lcd object
 *   col: color
 *
 *   returns: None
 */
void LCD_Fill(GC9A01A *lcd, uint16_t col){
	GC9A01A_SetWindow(lcd,0,0,lcd->width,lcd->height);
		for(uint8_t i = 0; i < lcd->width ; i++){
			for(uint8_t j = 0; j < lcd->height ; j++){
				GC9A01A_WriteData_Word(lcd,col);
			}
		}
	}
/*
 * Function: LCD_FillWindow
 * ----------------------------
 *   Fill a window with a color.
 *
 *   lcd: pointer to lcd object
 *   x: window x start
 *   y: window y start
 *   w: window width
 *   h: window height
 *   col: color
 *
 *   returns: None
 */
void LCD_FillWindow(GC9A01A *lcd,uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t col){
	GC9A01A_SetWindow(lcd,x,y,w,h);
	for(uint8_t i = 0; i < w ; i++){
		for(uint8_t j = 0; j < h ; j++){
			GC9A01A_WriteData_Word(lcd,col);
		}
	}
}
