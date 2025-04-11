/*
 * LCD_Paint.h
 *
 *  Created on: Apr 11, 2025
 *      Author: arthur
 */

#ifndef LCD_PAINT_H_
#define LCD_PAINT_H_

#include "GC9A01A.h"

void LCD_DrawPixel(GC9A01A *lcd, uint16_t x, uint16_t y, uint16_t col);

/*Drawing functions*/
void LCD_Fill(GC9A01A *lcd, uint16_t col);
void LCD_FillWindow(GC9A01A *lcd, uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t col);


#endif /* LCD_PAINT_H_ */
