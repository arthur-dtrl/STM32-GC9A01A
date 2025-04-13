/* WARNING: This main file in not usable. Its just an example of how the library can be used and must be adapted to each STM32 project. */

#include "LCD_Paint.h"
#include "Config.h"

#include "f1.h"
#include "f2.h"
#include "f3.h"

extern const uint16_t f1[];
extern const uint16_t f2[];
extern const uint16_t f3[];

int main(){

  GC9A01A lcd = {&hspi1,&htim3,2,GC9A01A_HEIGHT,GC9A01A_WIDTH,GC9A01A_CS_Pin,GC9A01A_CS_GPIO_Port,
		  GC9A01A_DC_Pin ,GC9A01A_DC_GPIO_Port,GC9A01A_BL_Pin,GC9A01A_BL_GPIO_Port,
		  GC9A01A_RST_Pin,GC9A01A_RST_GPIO_Port};

  GC9A01A_Init(&lcd);
  GC9A01A_SetBacklight(&lcd,100);
  LCD_Fill(&lcd,LCD_BLACK);
  LCD_DrawLine(&lcd,0,145,240,145,LCD_WHITE);
  while (1){
	  LCD_DrawImage(&lcd, 88, 80, 64, 64, f3);
	  HAL_Delay(200);
	  LCD_DrawImage(&lcd, 88, 80, 64, 64, f2);
	  HAL_Delay(200);
	  LCD_DrawImage(&lcd, 88, 80, 64, 64, f1);
	  HAL_Delay(200);
  }

}
