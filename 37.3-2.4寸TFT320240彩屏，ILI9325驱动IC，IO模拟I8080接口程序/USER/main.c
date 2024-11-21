/*---------------------------------------------------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/* 液晶屏驱动程序参考wiki技术网站提供的开源源码，仅供学习使用          */
/*---------------------------------------------------------------------*/

//=========================================电源接线================================================//
//VDD接DC 3.3V电源
//GND接地
//=======================================液晶屏数据线接线==========================================//
//本模块数据总线类型为8位并口
// LCD_D0~D7     接       P20~P27        //液晶屏8位数据线
//=======================================液晶屏控制线接线==========================================//
// LCD_RS        接        P45           //数据/命令选择控制信号
// LCD_RD        接        P37           //读控制信号
// LCD_RST       接        P47           //复位信号
// LCD_WR        接        P36           //写控制信号
// LCD_CS        接        P05/P53       //片选控制信号
//===========================================触摸屏接线============================================//
//不使用触摸或者模块本身不带触摸，则可不连接
//触摸屏使用的数据总线类型为SPI
//  T_CS         接        P15          //触摸屏片选控制信号
//  T_CLK        接        P32          //触摸屏SPI时钟信号
//  T_DO         接        P33          //触摸屏SPI读信号
//  T_DIN        接        P34          //触摸屏SPI写信号
//  T_IRQ        接        P14          //触摸屏响应检查信号
//================================================================================================//
#include "sys.h"
#include "lcd.h"
#include "gui.h"
#include "test.h"

//主函数
void main(void)
{ 
    WTST = 0;  //设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
    EAXFR = 1; //扩展寄存器(XFR)访问使能
    CKCON = 0; //提高访问XRAM速度

	//液晶屏初始化
	LCD_Init();

	//循环进行各项测试	
	while(1)
	{
		main_test(); 		//测试主界面
		Test_Read();     //读ID和颜色值测试
		Test_Color();  		//简单刷屏填充测试
		Test_FillRec();		//GUI矩形绘图测试
		Test_Circle(); 		//GUI画圆测试
		Test_Triangle();   //GUI三角形填充测试
		English_Font_test();//英文字体示例测试
		Chinese_Font_test();//中文字体示例测试
		Pic_test();			//图片显示示例测试
	}
}
