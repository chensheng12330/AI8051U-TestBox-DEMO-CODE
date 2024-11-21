/*---------------------------------------------------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/*---------------------------------------------------------------------*/

/*************  功能说明    **************

本例程基于AI8051U为主控芯片的实验箱进行编写测试。

使用Keil C251编译器，Memory Model推荐设置XSmall模式，默认定义变量在edata，单时钟存取访问速度快。

edata建议保留1K给堆栈使用，空间不够时可将大数组、不常用变量加xdata关键字定义到xdata空间。

硬件LCM M6800接口驱动LCD1602字符屏.

显示效果为: LCD显示时间.

第一行显示 ---Clock demo---
第二行显示     12-00-00

LCD1602字符屏连接12864模块接口1~16PIN.

R120焊接0欧电阻，将16PIN短接到GND.

下载时, 选择时钟 24MHz (用户可自行修改频率).

******************************************/

#include    "AI8051U.h"     //包含此头文件后，不需要再包含"reg51.h"头文件
#include    "intrins.h"

#define     MAIN_Fosc       24000000L   //定义主时钟

typedef     unsigned char   u8;
typedef     unsigned int    u16;
typedef     unsigned long   u32;

/*************	Pin define	*****************************************************/

sbit	LCD_B7  = P2^7;	//D7 -- Pin 14		LED- -- Pin 16 
sbit	LCD_B6  = P2^6;	//D6 -- Pin 13		LED+ -- Pin 15
sbit	LCD_B5  = P2^5;	//D5 -- Pin 12		Vo   -- Pin 3
sbit	LCD_B4  = P2^4;	//D4 -- Pin 11		VDD  -- Pin 2
sbit	LCD_B3  = P2^3;	//D3 -- Pin 10		VSS  -- Pin 1
sbit	LCD_B2  = P2^2;	//D2 -- Pin  9
sbit	LCD_B1  = P2^1;	//D1 -- Pin  8
sbit	LCD_B0  = P2^0;	//D0 -- Pin  7

sbit	LCD_ENA	= P3^7;	//Pin 6
sbit	LCD_RW	= P3^6;	//Pin 5	//LCD_RS   R/W   DB7--DB0        FOUNCTION
sbit	LCD_RS	= P4^5;	//Pin 4	//	0		0	  INPUT      write the command to LCD model
								//	0		1     OUTPUT     read BF and AC pointer from LCD model
								//	1		0     INPUT      write the data to LCD  model
								//	1		1     OUTPUT     read the data from LCD model

u8	hour,minute,second;

void RTC(void);
void ClearLine(u8 row);
void Initialize_LCD(void);
void PutString(u8 row, u8 column, u8 *puts);
void DisplayRTC(void);
void delay_ms(u16 ms);
void WriteChar(u8 row, u8 column, u8 dat);
void LCM_Config(void);

void main(void)
{
    WTST = 0;  //设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
    EAXFR = 1; //扩展寄存器(XFR)访问使能
    CKCON = 0; //提高访问XRAM速度

    P0M1 = 0x00;   P0M0 = 0x00;   //设置为准双向口
    P1M1 = 0x00;   P1M0 = 0x00;   //设置为准双向口
    P2M1 = 0x00;   P2M0 = 0x00;   //设置为准双向口
    P3M1 = 0x00;   P3M0 = 0x00;   //设置为准双向口
    P4M1 = 0x00;   P4M0 = 0x00;   //设置为准双向口
    P5M1 = 0x00;   P5M0 = 0x00;   //设置为准双向口
    P6M1 = 0x00;   P6M0 = 0x00;   //设置为准双向口
    P7M1 = 0x00;   P7M0 = 0x00;   //设置为准双向口

    LCM_Config();
    Initialize_LCD();
    ClearLine(0);
    ClearLine(1);

    PutString(0,0,"---Clock demo---");
	
    hour   = 12;	//初始化时间值
    minute = 0;
    second = 0;
    DisplayRTC();

    while(1)
    {
        delay_ms(1000);
        RTC();
        DisplayRTC();
    }
}

