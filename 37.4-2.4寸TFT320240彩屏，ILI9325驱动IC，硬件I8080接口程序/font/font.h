/*---------------------------------------------------------------------*/
/* --- STC AI Limited -------------------------------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* 液晶屏驱动程序参考wiki技术网站提供的开源源码，仅供学习使用          */
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序        */
/*---------------------------------------------------------------------*/

//=========================================电源接线================================================//
//VDD接DC 3.3V电源
//GND接地
//=======================================液晶屏数据线接线==========================================//
//本模块数据总线类型为8位并口
//液晶屏模块              STC8051U
// LCD_D0~D7     接       P20~P27        //液晶屏8位数据线
//=======================================液晶屏控制线接线==========================================//
//液晶屏模块              STC8051U
// LCD_RS        接        P45           //数据/命令选择控制信号
// LCD_RD        接        P37           //读控制信号
// LCD_RST       接        P47           //复位信号
// LCD_WR        接        P36           //写控制信号
// LCD_CS        接        P05/P53       //片选控制信号
//===========================================触摸屏接线============================================//
//不使用触摸或者模块本身不带触摸，则可不连接
//触摸屏使用的数据总线类型为SPI
//液晶屏模块              STC8051U
//  T_CS         接        P15          //触摸屏片选控制信号
//  T_CLK        接        P32          //触摸屏SPI时钟信号
//  T_DO         接        P33          //触摸屏SPI读信号
//  T_DIN        接        P34          //触摸屏SPI写信号
//  T_IRQ        接        P14          //触摸屏响应检查信号
//================================================================================================//
// 本实验测试使用的2.4寸320*240的并口彩屏，是在淘宝店 https://kcer001.taobao.com/ 提供的样品彩屏上测试通过的
//**************************************************************************************************/
#ifndef __FONT_H
#define __FONT_H 	

//ASCII码字库
//字体取模：宋体10
//宽度高度：8*12
//扫描模式：水平扫描，从左到右，从上到下（高位在前）
//数据格式：C表格(格式1)
struct FONT_1206
{
    unsigned char dat[12];
};

