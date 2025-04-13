/*
 * LCD_Paint.h
 *
 *  Created on: Apr 11, 2025
 *      Author: arthur
 */

#ifndef LCD_PAINT_H_
#define LCD_PAINT_H_

#include "GC9A01A.h"
#include "malloc.h"

/*Colors*/
#define LCD_BLACK			0x0000
#define LCD_DARKGREY 		0x7BEF
#define LCD_LIGHTGREY 		0xC618
#define LCD_WHITE			0xFFFF
#define LCD_MAGENTA			0xf81F
#define LCD_BLUE			0x001F
#define LCD_CYAN			0x07FF
#define LCD_GREEN			0x07E0
#define LCD_YELLOW			0xFFE0
#define LCD_ORANGE			0xFBC0
#define LCD_RED				0xF800
#define LCD_PINK 			0xFC18


/*Functions declarations*/

void LCD_DrawPixel(GC9A01A *lcd, uint16_t x, uint16_t y, uint16_t col);
void LCD_DrawLine(GC9A01A *lcd,uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t col);
void LCD_DrawImage(GC9A01A* lcd,uint16_t x, uint16_t y,uint16_t w,uint16_t h,const uint16_t* img);
void LCD_Fill(GC9A01A *lcd, uint16_t col);
void LCD_FillWindow(GC9A01A *lcd, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t col);


#endif /* LCD_PAINT_H_ */