//========================================================================
// 函数: void delay_ms(u16 ms)
// 描述: 延时函数。
// 参数: ms,要延时的ms数, 这里只支持1~65535ms. 自动适应主时钟.
// 返回: none.
// 版本: VER1.0
// 日期: 2024-9-30
// 备注: 
//========================================================================
void delay_ms(u16 ms)
{
     u16 i;
     do{
          i = MAIN_Fosc / 6000;
          while(--i);
     }while(--ms);
}

//========================================================================
// 函数: void DisplayRTC(void)
// 描述: 显示时钟函数
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2024-9-30
// 备注: 
//========================================================================
void DisplayRTC(void)
{
	if(hour >= 10)	WriteChar(1,4,(u8)(hour / 10 + '0'));
	else			WriteChar(1,4,' ');
	WriteChar(1,5,(u8)(hour % 10 +'0'));
	WriteChar(1,6,'-');
	WriteChar(1,7,(u8)(minute / 10+'0'));
	WriteChar(1,8,(u8)(minute % 10+'0'));
	WriteChar(1,9,'-');
	WriteChar(1,10,(u8)(second / 10 +'0'));
	WriteChar(1,11,(u8)(second % 10 +'0'));
}

//========================================================================
// 函数: void RTC(void)
// 描述: RTC演示函数
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2024-9-30
// 备注: 
//========================================================================
void RTC(void)
{
	if(++second >= 60)
	{
		second = 0;
		if(++minute >= 60)
		{
			minute = 0;
			if(++hour >= 24)	hour = 0;
		}
	}
}

/************* LCD1602相关程序	*****************************************************/
//8位数据访问方式	LCD1602		标准程序	梁工编写	2014-2-21

#define LineLength	16		//16x2

/*
total 2 lines, 16x2= 32
first line address:  0~15
second line address: 64~79

*/

#define C_CLEAR			0x01		//clear LCD
#define C_HOME 			0x02		//cursor go home
#define C_CUR_L			0x04		//cursor shift left after input
#define C_RIGHT			0x05		//picture shift right after input
#define C_CUR_R			0x06		//cursor shift right after input
#define C_LEFT 			0x07		//picture shift left after input
#define C_OFF  			0x08		//turn off LCD
#define C_ON   			0x0C		//turn on  LCD
#define C_FLASH			0x0D		//turn on  LCD, flash 
#define C_CURSOR		0x0E		//turn on  LCD and cursor
#define C_FLASH_ALL		0x0F		//turn on  LCD and cursor, flash
#define C_CURSOR_LEFT	0x10		//single cursor shift left
#define C_CURSOR_RIGHT	0x10		//single cursor shift right
#define C_PICTURE_LEFT	0x10		//single picture shift left
#define C_PICTURE_RIGHT	0x10		//single picture shift right
#define C_BIT8			0x30		//set the data is 8 bits
#define C_BIT4			0x20		//set the data is 4 bits
#define C_L1DOT7		0x30		//8 bits,one line 5*7  dots
#define C_L1DOT10		0x34		//8 bits,one line 5*10 dots
#define C_L2DOT7		0x38		//8 bits,tow lines 5*7 dots
#define C_4bitL2DOT7	0x28		//4 bits,tow lines 5*7 dots
#define C_CGADDRESS0	0x40		//CGRAM address0 (addr=40H+x)
#define C_DDADDRESS0	0x80		//DDRAM address0 (addr=80H+x)