struct FONT_1206 code asc2_1206[] =
{
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*' ',0*/
  },
  {
    0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x04,0x00, /*'!',1*/
  },
  {
    0x00,0x14,0x14,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*'"',2*/
  },
  {
    0x00,0x00,0x24,0x24,0x3F,0x24,0x12,0x12,0x3F,0x12,0x12,0x00, /*'#',3*/
  },
  {
    0x00,0x08,0x1C,0x2A,0x0A,0x0C,0x18,0x28,0x2A,0x2A,0x1C,0x08, /*'$',4*/
  },
  {
    0x00,0x00,0x12,0x15,0x0D,0x0D,0x16,0x2C,0x2C,0x2A,0x12,0x00, /*'%',5*/
  },
  {
    0x00,0x00,0x04,0x0A,0x0A,0x06,0x32,0x15,0x15,0x49,0x36,0x00, /*'&',6*/
  },
  {
    0x00,0x06,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*''',7*/
  },
  {
    0x00,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20, /*'(',8*/
  },
  {
    0x00,0x02,0x04,0x04,0x08,0x08,0x08,0x08,0x08,0x04,0x04,0x02, /*')',9*/
  },
  {
    0x00,0x00,0x00,0x08,0x2A,0x1C,0x1C,0x2A,0x08,0x00,0x00,0x00, /*'*',10*/
  },
  {
    0x00,0x00,0x00,0x08,0x08,0x08,0x7F,0x08,0x08,0x08,0x00,0x00, /*'+',11*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x04,0x02, /*',',12*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00, /*'-',13*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00, /*'.',14*/
  },
  {
    0x00,0x20,0x10,0x10,0x08,0x08,0x04,0x04,0x04,0x02,0x02,0x01, /*'/',15*/
  },
  {
    0x00,0x00,0x1C,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x1C,0x00, /*'0',16*/
  },
  {
    0x00,0x00,0x08,0x0C,0x08,0x08,0x08,0x08,0x08,0x08,0x1C,0x00, /*'1',17*/
  },
  {
    0x00,0x00,0x1C,0x22,0x22,0x20,0x10,0x08,0x04,0x22,0x3E,0x00, /*'2',18*/
  },
  {
    0x00,0x00,0x1C,0x22,0x20,0x20,0x18,0x20,0x20,0x22,0x1C,0x00, /*'3',19*/
  },
  {
    0x00,0x00,0x10,0x10,0x18,0x14,0x14,0x12,0x3E,0x10,0x38,0x00, /*'4',20*/
  },
  {
    0x00,0x00,0x3E,0x02,0x02,0x1E,0x22,0x20,0x22,0x22,0x1C,0x00, /*'5',21*/
  },
  {
    0x00,0x00,0x18,0x24,0x02,0x1A,0x26,0x22,0x22,0x22,0x1C,0x00, /*'6',22*/
  },
  {
    0x00,0x00,0x3E,0x22,0x10,0x10,0x10,0x08,0x08,0x08,0x08,0x00, /*'7',23*/
  },
  {
    0x00,0x00,0x1C,0x22,0x22,0x22,0x1C,0x22,0x22,0x22,0x1C,0x00, /*'8',24*/
  },
  {
    0x00,0x00,0x1C,0x22,0x22,0x22,0x32,0x2C,0x20,0x12,0x0C,0x00, /*'9',25*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x04,0x00, /*':',26*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x08,0x08, /*';',27*/
  },
  {
    0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x00, /*'<',28*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x3F,0x00,0x3F,0x00,0x00,0x00,0x00, /*'=',29*/
  },
  {
    0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x10,0x08,0x04,0x02,0x00, /*'>',30*/
  },
  {
    0x00,0x00,0x1C,0x22,0x22,0x20,0x10,0x08,0x08,0x00,0x08,0x00, /*'?',31*/
  },
  {
    0x00,0x00,0x3C,0x42,0x59,0x55,0x55,0x55,0x39,0x42,0x3C,0x00, /*'@',32*/
  },
  {
    0x00,0x00,0x08,0x08,0x14,0x14,0x14,0x1C,0x22,0x22,0x77,0x00, /*'A',33*/
  },
  {
    0x00,0x00,0x1F,0x22,0x22,0x22,0x1E,0x22,0x22,0x22,0x1F,0x00, /*'B',34*/
  },
  {
    0x00,0x00,0x3C,0x22,0x01,0x01,0x01,0x01,0x01,0x22,0x1C,0x00, /*'C',35*/
  },
  {
    0x00,0x00,0x0F,0x12,0x22,0x22,0x22,0x22,0x22,0x12,0x0F,0x00, /*'D',36*/
  },
  {
    0x00,0x00,0x3F,0x22,0x02,0x12,0x1E,0x12,0x02,0x22,0x3F,0x00, /*'E',37*/
  },
  {
    0x00,0x00,0x3F,0x22,0x02,0x12,0x1E,0x12,0x02,0x02,0x07,0x00, /*'F',38*/
  },
  {
    0x00,0x00,0x1C,0x12,0x01,0x01,0x01,0x39,0x11,0x12,0x0C,0x00, /*'G',39*/
  },
  {
    0x00,0x00,0x77,0x22,0x22,0x22,0x3E,0x22,0x22,0x22,0x77,0x00, /*'H',40*/
  },
  {
    0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00, /*'I',41*/
  },
  {
    0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x09, /*'J',42*/
  },
  {
    0x00,0x00,0x37,0x12,0x0A,0x06,0x0E,0x0A,0x12,0x12,0x37,0x00, /*'K',43*/
  },
  {
    0x00,0x00,0x07,0x02,0x02,0x02,0x02,0x02,0x02,0x22,0x3F,0x00, /*'L',44*/
  },
  {
    0x00,0x00,0x77,0x36,0x36,0x36,0x2A,0x2A,0x2A,0x2A,0x6B,0x00, /*'M',45*/
  },
  {
    0x00,0x00,0x77,0x26,0x26,0x2A,0x2A,0x2A,0x32,0x32,0x27,0x00, /*'N',46*/
  },
  {
    0x00,0x00,0x0C,0x12,0x21,0x21,0x21,0x21,0x21,0x12,0x0C,0x00, /*'O',47*/
  },
  {
    0x00,0x00,0x1F,0x22,0x22,0x22,0x1E,0x02,0x02,0x02,0x07,0x00, /*'P',48*/
  },
  {
    0x00,0x00,0x0C,0x12,0x21,0x21,0x21,0x21,0x2D,0x12,0x1C,0x30, /*'Q',49*/
  },
  {
    0x00,0x00,0x1F,0x22,0x22,0x1E,0x0A,0x12,0x12,0x22,0x67,0x00, /*'R',50*/
  },
  {
    0x00,0x00,0x3C,0x22,0x02,0x04,0x18,0x20,0x20,0x22,0x1E,0x00, /*'S',51*/
  },
  {
    0x00,0x00,0x3E,0x2A,0x08,0x08,0x08,0x08,0x08,0x08,0x1C,0x00, /*'T',52*/
  },
  {
    0x00,0x00,0x77,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x1C,0x00, /*'U',53*/
  },
  {
    0x00,0x00,0x77,0x22,0x22,0x14,0x14,0x14,0x14,0x08,0x08,0x00, /*'V',54*/
  },
  {
    0x00,0x00,0x6B,0x2A,0x2A,0x2A,0x2A,0x36,0x14,0x14,0x14,0x00, /*'W',55*/
  },
  {
    0x00,0x00,0x33,0x12,0x12,0x0C,0x0C,0x0C,0x12,0x12,0x33,0x00, /*'X',56*/
  },
  {
    0x00,0x00,0x77,0x22,0x14,0x14,0x08,0x08,0x08,0x08,0x1C,0x00, /*'Y',57*/
  },
  {
    0x00,0x00,0x3E,0x12,0x10,0x08,0x08,0x08,0x04,0x24,0x3E,0x00, /*'Z',58*/
  },
  {
    0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x38, /*'[',59*/
  },
  {
    0x00,0x00,0x02,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20, /*'\',60*/
  },
  {
    0x00,0x0E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0E, /*']',61*/
  },
  {
    0x08,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*'^',62*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*'_',63*/
  },
  {
    0x06,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*'`',64*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x38,0x24,0x22,0x7C,0x00, /*'a',65*/
  },
  {
    0x00,0x00,0x03,0x02,0x02,0x1E,0x22,0x22,0x22,0x22,0x1E,0x00, /*'b',66*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x3C,0x22,0x02,0x02,0x22,0x1C,0x00, /*'c',67*/
  },
  {
    0x00,0x00,0x30,0x20,0x20,0x3C,0x22,0x22,0x22,0x22,0x7C,0x00, /*'d',68*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x3E,0x02,0x22,0x1C,0x00, /*'e',69*/
  },
  {
    0x00,0x00,0x18,0x24,0x04,0x1F,0x04,0x04,0x04,0x04,0x1E,0x00, /*'f',70*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x3C,0x12,0x12,0x0C,0x02,0x1C,0x22, /*'g',71*/
  },
  {
    0x00,0x00,0x03,0x02,0x02,0x1A,0x26,0x22,0x22,0x22,0x77,0x00, /*'h',72*/
  },
  {
    0x00,0x00,0x08,0x00,0x00,0x0E,0x08,0x08,0x08,0x08,0x3E,0x00, /*'i',73*/
  },
  {
    0x00,0x00,0x10,0x00,0x00,0x1C,0x10,0x10,0x10,0x10,0x10,0x10, /*'j',74*/
  },
  {
    0x00,0x00,0x03,0x02,0x02,0x3A,0x12,0x0A,0x0E,0x12,0x37,0x00, /*'k',75*/
  },
  {
    0x00,0x00,0x0E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00, /*'l',76*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x1F,0x2A,0x2A,0x2A,0x2A,0x6B,0x00, /*'m',77*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x1B,0x26,0x22,0x22,0x22,0x77,0x00, /*'n',78*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x22,0x22,0x22,0x1C,0x00, /*'o',79*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x22,0x1E,0x02, /*'p',80*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x3C,0x22,0x22,0x22,0x22,0x3C,0x20, /*'q',81*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x36,0x0C,0x04,0x04,0x04,0x1E,0x00, /*'r',82*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x3C,0x22,0x0C,0x10,0x22,0x1E,0x00, /*'s',83*/
  },
  {
    0x00,0x00,0x00,0x04,0x04,0x1F,0x04,0x04,0x04,0x24,0x18,0x00, /*'t',84*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x33,0x22,0x22,0x22,0x32,0x6C,0x00, /*'u',85*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x63,0x22,0x22,0x14,0x14,0x08,0x00, /*'v',86*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x6B,0x2A,0x2A,0x2A,0x14,0x14,0x00, /*'w',87*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x37,0x12,0x0C,0x0C,0x12,0x3B,0x00, /*'x',88*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x77,0x22,0x14,0x14,0x08,0x08,0x08, /*'y',89*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x3E,0x12,0x08,0x08,0x24,0x3E,0x00, /*'z',90*/
  },
  {
    0x00,0x30,0x10,0x10,0x10,0x10,0x08,0x10,0x10,0x10,0x10,0x30, /*'{',91*/
  },
  {
    0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08, /*'|',92*/
  },
  {
    0x00,0x06,0x04,0x04,0x04,0x04,0x08,0x04,0x04,0x04,0x04,0x06, /*'}',93*/
  },
  {
    0x2C,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*'~',94*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*'',95*/
  },
};

//ASCII码字库
//字体取模：宋体12
//宽度高度：8*16
//扫描模式：水平扫描，从左到右，从上到下（高位在前）
//数据格式：C表格(格式1)
struct FONT_1608
{
    unsigned char dat[16];
};

struct FONT_1608 code asc2_1608[] =
{
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*' ',0*/
  },
  {
    0x00,0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x08,0x08,0x00,0x00, /*'!',1*/
  },
  {
    0x00,0x48,0x24,0x24,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*'"',2*/
  },
  {
    0x00,0x00,0x00,0x48,0x48,0x48,0x7E,0x24,0x24,0x24,0x7E,0x24,0x24,0x24,0x00,0x00, /*'#',3*/
  },
  {
    0x00,0x00,0x10,0x3C,0x52,0x52,0x12,0x1C,0x30,0x50,0x50,0x52,0x52,0x3C,0x10,0x10, /*'$',4*/
  },
  {
    0x00,0x00,0x00,0x22,0x25,0x15,0x15,0x0D,0x2A,0x58,0x54,0x54,0x52,0x22,0x00,0x00, /*'%',5*/
  },
  {
    0x00,0x00,0x00,0x0C,0x12,0x12,0x12,0x0A,0x76,0x25,0x29,0x19,0x91,0x6E,0x00,0x00, /*'&',6*/
  },
  {
    0x00,0x06,0x04,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*''',7*/
  },
  {
    0x00,0x40,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20,0x40,0x00, /*'(',8*/
  },
  {
    0x00,0x02,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x02,0x00, /*')',9*/
  },
  {
    0x00,0x00,0x00,0x00,0x08,0x08,0x6B,0x1C,0x1C,0x6B,0x08,0x08,0x00,0x00,0x00,0x00, /*'*',10*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x10,0xFE,0x10,0x10,0x10,0x00,0x00,0x00,0x00, /*'+',11*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x04,0x04,0x02, /*',',12*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*'-',13*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00,0x00, /*'.',14*/
  },
  {
    0x00,0x00,0x40,0x20,0x20,0x20,0x10,0x10,0x08,0x08,0x08,0x04,0x04,0x02,0x02,0x00, /*'/',15*/
  },
  {
    0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00, /*'0',16*/
  },
  {
    0x00,0x00,0x00,0x10,0x1C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00, /*'1',17*/
  },
  {
    0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x40,0x20,0x10,0x08,0x04,0x42,0x7E,0x00,0x00, /*'2',18*/
  },
  {
    0x00,0x00,0x00,0x3C,0x42,0x42,0x40,0x20,0x18,0x20,0x40,0x42,0x42,0x3C,0x00,0x00, /*'3',19*/
  },
  {
    0x00,0x00,0x00,0x20,0x30,0x30,0x28,0x24,0x24,0x22,0xFE,0x20,0x20,0xF8,0x00,0x00, /*'4',20*/
  },
  {
    0x00,0x00,0x00,0x7E,0x02,0x02,0x02,0x1E,0x22,0x40,0x40,0x42,0x22,0x1C,0x00,0x00, /*'5',21*/
  },
  {
    0x00,0x00,0x00,0x18,0x24,0x02,0x02,0x3A,0x46,0x42,0x42,0x42,0x44,0x38,0x00,0x00, /*'6',22*/
  },
  {
    0x00,0x00,0x00,0x7E,0x42,0x20,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x00,0x00, /*'7',23*/
  },
  {
    0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00, /*'8',24*/
  },
  {
    0x00,0x00,0x00,0x1C,0x22,0x42,0x42,0x42,0x62,0x5C,0x40,0x40,0x24,0x18,0x00,0x00, /*'9',25*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00, /*':',26*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x08, /*';',27*/
  },
  {
    0x00,0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x40,0x00,0x00, /*'<',28*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00, /*'=',29*/
  },
  {
    0x00,0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00, /*'>',30*/
  },
  {
    0x00,0x00,0x00,0x3C,0x42,0x42,0x46,0x20,0x10,0x10,0x10,0x00,0x18,0x18,0x00,0x00, /*'?',31*/
  },
  {
    0x00,0x00,0x00,0x1C,0x22,0x5A,0x55,0x55,0x55,0x55,0x55,0x3A,0x42,0x3C,0x00,0x00, /*'@',32*/
  },
  {
    0x00,0x00,0x00,0x08,0x08,0x18,0x14,0x14,0x24,0x3C,0x22,0x42,0x42,0xE7,0x00,0x00, /*'A',33*/
  },
  {
    0x00,0x00,0x00,0x1F,0x22,0x22,0x22,0x1E,0x22,0x42,0x42,0x42,0x22,0x1F,0x00,0x00, /*'B',34*/
  },
  {
    0x00,0x00,0x00,0x7C,0x42,0x42,0x01,0x01,0x01,0x01,0x01,0x42,0x22,0x1C,0x00,0x00, /*'C',35*/
  },
  {
    0x00,0x00,0x00,0x1F,0x22,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1F,0x00,0x00, /*'D',36*/
  },
  {
    0x00,0x00,0x00,0x3F,0x42,0x12,0x12,0x1E,0x12,0x12,0x02,0x42,0x42,0x3F,0x00,0x00, /*'E',37*/
  },
  {
    0x00,0x00,0x00,0x3F,0x42,0x12,0x12,0x1E,0x12,0x12,0x02,0x02,0x02,0x07,0x00,0x00, /*'F',38*/
  },
  {
    0x00,0x00,0x00,0x3C,0x22,0x22,0x01,0x01,0x01,0x71,0x21,0x22,0x22,0x1C,0x00,0x00, /*'G',39*/
  },
  {
    0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0xE7,0x00,0x00, /*'H',40*/
  },
  {
    0x00,0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00, /*'I',41*/
  },
  {
    0x00,0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x11,0x0F, /*'J',42*/
  },
  {
    0x00,0x00,0x00,0x77,0x22,0x12,0x0A,0x0E,0x0A,0x12,0x12,0x22,0x22,0x77,0x00,0x00, /*'K',43*/
  },
  {
    0x00,0x00,0x00,0x07,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x42,0x7F,0x00,0x00, /*'L',44*/
  },
  {
    0x00,0x00,0x00,0x77,0x36,0x36,0x36,0x36,0x36,0x2A,0x2A,0x2A,0x2A,0x6B,0x00,0x00, /*'M',45*/
  },
  {
    0x00,0x00,0x00,0xE3,0x46,0x46,0x4A,0x4A,0x52,0x52,0x52,0x62,0x62,0x47,0x00,0x00, /*'N',46*/
  },
  {
    0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x41,0x22,0x1C,0x00,0x00, /*'O',47*/
  },
  {
    0x00,0x00,0x00,0x3F,0x42,0x42,0x42,0x42,0x3E,0x02,0x02,0x02,0x02,0x07,0x00,0x00, /*'P',48*/
  },
  {
    0x00,0x00,0x00,0x1C,0x22,0x41,0x41,0x41,0x41,0x41,0x41,0x4D,0x32,0x1C,0x60,0x00, /*'Q',49*/
  },
  {
    0x00,0x00,0x00,0x3F,0x42,0x42,0x42,0x3E,0x12,0x12,0x22,0x22,0x42,0xC7,0x00,0x00, /*'R',50*/
  },
  {
    0x00,0x00,0x00,0x7C,0x42,0x42,0x02,0x04,0x18,0x20,0x40,0x42,0x42,0x3E,0x00,0x00, /*'S',51*/
  },
  {
    0x00,0x00,0x00,0x7F,0x49,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x1C,0x00,0x00, /*'T',52*/
  },
  {
    0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00, /*'U',53*/
  },
  {
    0x00,0x00,0x00,0xE7,0x42,0x42,0x22,0x24,0x24,0x14,0x14,0x18,0x08,0x08,0x00,0x00, /*'V',54*/
  },
  {
    0x00,0x00,0x00,0x6B,0x2A,0x2A,0x2A,0x2A,0x2A,0x36,0x14,0x14,0x14,0x14,0x00,0x00, /*'W',55*/
  },
  {
    0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x18,0x24,0x24,0x42,0xE7,0x00,0x00, /*'X',56*/
  },
  {
    0x00,0x00,0x00,0x77,0x22,0x22,0x14,0x14,0x08,0x08,0x08,0x08,0x08,0x1C,0x00,0x00, /*'Y',57*/
  },
  {
    0x00,0x00,0x00,0x7E,0x21,0x20,0x10,0x10,0x08,0x04,0x04,0x42,0x42,0x3F,0x00,0x00, /*'Z',58*/
  },
  {
    0x00,0x78,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x78,0x00, /*'[',59*/
  },
  {
    0x00,0x00,0x02,0x04,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x20,0x20,0x20,0x40,0x40, /*'\',60*/
  },
  {
    0x00,0x1E,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1E,0x00, /*']',61*/
  },
  {
    0x00,0x18,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*'^',62*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF, /*'_',63*/
  },
  {
    0x00,0x06,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*'`',64*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x30,0x2C,0x22,0x32,0x6C,0x00,0x00, /*'a',65*/
  },
  {
    0x00,0x00,0x00,0x00,0x03,0x02,0x02,0x1A,0x26,0x42,0x42,0x42,0x26,0x1A,0x00,0x00, /*'b',66*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x02,0x02,0x02,0x44,0x38,0x00,0x00, /*'c',67*/
  },
  {
    0x00,0x00,0x00,0x00,0x60,0x40,0x40,0x7C,0x42,0x42,0x42,0x42,0x62,0xDC,0x00,0x00, /*'d',68*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x7E,0x02,0x42,0x3C,0x00,0x00, /*'e',69*/
  },
  {
    0x00,0x00,0x00,0x00,0x30,0x48,0x08,0x3E,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00, /*'f',70*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x22,0x22,0x1C,0x02,0x3C,0x42,0x42,0x3C, /*'g',71*/
  },
  {
    0x00,0x00,0x00,0x00,0x03,0x02,0x02,0x3A,0x46,0x42,0x42,0x42,0x42,0xE7,0x00,0x00, /*'h',72*/
  },
  {
    0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x0E,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00, /*'i',73*/
  },
  {
    0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x38,0x20,0x20,0x20,0x20,0x20,0x20,0x22,0x1E, /*'j',74*/
  },
  {
    0x00,0x00,0x00,0x00,0x03,0x02,0x02,0x72,0x12,0x0A,0x0E,0x12,0x22,0x77,0x00,0x00, /*'k',75*/
  },
  {
    0x00,0x00,0x00,0x08,0x0E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3E,0x00,0x00, /*'l',76*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x92,0x92,0x92,0x92,0x92,0xB7,0x00,0x00, /*'m',77*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3B,0x46,0x42,0x42,0x42,0x42,0xE7,0x00,0x00, /*'n',78*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00, /*'o',79*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1B,0x26,0x42,0x42,0x42,0x26,0x1A,0x02,0x07, /*'p',80*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x58,0x64,0x42,0x42,0x42,0x64,0x58,0x40,0xE0, /*'q',81*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x4C,0x04,0x04,0x04,0x04,0x1F,0x00,0x00, /*'r',82*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x42,0x02,0x3C,0x40,0x42,0x3E,0x00,0x00, /*'s',83*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x3E,0x08,0x08,0x08,0x08,0x48,0x30,0x00,0x00, /*'t',84*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x63,0x42,0x42,0x42,0x42,0x62,0xDC,0x00,0x00, /*'u',85*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x77,0x22,0x22,0x14,0x14,0x08,0x08,0x00,0x00, /*'v',86*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDB,0x91,0x52,0x5A,0x2A,0x24,0x24,0x00,0x00, /*'w',87*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6E,0x24,0x18,0x18,0x18,0x24,0x76,0x00,0x00, /*'x',88*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x08,0x08,0x06, /*'y',89*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x22,0x10,0x08,0x08,0x44,0x7E,0x00,0x00, /*'z',90*/
  },
  {
    0x00,0xC0,0x20,0x20,0x20,0x20,0x20,0x20,0x10,0x20,0x20,0x20,0x20,0x20,0xC0,0x00, /*'{',91*/
  },
  {
    0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10, /*'|',92*/
  },
  {
    0x00,0x03,0x04,0x04,0x04,0x04,0x04,0x04,0x08,0x04,0x04,0x04,0x04,0x04,0x03,0x00, /*'}',93*/
  },
  {
    0x04,0x5A,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*'~',94*/
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /*'',95*/
  },
};

