/*
 * GC9A01A.c
 *
 *  Created on: Apr 1, 2025
 *      Author: arthur
 */

#include "GC9A01A.h"

/*Array to help with channel selection*/

static const uint32_t tim_channels[] = {
    TIM_CHANNEL_1,
    TIM_CHANNEL_2,
    TIM_CHANNEL_3,
    TIM_CHANNEL_4
};

/* Commands to setup the IC. The commands with //? are given by the manufacturers code but not present in the datasheet.*/

static const uint8_t init_cmd[] = {
		GC9A01A_INTREG2, 0,													  //Inter register enable2
		0xEB, 1, 0x14,                                                        // ?
		GC9A01A_INTREG1, 0,													  //Inter register enable1
		GC9A01A_INTREG2, 0,													  //Inter register enable2
		0xEB, 1, 0x14,                                                        // ?
		0x84, 1, 0x40,                                                        // ?
		0x85, 1, 0xFF,                                                        // ?
		0x86, 1, 0xFF,                                                        // ?
		0x87, 1, 0xFF,                                                        // ?
		0x88, 1, 0x0A,                                                        // ?
		0x89, 1, 0x21,                                                        // ?
		0x8A, 1, 0x00,                                                        // ?
		0x8B, 1, 0x80,                                                        // ?
		0x8C, 1, 0x01,                                                        // ?
		0x8D, 1, 0x01,                                                        // ?
		0x8E, 1, 0xFF,                                                        // ?
		0x8F, 1, 0xFF,                                                        // ?
		GC9A01A_DSPFCTL, 2, 0x00, 0x00,                                       //Display function control
		GC9A01A_MACTL, 1, GC9A01A_MAC_MX | GC9A01A_MAC_BGR,					  //Memory Access Control
		GC9A01A_PXLFMT, 1, 0x05,											  //Pixel Format Set
		0x90, 4, 0x08, 0x08, 0x08, 0x08,                                      // ?
		0xBD, 1, 0x06,                                                        // ?
		0xBC, 1, 0x00,                                                        // ?
		0xFF, 3, 0x60, 0x01, 0x04,                                            // ?
		GC9A01A_PWRCTR2, 1, 0x13,											  //PWR CTRL 2
		GC9A01A_PWRCTR3, 1, 0x13,											  //PWR CTRL 3
		GC9A01A_PWRCTR4, 1, 0x22,											  //PWR CTRL 4
		0xBE, 1, 0x11,                                                        // ?
		0xE1, 2, 0x10, 0x0E,                                                  // ?
		0xDF, 3, 0x21, 0x0c, 0x02,                                            // ?
		GC9A01A_SETGAM1, 6, 0x45, 0x09, 0x08, 0x08, 0x26, 0x2A,				  //Set Gamma 1
		GC9A01A_SETGAM2, 6, 0x43, 0x70, 0x72, 0x36, 0x37, 0x6F,				  //Set Gamma 2
		GC9A01A_SETGAM3, 6, 0x45, 0x09, 0x08, 0x08, 0x26, 0x2A,				  //Set Gamma 3
		GC9A01A_SETGAM4, 6, 0x43, 0x70, 0x72, 0x36, 0x37, 0x6F,				  //Set Gamma 4
		0xED, 2, 0x1B, 0x0B,                                                  // ?
		0xAE, 1, 0x77,                                                        // ?
		0xCD, 1, 0x63,                                                        // ?
		GC9A01A_FRMRATE, 1, 0x04,											  //Frame rate control
		0x62, 12, 0x18, 0x0D, 0x71, 0xED, 0x70, 0x70,                         // ?
            0x18, 0x0F, 0x71, 0xEF, 0x70, 0x70,
		0x63, 12, 0x18, 0x11, 0x71, 0xF1, 0x70, 0x70,                         // ?
            0x18, 0x13, 0x71, 0xF3, 0x70, 0x70,
		0x64, 7, 0x28, 0x29, 0xF1, 0x01, 0xF1, 0x00, 0x07,                    // ?
		0x66, 10, 0x3C, 0x00, 0xCD, 0x67, 0x45, 0x45, 0x10, 0x00, 0x00, 0x00, // ?
		0x67, 10, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x01, 0x54, 0x10, 0x32, 0x98, // ?
		0x74, 7, 0x10, 0x85, 0x80, 0x00, 0x00, 0x4E, 0x00,                    // ?
		0x98, 2, 0x3e, 0x07,                                                  // ?
		GC9A01A_TELON, 0,													  //Tearing Effect Line ON
		GC9A01A_INVON, 0,												      //Display Inversion ON
		GC9A01A_SLPOFF, 0x80,                                                 //Sleep mode OUT
		GC9A01A_DISPON, 0x80,                                                 //Display ON
		0x00                                                                  //End
};

/*Functions definition*/

/*
 * Function: GC9A01A_WriteReg
 * ----------------------------
 *   Write command to the IC.
 *
 *   lcd: pointer to lcd object
 *   cmd: command to be sent
 *
 *   returns: None
 */
void GC9A01A_WriteReg(GC9A01A *lcd, uint8_t cmd){
	HAL_GPIO_WritePin(lcd->cs_gpio,lcd->cs_pin,GPIO_PIN_RESET);

	HAL_GPIO_WritePin(lcd->dc_gpio,lcd->dc_pin,GPIO_PIN_RESET);
	HAL_SPI_Transmit(lcd->hspi,&cmd,1,HAL_MAX_DELAY);

	HAL_GPIO_WritePin(lcd->cs_gpio,lcd->cs_pin,GPIO_PIN_SET);
}

