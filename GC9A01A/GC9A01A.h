/*
 * GC9A01A.h
 *
 *  Created on: Apr 1, 2025
 *      Author: arthur
 */

#ifndef __GC9A01A_H__
#define __GC9A01A_H__

#include "stm32f4xx_hal.h"

/* GC9A01A parameters */

typedef struct {
  SPI_HandleTypeDef *hspi;
  TIM_HandleTypeDef *htim;	//PWM for backlight
  uint8_t			tim_ch;	//PWM channel for backlight
  uint16_t 			width;
  uint16_t 			height;
  uint16_t          cs_pin;
  GPIO_TypeDef      *cs_gpio;
  uint16_t          dc_pin;
  GPIO_TypeDef      *dc_gpio;
  uint16_t          bl_pin;
  GPIO_TypeDef      *bl_gpio;
  uint16_t          rst_pin;
  GPIO_TypeDef      *rst_gpio;
} GC9A01A;



/*Memory Access Control*/
#define GC9A01A_MAC_RGB 0x00
#define GC9A01A_MAC_MH  0x04
#define GC9A01A_MAC_BGR 0x08
#define GC9A01A_MAC_ML  0x10
#define GC9A01A_MAC_MV  0x20
#define GC9A01A_MAC_MX  0x40
#define GC9A01A_MAC_MY  0x80

/* Command list */
#define GC9A01A_SWRESET 		0x01   	//Software Reset
#define GC9A01A_RDDID 			0x04    //Read display identification information
#define GC9A01A_RDDST 			0x09    //Read Display Status
#define GC9A01A_SLPON			0x10	//Sleep IN
#define GC9A01A_SLPOFF			0x11	//Sleep OUT
#define GC9A01A_PRTLON			0x12	//Partial Mode ON
#define GC9A01A_NRMLON			0x13	//Normal Display Mode ON

#define GC9A01A_INVOFF			0x20	//Display Inversion OFF
#define GC9A01A_INVON			0x21	//Display Inversion ON
#define GC9A01A_DISPOFF 	   	0x28	//Display OFF
#define GC9A01A_DISPON			0x29	//Display ON
#define GC9A01A_CASET			0x2A	//Column Address Set
#define GC9A01A_RASET			0x2B	//Row Address Set
#define GC9A01A_MEMWR			0x2C	//Memory Write

#define GC9A01A_PAREA			0x30	//Partial Area
#define GC9A01A_VSD				0x33	//Vertical Scrolling Definition
#define GC9A01A_TELOFF			0x34	//Tearing Effect Line OFF
#define GC9A01A_TELON			0x35	//Tearing Effect Line ON
#define GC9A01A_MACTL			0x36	//Memory Access Control
#define GC9A01A_VSADDR			0x37	//Vertical Scrolling Start Address
#define GC9A01A_IDLEOFF 		0x38   	//Idle mode OFF
#define GC9A01A_IDLEON 			0x39    ///Idle mode ON
#define GC9A01A_PXLFMT			0x3A	//Pixel Format Set
#define GC9A01A_CONTINUE 		0x3C    //Write Memory Continue

#define GC9A01A_SETTEAR			0x44    //Set Tear Scanline
#define GC9A01A_GETSL 			0x45    //Get Scanline

#define GC9A01A_DSPLIGHT		0x51	//Write Display Brightness
#define GC9A01A_SETCTRL 		0x53   	//Write CTRL Display

#define GC9A01A_TEWC 			0xBA    //Tearing effect width control
#define GC9A01A_DSPFCTL			0xB6	//Display function control

#define GC9A01A_PWRCTR1			0xC1	//PWR CTRL 1
#define GC9A01A_PWRCTR2			0xC3	//PWR CTRL 2
#define GC9A01A_PWRCTR3			0xC4	//PWR CTRL 3
#define GC9A01A_PWRCTR4			0xC9	//PWR CTRL 4
#define GC9A01A_PWRCTR7			0xA7	//PWR CTRL 7

#define GC9A01A_RDID1 			0xDA     //Read ID 1
#define GC9A01A_RDID2 			0xDB     //Read ID 2
#define GC9A01A_RDID3 			0xDC     //Read ID 3

#define GC9A01A_FRMRATE        	0xE8	 //Frame rate control
#define GC9A01A_SPI2DATA 		0xE9     // SPI 2DATA control

#define GC9A01A_SETGAM1			0xF0	 //Set Gamma 1
#define GC9A01A_SETGAM2			0xF1	 //Set Gamma 2
#define GC9A01A_SETGAM3			0xF2	 //Set Gamma 3
#define GC9A01A_SETGAM4			0xF3	 //Set Gamma 4

#define GC9A01A_INTCTRL			0xF6    //Interface control
#define GC9A01A_INTREG1			0xFE 	//Inter register enable1
#define GC9A01A_INTREG2			0xEF	//Inter register enable2

/*Colors*/
#define GC9A01A_BLACK			0x0000
#define GC9A01A_DARKGREY 		0x7BEF
#define GC9A01A_LIGHTGREY 		0xC618
#define GC9A01A_WHITE			0xFFFF
#define GC9A01A_MAGENTA			0xf81F
#define GC9A01A_BLUE			0x001F
#define GC9A01A_CYAN			0x07FF
#define GC9A01A_GREEN			0x07E0
#define GC9A01A_YELLOW			0xFFE0
#define GC9A01A_ORANGE			0xFBC0
#define GC9A01A_RED				0xF800
#define GC9A01A_PINK 			0xFC18


/*Functions declarations*/

void GC9A01A_Reset(GC9A01A *lcd);
void GC9A01A_Init(GC9A01A *lcd);
void GC9A01A_Sleep(GC9A01A *lcd);
void GC9A01A_WakeUp(GC9A01A *lcd);
void GC9A01A_SetBacklight(GC9A01A *lcd, uint8_t val);

void GC9A01A_SetWindow(GC9A01A *lcd, uint16_t x, uint16_t y, uint16_t w,uint16_t h);
void GC9A01A_SetWord(GC9A01A *lcd, uint16_t x, uint16_t y, uint16_t col);
void GC9A01A_FillWindow(GC9A01A *lcd,uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t col);

#endif /* __GC9A01A_H__ */