//字体取模：宋体12
//宽度高度：16*16
//扫描模式：水平扫描，从左到右，从上到下（低位在前）
//数据格式：C表格(格式2)
typedef struct 
{
    unsigned char dat[32];
    char txt[2];
}typFNT_GB16; 
typFNT_GB16 code tfont16[] =
{
  {
    0x00,0x00,0x27,0xFC,0x14,0x04,0x14,0xA4,0x81,0x10,0x42,0x08,0x40,0x40,0x10,0x40,
    0x17,0xFC,0x20,0x40,0xE0,0xE0,0x21,0x50,0x22,0x48,0x2C,0x46,0x20,0x40,0x00,0x40,"深", /* 0 */ 
  },
  {
    0x11,0x04,0x11,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0xFD,0x24,0x11,0x24,0x11,0x24,
    0x11,0x24,0x11,0x24,0x11,0x24,0x1D,0x24,0xE1,0x24,0x42,0x24,0x02,0x04,0x04,0x04,"圳", /* 1 */ 
  },
  {
    0x00,0x00,0x7F,0xFC,0x40,0x04,0x40,0x04,0x5F,0xF4,0x41,0x04,0x41,0x04,0x4F,0xE4,
    0x41,0x04,0x41,0x44,0x41,0x24,0x5F,0xF4,0x40,0x04,0x40,0x04,0x7F,0xFC,0x40,0x04,"国", /* 2 */ 
  },
  {
    0x08,0x20,0x08,0x20,0xFF,0xFE,0x08,0x20,0x08,0x20,0x02,0x00,0x01,0x00,0x00,0x80,
    0x04,0x08,0x24,0x04,0x24,0x02,0x44,0x02,0x84,0x10,0x04,0x10,0x03,0xF0,0x00,0x00,"芯", /* 3 */ 
  },
  {
    0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x02,0x80,0x02,0x80,
    0x04,0x40,0x04,0x40,0x08,0x20,0x08,0x20,0x10,0x10,0x20,0x08,0x40,0x04,0x80,0x02,"人", /* 4 */ 
  },
  {
    0x00,0x00,0x00,0x00,0x7F,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
    0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00,"工", /* 5 */ 
  },
  {
    0x20,0x00,0x3E,0x7C,0x48,0x44,0x08,0x44,0xFF,0x44,0x14,0x44,0x22,0x7C,0x40,0x00,
    0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,"智", /* 6 */ 
  },
  {
    0x10,0x40,0x24,0x44,0x42,0x48,0xFF,0x70,0x01,0x40,0x00,0x42,0x7E,0x42,0x42,0x3E,
    0x42,0x00,0x7E,0x44,0x42,0x48,0x42,0x70,0x7E,0x40,0x42,0x42,0x4A,0x42,0x44,0x3E,"能", /* 7 */ 
  },
  {
    0x08,0x10,0x1D,0x10,0xF0,0x90,0x10,0x90,0x10,0x10,0xFD,0x10,0x10,0x90,0x38,0x90,
    0x34,0x10,0x50,0x1E,0x53,0xF0,0x90,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,"科", /* 8 */ 
  },
  {
    0x10,0x20,0x10,0x20,0x10,0x20,0x13,0xFE,0xFC,0x20,0x10,0x20,0x10,0x20,0x15,0xFC,
    0x18,0x84,0x30,0x88,0xD0,0x48,0x10,0x50,0x10,0x20,0x10,0x50,0x51,0x88,0x26,0x06,"技", /* 9 */ 
  },
  {
    0x02,0x00,0x02,0x00,0xFF,0xFE,0x04,0x00,0x04,0x00,0x0F,0xF0,0x08,0x10,0x18,0x10,
    0x2F,0xF0,0x48,0x10,0x88,0x10,0x0F,0xF0,0x08,0x10,0x08,0x10,0x08,0x50,0x08,0x20,"有", /* 10 */ 
  },
  {
    0x00,0x00,0x7B,0xF8,0x4A,0x08,0x52,0x08,0x53,0xF8,0x62,0x08,0x52,0x08,0x4B,0xF8,
    0x4A,0x44,0x4A,0x48,0x6A,0x30,0x52,0x20,0x42,0x10,0x42,0x88,0x43,0x06,0x42,0x00,"限", /* 11 */ 
  },
  {
    0x00,0x80,0x04,0x80,0x04,0x80,0x08,0x40,0x08,0x40,0x10,0x20,0x20,0x10,0x42,0x08,
    0x82,0x06,0x04,0x00,0x04,0x40,0x08,0x20,0x10,0x20,0x3F,0xF0,0x10,0x10,0x00,0x00,"公", /* 12 */ 
  },
  {
    0x00,0x00,0x3F,0xF8,0x00,0x08,0x00,0x08,0x7F,0xE8,0x00,0x08,0x00,0x08,0x1F,0x88,
    0x10,0x88,0x10,0x88,0x10,0x88,0x10,0x88,0x1F,0x88,0x10,0x88,0x00,0x28,0x00,0x10,"司", /* 13 */ 
  },
  {
    0x02,0x00,0x01,0x00,0x7F,0xFE,0x40,0x02,0x82,0x04,0x02,0x00,0x7F,0xFC,0x04,0x00,
    0x04,0x80,0x08,0x80,0x09,0x00,0x11,0x00,0x22,0x20,0x44,0x10,0x8F,0xF8,0x04,0x08,"宏", /* 14 */ 
  },
  {
    0x0F,0xE0,0x08,0x20,0x08,0x20,0x0F,0xE0,0x08,0x20,0x08,0x20,0x0F,0xE0,0x00,0x00,
    0x7E,0xFC,0x42,0x84,0x42,0x84,0x7E,0xFC,0x42,0x84,0x42,0x84,0x7E,0xFC,0x42,0x84,"晶", /* 15 */ 
  },
  {
    0x00,0x80,0x00,0x80,0xFC,0x80,0x04,0xFC,0x05,0x04,0x49,0x08,0x2A,0x40,0x14,0x40,
    0x10,0x40,0x28,0xA0,0x24,0xA0,0x45,0x10,0x81,0x10,0x02,0x08,0x04,0x04,0x08,0x02,"欢", /* 16 */ 
  },
  {
    0x00,0x00,0x20,0x80,0x13,0x3C,0x12,0x24,0x02,0x24,0x02,0x24,0xF2,0x24,0x12,0x24,
    0x12,0x24,0x12,0xB4,0x13,0x28,0x12,0x20,0x10,0x20,0x28,0x20,0x47,0xFE,0x00,0x00,"迎", /* 17 */ 
  },
  {
    0x09,0x00,0x09,0x00,0x11,0xFC,0x32,0x04,0x54,0x48,0x99,0x50,0x11,0x48,0x12,0x44,
    0x14,0x44,0x11,0x40,0x10,0x80,0x02,0x00,0x51,0x04,0x51,0x12,0x90,0x12,0x0F,0xF0,"您", /* 18 */ 
  },
  {
    0x10,0x40,0x10,0x40,0x20,0x40,0x23,0xFC,0x48,0x40,0xFA,0x48,0x12,0x48,0x22,0x48,
    0x42,0x48,0xFB,0xF8,0x40,0x48,0x00,0x40,0x18,0x42,0xE0,0x42,0x40,0x3E,0x00,0x00,"纯", /* 19 */ 
  },
  {
    0x08,0x00,0x08,0x00,0x1F,0xE0,0x20,0x20,0x40,0x40,0xBF,0xF8,0x21,0x08,0x21,0x08,
    0x21,0x08,0x3F,0xF8,0x20,0x00,0x20,0x02,0x20,0x02,0x20,0x02,0x1F,0xFE,0x00,0x00,"色", /* 20 */ 
  },
  {
    0x20,0x40,0x20,0x40,0x27,0xFC,0x20,0x40,0x23,0xF8,0xFA,0x08,0x23,0xF8,0x22,0x08,
    0x23,0xF8,0x22,0x08,0x23,0xF8,0x3A,0x08,0xEF,0xFE,0x41,0x10,0x02,0x08,0x04,0x04,"填", /* 21 */ 
  },
  {
    0x02,0x00,0x01,0x00,0xFF,0xFE,0x04,0x00,0x04,0x00,0x08,0x20,0x10,0x10,0x3F,0xF8,
    0x04,0x48,0x04,0x40,0x04,0x40,0x04,0x40,0x08,0x44,0x08,0x44,0x10,0x44,0x60,0x3C,"充", /* 22 */ 
  },
  {
    0x20,0x00,0x21,0xFE,0x3D,0x00,0x51,0x00,0x91,0x00,0x11,0xFC,0x11,0x04,0xFF,0x04,
    0x11,0x04,0x11,0x04,0x11,0xFC,0x29,0x00,0x25,0x00,0x45,0x00,0x41,0xFE,0x80,0x00,"矩", /* 23 */ 
  },
  {
    0x00,0x00,0x7F,0x84,0x12,0x04,0x12,0x08,0x12,0x10,0x12,0x22,0x12,0x02,0xFF,0xC4,
    0x12,0x08,0x12,0x10,0x12,0x22,0x12,0x02,0x22,0x04,0x22,0x08,0x42,0x10,0x82,0x60,"形", /* 24 */ 
  },
  {
    0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00,0x4F,0xE4,0x49,0x24,0x49,0x24,0x4F,0xE4,
    0x49,0x24,0x49,0x24,0x49,0x24,0x4F,0xE4,0x40,0x04,0x40,0x04,0x7F,0xFC,0x00,0x04,"画", /* 25 */ 
  },
  {
    0x00,0x00,0x7F,0xFC,0x40,0x04,0x4F,0xE4,0x48,0x24,0x4F,0xE4,0x40,0x04,0x5F,0xF4,
    0x50,0x14,0x51,0x14,0x51,0x14,0x52,0x94,0x44,0x44,0x48,0x24,0x7F,0xFC,0x40,0x04,"圆", /* 26 */ 
  },
  {
    0x00,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF8,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00,"三", /* 27 */ 
  },
  {
    0x08,0x00,0x08,0x00,0x1F,0xE0,0x20,0x20,0x40,0x40,0xBF,0xF8,0x21,0x08,0x21,0x08,
    0x3F,0xF8,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x41,0x08,0x41,0x28,0x80,0x10,"角", /* 28 */ 
  },
  {
    0x00,0x00,0x7F,0xFC,0x42,0x04,0x42,0x04,0x47,0xE4,0x4C,0x44,0x52,0x84,0x41,0x04,
    0x46,0xC4,0x78,0x3C,0x43,0x04,0x40,0x84,0x46,0x04,0x41,0x84,0x7F,0xFC,0x40,0x04,"图", /* 29 */ 
  },
  {
    0x00,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0x1F,0xFC,0x10,0x00,0x10,0x00,
    0x10,0x00,0x1F,0xE0,0x10,0x20,0x10,0x20,0x10,0x20,0x20,0x20,0x20,0x20,0x40,0x20,"片", /* 30 */ 
  },
  {
    0x00,0x00,0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,
    0x04,0x40,0x44,0x44,0x24,0x44,0x14,0x48,0x14,0x50,0x04,0x40,0xFF,0xFE,0x00,0x00,"显", /* 31 */ 
  },
  {
    0x00,0x00,0x3F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x01,0x00,
    0x01,0x00,0x11,0x10,0x11,0x08,0x21,0x04,0x41,0x02,0x81,0x02,0x05,0x00,0x02,0x00,"示", /* 32 */ 
  },
  {
    0x08,0x20,0x08,0x20,0xFF,0xFE,0x08,0x20,0x00,0x10,0x00,0xF8,0x3F,0x00,0x11,0x10,
    0x08,0x20,0x01,0x00,0x7F,0xFC,0x05,0x40,0x09,0x20,0x31,0x18,0xC1,0x06,0x01,0x00,"菜", /* 33 */ 
  },
  {
    0x10,0x10,0x08,0x20,0x04,0x40,0x3F,0xF8,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,
    0x21,0x08,0x3F,0xF8,0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,"单", /* 34 */ 
  },
  {
    0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,
    0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,"中", /* 35 */ 
  },
  {
    0x08,0x20,0x08,0x20,0xFF,0xFE,0x08,0x20,0x01,0x00,0x01,0x00,0x1F,0xF0,0x11,0x10,
    0x11,0x10,0x11,0x10,0xFF,0xFE,0x02,0x80,0x04,0x40,0x08,0x20,0x30,0x18,0xC0,0x06,"英", /* 36 */ 
  },
  {
    0x02,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x10,0x10,0x10,0x10,0x08,0x20,0x08,0x20,
    0x04,0x40,0x02,0x80,0x01,0x00,0x02,0x80,0x04,0x40,0x08,0x20,0x30,0x18,0xC0,0x06,"文", /* 37 */ 
  },
  {
    0x10,0x40,0x10,0x20,0x23,0xFE,0x22,0x02,0x48,0x00,0xF9,0xFC,0x10,0x00,0x20,0x00,
    0x43,0xFE,0xF8,0x20,0x41,0x28,0x01,0x24,0x1A,0x22,0xE4,0x22,0x40,0xA0,0x00,0x40,"综", /* 38 */ 
  },
  {
    0x01,0x00,0x01,0x00,0x02,0x80,0x04,0x40,0x08,0x20,0x30,0x18,0xCF,0xE6,0x00,0x00,
    0x00,0x00,0x1F,0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,"合", /* 39 */ 
  },
  {
    0x02,0x00,0x01,0x00,0x7F,0xFC,0x00,0x00,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x00,0x00,
    0x7F,0xFE,0x40,0x02,0x8F,0xE4,0x08,0x20,0x08,0x20,0x10,0x22,0x20,0x22,0xC0,0x1E,"亮", /* 40 */ 
  },
  {
    0x01,0x00,0x00,0x80,0x3F,0xFE,0x22,0x20,0x22,0x20,0x3F,0xFC,0x22,0x20,0x22,0x20,
    0x23,0xE0,0x20,0x00,0x2F,0xF0,0x24,0x10,0x42,0x20,0x41,0xC0,0x86,0x30,0x38,0x0E,"度", /* 41 */ 
  },
  {
    0x00,0x04,0x27,0xC4,0x14,0x44,0x14,0x54,0x85,0x54,0x45,0x54,0x45,0x54,0x15,0x54,
    0x15,0x54,0x25,0x54,0xE5,0x54,0x21,0x04,0x22,0x84,0x22,0x44,0x24,0x14,0x08,0x08,"测", /* 42 */ 
  },
  {
    0x00,0x28,0x20,0x24,0x10,0x24,0x10,0x20,0x07,0xFE,0x00,0x20,0xF0,0x20,0x17,0xE0,
    0x11,0x20,0x11,0x10,0x11,0x10,0x15,0x10,0x19,0xCA,0x17,0x0A,0x02,0x06,0x00,0x02,"试", /* 43 */ 
  },
  {
    0x08,0x00,0x1D,0xFC,0xF1,0x04,0x11,0x04,0x11,0x04,0xFD,0xFC,0x10,0x00,0x30,0x00,
    0x39,0xFE,0x54,0x20,0x54,0x20,0x91,0xFC,0x10,0x20,0x10,0x20,0x13,0xFE,0x10,0x00,"程", /* 44 */ 
  },
  {
    0x01,0x00,0x00,0x80,0x3F,0xFE,0x20,0x00,0x23,0xF8,0x20,0x10,0x20,0xA0,0x20,0x40,
    0x2F,0xFE,0x20,0x42,0x20,0x44,0x20,0x40,0x40,0x40,0x40,0x40,0x81,0x40,0x00,0x80,"序", /* 45 */ 
  },
  {
    0x00,0x00,0x47,0xFC,0x24,0x44,0x24,0x44,0x05,0xF4,0x04,0x44,0xE4,0x44,0x27,0xFC,
    0x24,0x04,0x25,0xF4,0x25,0x14,0x2D,0x14,0x35,0xF4,0x24,0x04,0x04,0x14,0x08,0x08,"调", /* 46 */ 
  },
  {
    0x01,0x00,0x21,0x08,0x11,0x08,0x09,0x10,0x09,0x20,0x01,0x00,0xFF,0xFE,0x04,0x40,
    0x04,0x40,0x04,0x40,0x04,0x40,0x08,0x42,0x08,0x42,0x10,0x42,0x20,0x3E,0xC0,0x00,"光", /* 47 */ 
  },
  {
    0x08,0x08,0x48,0x1C,0x49,0xE0,0x49,0x00,0x49,0x00,0x7D,0xFC,0x41,0x44,0x41,0x44,
    0x79,0x44,0x49,0x28,0x49,0x28,0x49,0x10,0x49,0x10,0x4A,0x28,0x4A,0x44,0x8C,0x82,"版", /* 48 */ 
  },
  {
    0x10,0x00,0x13,0xFC,0x11,0x04,0x11,0x04,0xFD,0x04,0x10,0x88,0x30,0x88,0x38,0x88,
    0x54,0x50,0x54,0x50,0x90,0x20,0x10,0x20,0x10,0x50,0x10,0x88,0x11,0x04,0x16,0x02,"权", /* 49 */ 
  },
  {
    0x02,0x08,0x07,0x1C,0x38,0xE0,0x20,0x80,0x20,0x80,0x3E,0x80,0x22,0xFE,0x22,0x88,
    0x22,0x88,0x3E,0x88,0x20,0x88,0x20,0x88,0x41,0x08,0x41,0x08,0x82,0x08,0x04,0x08,"所", /* 50 */ 
  },
  {
    0x02,0x00,0x02,0x00,0xFF,0xFE,0x04,0x00,0x04,0x00,0x0F,0xF0,0x08,0x10,0x18,0x10,
    0x2F,0xF0,0x48,0x10,0x88,0x10,0x0F,0xF0,0x08,0x10,0x08,0x10,0x08,0x50,0x08,0x20,"有", /* 51 */ 
  },
  {
    0x00,0x00,0x3F,0xF8,0x20,0x08,0x20,0x08,0x3F,0xF8,0x24,0x10,0x22,0x20,0x2F,0xF8,
    0x22,0x20,0x22,0x20,0x3F,0xFC,0x22,0x20,0x42,0x20,0x44,0x20,0x84,0x20,0x08,0x20,"屏", /* 52 */ 
  },
  {
    0x04,0x40,0x7F,0xFC,0x04,0x40,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0x1F,0xF0,
    0x04,0x00,0xFF,0xFE,0x11,0x10,0x3F,0xF8,0xD1,0x16,0x11,0x50,0x11,0x20,0x01,0x00,"幕", /* 53 */ 
  },
  {
    0x20,0x80,0x10,0x80,0x10,0xFE,0x01,0x00,0xFE,0x00,0x21,0xFC,0x20,0x24,0x3C,0x24,
    0x24,0xA0,0x24,0xA0,0x24,0xBC,0x24,0xA0,0x24,0xA0,0x45,0x60,0x55,0x3E,0x8A,0x00,"旋", /* 54 */ 
  },
  {
    0x20,0x20,0x20,0x20,0x20,0x20,0xFD,0xFC,0x40,0x20,0x50,0x40,0x93,0xFE,0xFC,0x40,
    0x10,0x80,0x11,0xFC,0x1C,0x04,0xF0,0x88,0x50,0x50,0x10,0x20,0x10,0x10,0x10,0x10,"转", /* 55 */ 
  },
  {
    0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0xFF,0xFE,0x00,0x40,0x00,0x40,0x00,0x40,
    0x10,0x40,0x08,0x40,0x08,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x01,0x40,0x00,0x80,"寸", /* 56 */ 
  },
  {
    0x00,0x20,0x20,0x20,0x11,0xFC,0x10,0x20,0x00,0x20,0x03,0xFE,0xF0,0x02,0x10,0x94,
    0x10,0x50,0x11,0x10,0x10,0x90,0x13,0xFE,0x14,0x28,0x18,0x44,0x10,0x82,0x03,0x02,"读", /* 57 */ 
  },
  {
    0x04,0x00,0x0E,0x00,0x78,0x00,0x08,0x7C,0x08,0x44,0xFF,0x44,0x08,0x44,0x18,0x44,
    0x1C,0x44,0x2A,0x44,0x2A,0x44,0x48,0x44,0x88,0x7C,0x08,0x44,0x08,0x00,0x08,0x00,"和", /* 58 */ 
  },
  {
    0x10,0x00,0x08,0xFE,0x7F,0x10,0x22,0x20,0x14,0x7C,0x7F,0x44,0x44,0x54,0x48,0x54,
    0x52,0x54,0x44,0x54,0x48,0x54,0x51,0x54,0x42,0x28,0x44,0x24,0x88,0x42,0x30,0x82,"颜", /* 59 */ 
  },
  {
    0x08,0x40,0x08,0x40,0x0F,0xFC,0x10,0x40,0x10,0x40,0x33,0xF8,0x32,0x08,0x53,0xF8,
    0x92,0x08,0x13,0xF8,0x12,0x08,0x13,0xF8,0x12,0x08,0x12,0x08,0x1F,0xFE,0x10,0x00,"值", /* 60 */ 
  },
};

