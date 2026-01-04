#include "lcd1602.h"

LCD1602 lcd1602;

void LCD1602_Init(void)//初始化
{
	WriteByteCmd(LCD_BUSYSIGNEL); 
	DisplayOnAndOff(1);
	CursorOnAndOff(0);
	StringMoveLeftOrRight(0);
	ClearScreen();
}

void WriteByteData(char argc) //显示数据
{
	//LCD1602_Data_TR(1);
	LCD1602_RS(1);
	LCD1602_RW(0);	
	LCD1602_CS(0);
	LCD1602_D0(argc);
	LCD1602_D1(argc);
	LCD1602_D2(argc);
	LCD1602_D3(argc);
	LCD1602_D4(argc);
	LCD1602_D5(argc);
	LCD1602_D6(argc);
	LCD1602_D7(argc);
	LCD1602_CS(1);
	delay_ms(5);
	LCD1602_CS(0);	
}

void WriteByteCmd(char argc)//写命令
{
	//LCD1602_Data_TR(1);
	LCD1602_RS(0);
	LCD1602_RW(0);
	LCD1602_CS(0);
	LCD1602_D0(argc);
	LCD1602_D1(argc);
	LCD1602_D2(argc);
	LCD1602_D3(argc);
	LCD1602_D4(argc);
	LCD1602_D5(argc);
	LCD1602_D6(argc);
	LCD1602_D7(argc);
	LCD1602_CS(1);
	delay_ms(5);
	LCD1602_CS(0);
}
	
void ReadState(void)//读状态
{
	LCD1602_RS(0);
	LCD1602_RW(1);	
	LCD1602_CS(1);
}

void ClearScreen(void)
{
	WriteByteCmd(LCD_CLEAR);
}


void ShowString(int row,int col,char data[]) //16*2
{
	int ret = SetAddr(row,col);
	char *GetData = data;
	if(ret != 0) return;
	while(*GetData)
	{
		WriteByteData(*GetData);
		GetData++;
	}
}

int SetAddr(int row,int col) //设置地址
{
	char addr;
	if(row == 0) addr = LCD_SETDDRAMADDR + col; //第0行
	else if(row == 1) addr = LCD_SETDDRAMADDR + LCD_SETCGRAMADDR +col;//第1行
	else return -1;
	WriteByteCmd(addr);
	return 0;
}


void DisplayOnAndOff(volatile char ret)
{
	if(ret)
	{
		lcd1602.DisplayControl |= LCD_DISPLAYON;	
	}
	else
	{
		lcd1602.DisplayControl &= ~LCD_DISPLAYON;
	}
	WriteByteCmd(lcd1602.DisplayControl|LCD_DISPLAYCONTROL);
}

void CursorOnAndOff(volatile char ret)
{
	if(ret)
	{
		lcd1602.DisplayControl |= LCD_CURSORON;
	}
	else
	{
		lcd1602.DisplayControl &= ~LCD_CURSORON;
	}
	WriteByteCmd(lcd1602.DisplayControl|LCD_DISPLAYCONTROL);		
}

void StringMoveLeftOrRight(volatile char ret)
{
	uint8_t cmd;
	if(ret == 1) cmd = LCD_CURSORSHIFT|LCD_MOVERIGHT;
	else if(ret == -1) cmd = LCD_CURSORSHIFT|LCD_MOVELEFT;
	else return;
	WriteByteCmd(cmd);
}

void Set_GPIO_Pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState state)
{
	if(state != GPIO_PIN_RESET)
	{
		GPIOx->BSRR = GPIO_Pin;
	}
	else
	{
		GPIOx->BRR = GPIO_Pin;
	}
}