/*
 * Function: GC9A01A_WriteData_Byte
 * ----------------------------
 *   Write data byte to the IC.
 *
 *   lcd: pointer to lcd object
 *   b: byte to be sent
 *
 *   returns: None
 */
void GC9A01A_WriteData_Byte(GC9A01A *lcd, uint8_t b){
	HAL_GPIO_WritePin(lcd->cs_gpio,lcd->cs_pin,GPIO_PIN_RESET);

	HAL_GPIO_WritePin(lcd->dc_gpio,lcd->dc_pin,GPIO_PIN_SET);
	HAL_SPI_Transmit(lcd->hspi,&b,1,HAL_MAX_DELAY);

	HAL_GPIO_WritePin(lcd->cs_gpio,lcd->cs_pin,GPIO_PIN_SET);
}
/*
 * Function: GC9A01A_WriteData_Word
 * ----------------------------
 *   Write data word to the IC.
 *
 *   lcd: pointer to lcd object
 *   w: word to be sent
 *
 *   returns: None
 */
void GC9A01A_WriteData_Word(GC9A01A *lcd, uint16_t w){
	uint8_t word_data[2]= { w >> 8 , w & 0xff};
	HAL_GPIO_WritePin(lcd->cs_gpio,lcd->cs_pin,GPIO_PIN_RESET);

	HAL_GPIO_WritePin(lcd->dc_gpio,lcd->dc_pin,GPIO_PIN_SET);
	HAL_SPI_Transmit(lcd->hspi,(uint8_t*)word_data,1,HAL_MAX_DELAY);
	HAL_SPI_Transmit(lcd->hspi,(uint8_t*) word_data+1,1,HAL_MAX_DELAY);

	HAL_GPIO_WritePin(lcd->cs_gpio,lcd->cs_pin,GPIO_PIN_SET);
}
/*
 * Function: GC9A01A_Reset
 * ----------------------------
 *   Reset peripheral.
 *
 *   lcd: pointer to lcd object
 *
 *   returns: None
 */
void GC9A01A_Reset(GC9A01A *lcd){
	HAL_GPIO_WritePin(lcd->rst_gpio,lcd->rst_pin,GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(lcd->rst_gpio,lcd->rst_pin,GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(lcd->rst_gpio,lcd->rst_pin,GPIO_PIN_SET);
	HAL_Delay(100);
}
/*
 * Function: GC9A01A_Init
 * ----------------------------
 *   Initialize the peripheral by reseting,sending the display parameters through SPI communication, and setting up the PWM for backlight control.
 *
 *   lcd: pointer to lcd object
 *
 *   returns: None
 */
void GC9A01A_Init(GC9A01A *lcd){
  GC9A01A_Reset(lcd);

  const uint8_t *p = init_cmd;
  while(*p){
	  GC9A01A_WriteReg(lcd,*p);
	  p++;
	  if(*p == 0x80) HAL_Delay(100);
	  else{
		  uint8_t nArgs=*p;
		  while(nArgs--){
			  p++;
			  GC9A01A_WriteData_Byte(lcd,*p);
		  }
	  }
	  p++;
  }
  HAL_TIM_PWM_Start(lcd->htim, tim_channels[lcd->tim_ch -1]);
}
/*
 * Function: GC9A01A_Sleep
 * ----------------------------
 *   Put the peripheral in sleep mode.
 *
 *   lcd: pointer to lcd object
 *
 *   returns: None
 */
inline void GC9A01A_Sleep(GC9A01A *lcd){
	 GC9A01A_WriteReg(lcd,GC9A01A_SLPON);
	 HAL_Delay(120);
}
/*
 * Function: GC9A01A_WakeUp
 * ----------------------------
 *   Put the peripheral out of sleep mode.
 *
 *   lcd: pointer to lcd object
 *
 *   returns: None
 */
inline void GC9A01A_WakeUp(GC9A01A *lcd){
	GC9A01A_WriteReg(lcd,GC9A01A_SLPOFF);
	HAL_Delay(120);
}
/*
 * Function: GC9A01A_SetBacklight
 * ----------------------------
 *   Controls PWM for backlight.
 *
 *   lcd: pointer to lcd object
 *   val: duty cycle between 0 and 100
 *
 *   returns: None
 */
void GC9A01A_SetBacklight(GC9A01A *lcd, uint8_t val){
	if(val > 100 ) val = 100;
	uint16_t cmd = 65535 * val / 100;
	__HAL_TIM_SET_COMPARE(lcd->htim, tim_channels[lcd->tim_ch -1],cmd);
}
/*
 * Function: GC9A01A_SetWindow
 * ----------------------------
 *   Set the window in which data will be sent.
 *
 *   lcd: pointer to lcd object
 *   x: window x start
 *   y: window y start
 *	 w: window width
 *	 h: window height
 *
 *   returns: None
 */
void GC9A01A_SetWindow(GC9A01A *lcd, uint16_t x, uint16_t y, uint16_t w,uint16_t h){
	GC9A01A_WriteReg(lcd,GC9A01A_CASET);
	GC9A01A_WriteData_Byte(lcd,0x00);
	GC9A01A_WriteData_Byte(lcd,x);
	GC9A01A_WriteData_Byte(lcd,0x00);
	GC9A01A_WriteData_Byte(lcd,x + w - 1);

	GC9A01A_WriteReg(lcd,GC9A01A_RASET);
	GC9A01A_WriteData_Byte(lcd,0x00);
	GC9A01A_WriteData_Byte(lcd,y);
	GC9A01A_WriteData_Byte(lcd,0x00);
	GC9A01A_WriteData_Byte(lcd,y + h - 1);

	GC9A01A_WriteReg(lcd,GC9A01A_MEMWR);
}