//字体取模：黑体18
//宽度高度：24*24
//扫描模式：水平扫描，从左到右，从上到下（低位在前）
//数据格式：C表格(格式2)
typedef struct 
{
    unsigned char dat[72];
    char txt[2];
}typFNT_GB24; 
typFNT_GB24 code tfont24[]=
{
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x0C,0xFF,0xFC,0x06,0xC0,0x0C,0x00,
    0xC0,0x0C,0x00,0xC8,0xCC,0x00,0x18,0x60,0x70,0x30,0x30,0x38,0x60,0x18,0x0C,0xC3,
    0x10,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0xFF,0xFE,0x04,0x0F,0x80,0x06,0x1B,0xC0,
    0x0C,0x1B,0xC0,0x0C,0x33,0x60,0x18,0x73,0x30,0x18,0xE3,0x18,0x39,0xC3,0x0C,0x31,
    0x83,0x04,0x10,0x03,0x00,0x00,0x00,0x00,"深", /* 0 */ 
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x30,0x0C,0x0C,0x30,0x0C,0x0C,0x31,0x88,0x0C,
    0x31,0x88,0x0C,0x31,0x88,0x0C,0x31,0x88,0x7F,0xB1,0x88,0x0C,0x31,0x88,0x0C,0x31,
    0x88,0x0C,0x31,0x88,0x0C,0x31,0x88,0x0C,0x31,0x88,0x0C,0x31,0x88,0x0C,0x31,0x88,
    0x0F,0x31,0x88,0x7C,0x61,0x88,0x60,0x61,0x88,0x00,0x61,0x88,0x00,0xC0,0x08,0x01,
    0x80,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,"圳", /* 1 */ 
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xFC,0x3F,0xFF,0xFC,0x30,0x00,0x0C,0x30,
    0x00,0x0C,0x33,0xFF,0xCC,0x33,0xFF,0xCC,0x30,0x18,0x0C,0x30,0x18,0x0C,0x30,0x18,
    0x0C,0x31,0xFF,0x8C,0x30,0x18,0x0C,0x30,0x19,0x0C,0x30,0x1B,0x8C,0x30,0x19,0x0C,
    0x30,0x18,0x0C,0x33,0xFF,0xCC,0x30,0x00,0x0C,0x30,0x00,0x0C,0x30,0x00,0x0C,0x3F,
    0xFF,0xFC,0x30,0x00,0x0C,0x00,0x00,0x00,"国", /* 2 */ 
  },
  {
    0x00,0x00,0x00,0x00,0x01,0x80,0x01,0x81,0x80,0x01,0x81,0x80,0x41,0x81,0x80,0x7F,
    0xFF,0xFE,0x01,0x81,0x80,0x01,0x81,0x80,0x01,0x81,0x80,0x01,0x80,0x00,0x00,0x18,
    0x00,0x00,0x1C,0x00,0x11,0x8C,0x20,0x19,0x8E,0x30,0x19,0x86,0x38,0x19,0x80,0x18,
    0x19,0x80,0x0C,0x31,0x80,0x0E,0x31,0x80,0x00,0x31,0x80,0x60,0x01,0x80,0xC0,0x01,
    0xFF,0xC0,0x00,0x3F,0x00,0x00,0x00,0x00,"芯", /* 3 */ 
  },
  {
    0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,
    0x18,0x00,0x1F,0xFF,0xF8,0x1F,0xFF,0xF8,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0xFF,0xF8,0x1F,0xFF,0xF8,0x18,0x18,0x18,
    0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x00,
    0x18,0x00,0x00,0x18,0x00,0x00,0x00,0x00,"中", /* 4 */ 
  },
  {
    0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x60,0x00,0x00,0x30,0x00,0x00,0x38,0x00,0x00,
    0x18,0x00,0x7F,0xFF,0xFE,0x7F,0xFF,0xFE,0x03,0x01,0x80,0x03,0x01,0x80,0x03,0x01,
    0x80,0x01,0x01,0x80,0x01,0x83,0x00,0x01,0x83,0x00,0x00,0xC6,0x00,0x00,0x6E,0x00,
    0x00,0x7C,0x00,0x00,0x38,0x00,0x00,0x7C,0x00,0x00,0xE7,0x00,0x03,0x83,0xE0,0x3F,
    0x00,0xFE,0x3C,0x00,0x3C,0x00,0x00,0x00,"文", /* 5 */ 
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x0C,0x39,0xFE,0x0C,0x1D,0xFE,0x0C,0x01,
    0x86,0x6C,0x01,0x86,0x4C,0x01,0xB6,0x4C,0x21,0xB6,0x4C,0x31,0xB6,0x4C,0x1D,0xB6,
    0x4C,0x09,0xB6,0x4C,0x01,0xB6,0x4C,0x01,0xB6,0x4C,0x0D,0xB6,0x4C,0x0D,0xB6,0x4C,
    0x08,0x20,0x6C,0x18,0x68,0x6C,0x30,0x7C,0x0C,0x30,0xCE,0x0C,0x70,0xC6,0x0C,0x61,
    0x83,0x3C,0x01,0x02,0x38,0x00,0x00,0x00,"测", /* 6 */ 
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x01,0xB0,0x38,0x01,0x98,0x18,0x01,0x9C,0x0C,
    0x01,0x88,0x00,0x01,0x80,0x01,0xFF,0xFC,0x00,0x01,0x80,0x7C,0x01,0x80,0x7C,0x01,
    0x80,0x0C,0xFD,0x80,0x0C,0xFD,0x80,0x0C,0x30,0x80,0x0C,0x30,0xC0,0x0C,0x30,0xC0,
    0x0C,0x30,0xC0,0x0D,0xB0,0xC0,0x0F,0x36,0x64,0x0E,0x3E,0x66,0x1C,0xF0,0x36,0x08,
    0x80,0x3C,0x00,0x00,0x1C,0x00,0x00,0x00,"试", /* 7 */ 
  },
};  

