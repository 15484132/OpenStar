#ifndef __LCD1602_H
#define __LCD1602_H

#include "main.h"
#include "gpio.h"
#include "mytime.h"

//#define LCD1602_RW(x) {x?HAL_GPIO_WritePin(GPIOA,RW_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOA,RW_Pin,GPIO_PIN_RESET);}
//#define	LCD1602_RS(x) {x?HAL_GPIO_WritePin(GPIOA,RS_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOA,RS_Pin,GPIO_PIN_RESET);}
//#define	LCD1602_CS(x) {x?HAL_GPIO_WritePin(GPIOA,E_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOA,E_Pin,GPIO_PIN_RESET);}
#define LCD1602_RW(x) {Set_GPIO_Pin(GPIOA,RW_Pin,(GPIO_PinState)x);}
#define LCD1602_RS(x) {Set_GPIO_Pin(GPIOA,RS_Pin,(GPIO_PinState)x);}
#define LCD1602_CS(x) {Set_GPIO_Pin(GPIOA,E_Pin,(GPIO_PinState)x);}

#define LCD1602_D0(x) {Set_GPIO_Pin(GPIOA,D0_Pin,(GPIO_PinState)(x&0x01));}
#define LCD1602_D1(x) {Set_GPIO_Pin(GPIOA,D1_Pin,(GPIO_PinState)((x>>1)&0x01));}
#define LCD1602_D2(x) {Set_GPIO_Pin(GPIOA,D2_Pin,(GPIO_PinState)((x>>2)&0x01));}
#define LCD1602_D3(x) {Set_GPIO_Pin(GPIOA,D3_Pin,(GPIO_PinState)((x>>3)&0x01));}
#define LCD1602_D4(x) {Set_GPIO_Pin(GPIOB,D4_Pin,(GPIO_PinState)((x>>4)&0x01));}
#define LCD1602_D5(x) {Set_GPIO_Pin(GPIOB,D5_Pin,(GPIO_PinState)((x>>5)&0x01));}
#define LCD1602_D6(x) {Set_GPIO_Pin(GPIOB,D6_Pin,(GPIO_PinState)((x>>6)&0x01));}
#define LCD1602_D7(x) {Set_GPIO_Pin(GPIOB,D7_Pin,(GPIO_PinState)((x>>7)&0x01));}

#define Row 2
#define Col 16

#define LCD_CLEAR 							0x01    //清屏指令
#define LCD_RETURNHOME					0x02    //回原指令
#define LCD_ENTYMODESET					0x04    //输入模式设置
#define LCD_DISPLAYCONTROL			0x08    //显示控制
#define LCD_DISPLAY							0x0C 		//开显示
#define LCD_CURSORSHIFT					0x10    //光标显示
#define LCD_FUNCTIONSET					0x20    //功能
#define LCD_SETCGRAMADDR        0x40    //设置字符地址
#define LCD_SETDDRAMADDR        0x80		//设置存储器地址
#define LCD_BUSYSIGNEL					0x38    //忙信号检测

#define LCD_DISPLAYON           0x04
#define LCD_CURSORON            0x02 

#define LCD_CURSORMOVE          0x00
#define LCD_MOVERIGHT           0x0C
#define LCD_MOVELEFT            0x08

typedef struct
{
	uint8_t DisplayControl;
	uint8_t DisplayFunction;
	uint8_t CurrentX;
	uint8_t CurrentY;
}LCD1602;

extern LCD1602 lcd1602;

int SetAddr(int row,int col);
void ShowString(int row,int col,char data[]);
void ClearScreen(void);
void ReadState(void);
void WriteByteCmd(char argc);
void WriteByteData(char argc);
void LCD1602_Init(void);
void DisplayOnAndOff(volatile char ret);
void CursorOnAndOff(volatile char ret);
void StringMoveLeftOrRight(volatile char ret);
void Set_GPIO_Pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState state);

#endif