//========================================================================
// 函数: void LCM_Config(void)
// 描述: LCM配置函数。
// 参数: none.
// 返回: none.
// 版本: V1.0, 2024-8-17
// 备注:
//========================================================================
//LCMIFCFG  (7EFE50H)	TFT彩屏接口配置寄存器
#define	LCMIFIE			(0<<7)	//TFT彩屏接口中断使能控制位(bit7), 1->允许中断，0->禁止
#define	LCMIFIP			(0<<4)	//TFT彩屏接口中断优先级控制位(bit5~bit4), (最低)0~3(最高).
#define	LCMIFDPS		(0<<2)	//TFT彩屏接口数据脚选择位(bit3~bit2), D18_D8=0: 0或2->8位数据在P2, D18_D8=1: 0: P2-高字节, P0低字节, 2: P2-高字节,低字节P0[7:4] P4.7 P4.6 P4.3 P4.1.
#define	LCM_D16_D8		(0<<1)	//TFT彩屏接口数据宽度控制位(bit1), 0: 8位数据，1:16位数据
#define	LCM_M68_I80		1		//TFT彩屏接口数据模式选择位(bit0), 0: I8080模式，1:M6800模式

//LCMIFCFG2  (7EFE51H)	TFT彩屏接口配置寄存器2
#define	LCMIFCPS		(1<<5)	//TFT彩屏接口控制脚选择位(bit6~bit5), RS RD(E) WR(RW), 0->P4.5 P4.4 P4.2，1->P4.5 P3.7 P3.6, 2->P4.0 P4.4 P4.2, 3->P4.0 P3.7 P3.6
#define	LCMSETUPT		(4<<2)	//TFT彩屏接口数据建立时间控制位(bit4~bit2), 0~7, 对应1~8个LCMIF时钟, 对于6800模式就是E高电平时间, 至少20us.
#define	LCMHOLDT		3		//TFT彩屏接口数据保持时间控制位(bit1~bit0), 0~3, 对应1~4个LCMIF时钟

//LCMIFCR  (7EFE52H)	TFT彩屏接口控制寄存器
#define	ENLCMIF			(1<<7)	//TFT彩屏接口使能控制位(bit7), 1->允许TFT彩屏接口功能, 0->禁止
#define	LCM_WRCMD		4		//TFT彩屏接口触发命令(bit2~bit0), 4->写命令
#define	LCM_WRDAT		5		//TFT彩屏接口触发命令(bit2~bit0), 5->写数据
#define	LCM_RDCMD		6		//TFT彩屏接口触发命令(bit2~bit0), 6->读命令/状态
#define	LCM_RDDAT		7		//TFT彩屏接口触发命令(bit2~bit0), 7->读数据

void LCM_Config(void)
{
	LCMIFCFG  = LCMIFIE  | LCMIFIP   | LCMIFDPS | LCM_D16_D8 | LCM_M68_I80;
	LCMIFCFG2 = LCMIFCPS | LCMSETUPT | LCMHOLDT;	//RS:P45,E:P37,RW:P36; Setup Time,HOLD Time
	LCMIFSTA  = 0x00;	//TFT彩屏接口中断请求标志，软件清0
	LCMIFPSCR = (u8)(MAIN_Fosc/250000UL-1);	//TFT彩屏接口时钟预分频0~255, LCMIF时钟频率 = SYSclk/(LCMIFPSCR+1), LCD12864速度慢，最快250KHz
	LCMIFCR   = ENLCMIF;
}

//========================================================================
// 函数: void CheckBusy(void)
// 描述: 检测忙函数
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2024-9-30
// 备注: 
//========================================================================
void CheckBusy(void)
{
	LCMIFSTA = 0;	//清除完成标志
    do
    {
		LCMIFCR   = ENLCMIF | LCM_RDCMD;	//读状态
		while((LCMIFSTA & 1) == 0)	;	//等待读完成
		LCMIFSTA = 0;	//清除完成标志
		LCD_ENA = 0;
    }while(LCMIFDATL & 0x80);	//bit7==0则空闲
}

//========================================================================
// 函数: void IniSendCMD(u8 cmd)
// 描述: 初始化写命令(不检测忙)
// 参数: cmd: 要写的命令.
// 返回: none.
// 版本: VER1.0
// 日期: 2024-9-30
// 备注: 
//========================================================================
void IniSendCMD(u8 cmd)
{
	LCMIFDATL = cmd;
	LCMIFCR   = ENLCMIF | LCM_WRCMD;	//写命令
	while((LCMIFSTA & 1) == 0)	;	//等待写完成
	LCMIFSTA = 0;	//清除完成标志
}