//字体取模：楷体24
//宽度高度：32*32
//扫描模式：水平扫描，从左到右，从上到下（低位在前）
//数据格式：C表格(格式2)
typedef struct 
{
    unsigned char dat[128];
    char txt[2];
}typFNT_GB32;
typFNT_GB32 code tfont32[]=
{
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,
    0x00,0x01,0xC0,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x1F,0x80,0x00,0x83,0xF1,0xC0,
    0x01,0xFC,0x01,0xE0,0x01,0x80,0x03,0xC0,0x03,0x80,0x02,0x00,0x03,0x01,0xF0,0x00,
    0x03,0x3E,0x38,0x00,0x00,0x18,0x70,0x00,0x00,0x00,0x60,0x00,0x00,0x01,0xC0,0x00,
    0x00,0x01,0x80,0xF0,0x00,0x00,0xFF,0xF8,0x00,0x7F,0xF8,0x00,0x1F,0xF0,0xC0,0x00,
    0x0C,0x00,0x40,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x60,0x00,
    0x00,0x00,0x60,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0xE0,0x00,0x00,0x18,0xC0,0x00,
    0x00,0x07,0xC0,0x00,0x00,0x03,0xC0,0x00,0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x00,"字", /* 0 */ 
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,
    0x00,0x60,0x70,0x00,0x00,0x70,0x30,0x00,0x00,0x60,0x30,0x00,0x00,0xE0,0x20,0x00,
    0x00,0xC0,0x20,0x00,0x00,0xC0,0x21,0xC0,0x01,0x80,0x3F,0xE0,0x01,0x07,0xFC,0x00,
    0x03,0x0F,0x70,0x00,0x06,0x80,0xE8,0x00,0x04,0x80,0xE8,0x00,0x0C,0x81,0xA4,0x00,
    0x18,0x81,0x22,0x00,0x20,0x83,0x23,0x00,0x40,0x86,0x21,0x80,0x00,0x84,0x21,0xC0,
    0x00,0x88,0x2C,0xE0,0x00,0x90,0xFE,0x78,0x01,0xA1,0xE0,0x3E,0x01,0xC0,0x20,0x00,
    0x01,0x80,0x20,0x00,0x01,0x80,0x20,0x00,0x01,0x80,0x60,0x00,0x01,0x00,0x60,0x00,
    0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"体", /* 1 */ 
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,
    0x00,0x00,0x00,0x30,0x00,0x00,0xC0,0x30,0x03,0x17,0xE0,0x30,0x03,0x98,0x60,0x30,
    0x01,0x90,0x60,0x30,0x00,0x12,0x64,0x30,0x00,0x13,0x66,0x30,0x00,0x13,0x66,0x30,
    0x18,0x13,0x62,0x30,0x0C,0x12,0x62,0x30,0x0C,0x92,0x62,0x30,0x01,0x12,0x62,0x30,
    0x01,0x12,0x62,0x30,0x02,0x32,0x66,0x30,0x02,0x36,0x66,0x30,0x06,0x16,0x42,0x30,
    0x0C,0x07,0x40,0x30,0x1C,0x04,0xC0,0x30,0x1C,0x0C,0xE0,0x30,0x18,0x18,0x70,0x30,
    0x08,0x30,0x30,0x30,0x00,0x40,0x01,0xF0,0x01,0x80,0x00,0xF0,0x00,0x00,0x00,0x60,
    0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"测", /* 2 */ 
  },
  {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,
    0x00,0x00,0x70,0x00,0x01,0xC0,0x70,0x00,0x00,0xF0,0x33,0xC0,0x00,0x70,0x31,0xC0,
    0x00,0x00,0x30,0xC0,0x00,0x00,0x30,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x10,0x00,
    0x00,0x00,0x1F,0x00,0x01,0xC0,0xFC,0x00,0x0F,0xC7,0x98,0x00,0x39,0x80,0x08,0x00,
    0x01,0x80,0x08,0x00,0x01,0x80,0x6C,0x00,0x01,0x83,0xC4,0x00,0x01,0x87,0x84,0x00,
    0x01,0x81,0x86,0x00,0x01,0x01,0x82,0x00,0x01,0x11,0x93,0x04,0x03,0xE1,0xE1,0x84,
    0x03,0xCF,0x01,0x84,0x07,0x1C,0x00,0xCC,0x02,0x00,0x00,0x7C,0x00,0x00,0x00,0x3C,
    0x00,0x00,0x00,0x1C,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"试", /* 3 */ 
  },
};
  
#endif