//========================================================================
// 函数: void Write_CMD(u8 cmd)
// 描述: 写命令(检测忙)
// 参数: cmd: 要写的命令.
// 返回: none.
// 版本: VER1.0
// 日期: 2024-9-30
// 备注: 
//========================================================================
void Write_CMD(u8 cmd)
{
	CheckBusy(); //检测忙
	LCMIFDATL = cmd;
	LCMIFCR   = ENLCMIF | LCM_WRCMD;	//写命令
	while((LCMIFSTA & 1) == 0)	;	//等待写完成
	LCMIFSTA = 0;	//清除完成标志
}

//========================================================================
// 函数: void Write_DIS_Data(u8 dat)
// 描述: 写显示数据(检测忙)
// 参数: dat: 要写的数据.
// 返回: none.
// 版本: VER1.0
// 日期: 2024-9-30
// 备注: 
//========================================================================
void Write_DIS_Data(u8 dat)
{
	CheckBusy(); //检测忙
	LCMIFDATL = dat;
	LCMIFCR   = ENLCMIF | LCM_WRDAT;	//写数据
	while((LCMIFSTA & 1) == 0)	;	//等待写完成
	LCMIFSTA = 0;	//清除完成标志
}

//========================================================================
// 函数: void Initialize_LCD(void)
// 描述: 初始化函数
// 参数: none.
// 返回: none.
// 版本: VER1.0
// 日期: 2024-9-30
// 备注: 
//========================================================================
void Initialize_LCD(void)
{
	LCD_ENA = 0;
	LCD_RS  = 0;
	LCD_RW = 0;

	delay_ms(100);
	IniSendCMD(C_BIT8);		//set the data is 8 bits

	delay_ms(10);
	Write_CMD(C_L2DOT7);		//tow lines 5*7 dots

	delay_ms(6);
	Write_CMD(C_CLEAR);		//clear LCD RAM
	Write_CMD(C_CUR_R);		//Curror Shift Right
	Write_CMD(C_ON);		//turn on  LCD
}

//========================================================================
// 函数: void ClearLine(u8 row)
// 描述: 清除1行
// 参数: row: 行(0或1)
// 返回: none.
// 版本: VER1.0
// 日期: 2024-9-30
// 备注: 
//========================================================================
void ClearLine(u8 row)
{
	u8 i;
	Write_CMD(((row & 1) << 6) | 0x80);
	for(i=0; i<LineLength; i++)	Write_DIS_Data(' ');
}

//========================================================================
// 函数: void WriteChar(u8 row, u8 column, u8 dat)
// 描述: 指定行、列和字符, 写一个字符
// 参数: row: 行(0或1),  column: 第几个字符(0~15),  dat: 要写的字符.
// 返回: none.
// 版本: VER1.0
// 日期: 2024-9-30
// 备注: 
//========================================================================
void WriteChar(u8 row, u8 column, u8 dat)
{
	Write_CMD((((row & 1) << 6) + column) | 0x80);
	Write_DIS_Data(dat);
}

//========================================================================
// 函数: void PutString(u8 row, u8 column, u8 *puts)
// 描述: 写一个字符串，指定行、列和字符串首地址
// 参数: row: 行(0或1),  column: 第几个字符(0~15),  puts: 要写的字符串指针.
// 返回: none.
// 版本: VER1.0
// 日期: 2024-9-30
// 备注: 
//========================================================================
void PutString(u8 row, u8 column, u8 *puts)
{
	Write_CMD((((row & 1) << 6) + column) | 0x80);
	for ( ;  *puts != 0;  puts++)		//遇到停止符0结束
	{
		Write_DIS_Data(*puts);
		if(++column >= LineLength)	break;
	}
}

//******************** LCD Module END ***************************
