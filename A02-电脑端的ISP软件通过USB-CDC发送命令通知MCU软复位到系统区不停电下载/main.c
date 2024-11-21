/*---------------------------------------------------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/*---------------------------------------------------------------------*/

/*************  功能说明    **************

本例程基于AI8051U为主控芯片的实验箱进行编写测试.

使用Keil C251编译器，Memory Model推荐设置XSmall模式，默认定义变量在edata，单时钟存取访问速度快。

edata建议保留1K给堆栈使用，空间不够时可将大数组、不常用变量加xdata关键字定义到xdata空间。

程序使用P0口来演示跑马灯，输出低驱动。

使用USB线连接电脑跟MCU。
通过加载“usb_cdc_32.lib”库函数，实现使用AIapp-ISP软件烧录时发送命令"@STCISP#"，MCU收到命令后执行软复位操作，进入USB下载模式并自动下载。
（软件复位进入ISP会重新置位RSTFLAG，系统ISP程序不用判断P3.2电平进入USB下载模式）

下载时, 选择时钟 24MHz (用户可自行修改频率).

******************************************/

#include "../comm/AI8051U.h"
#include "../comm/usb.h"     //USB调试及复位所需头文件

//==========================================================================


/*************  本地常量声明    **************/

#define MAIN_Fosc       24000000L   //定义主时钟

/*************  IO口定义    **************/


/*************  本地变量声明    **************/

//USB调试及复位所需定义
char *USER_DEVICEDESC = NULL;
char *USER_PRODUCTDESC = NULL;
char *USER_STCISPCMD = "@STCISP#";  //设置自动复位到ISP区的用户接口命令

/*************  本地函数声明    **************/

void delay_ms(u8 ms);

/****************  外部函数声明和外部变量声明 *****************/


/******************** 主函数 **************************/
void main(void)
{
    WTST = 0;   //设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
    EAXFR = 1;  //扩展寄存器(XFR)访问使能
    CKCON = 0;  //提高访问XRAM速度

    RSTFLAG |= 0x04;   //软复位标志写1清零，设置硬件复位后需要检测P3.2的状态选择运行区域，硬件复位后进入系统ISP检测到P3.2为低电平，才会进入USB下载模式

    P0M1 = 0x00;   P0M0 = 0xff;   //设置为推挽输出
    P1M1 = 0x00;   P1M0 = 0x00;   //设置为准双向口
    P2M1 = 0x00;   P2M0 = 0x00;   //设置为准双向口
    P3M1 = 0x00;   P3M0 = 0x00;   //设置为准双向口
    P4M1 = 0x00;   P4M0 = 0x00;   //设置为准双向口
    P5M1 = 0x00;   P5M0 = 0x00;   //设置为准双向口
    P6M1 = 0x00;   P6M0 = 0x00;   //设置为准双向口
    P7M1 = 0x00;   P7M0 = 0x00;   //设置为准双向口

    usb_init();
    EUSB = 1;       //IE2相关的中断位操作使能后，需要重新设置EUSB
    EA = 1;
    P40 = 0;        //LED Power On

    while(1)
    {
        P00 = 0;        //LED On
        delay_ms(250);
        P00 = 1;        //LED Off

        P01 = 0;        //LED On
        delay_ms(250);
        P01 = 1;        //LED Off

        P02 = 0;        //LED On
        delay_ms(250);
        P02 = 1;        //LED Off

        P03 = 0;        //LED On
        delay_ms(250);
        P03 = 1;        //LED Off

        P04 = 0;        //LED On
        delay_ms(250);
        P04 = 1;        //LED Off

        P05 = 0;        //LED On
        delay_ms(250);
        P05 = 1;        //LED Off

        P06 = 0;        //LED On
        delay_ms(250);
        P06 = 1;        //LED Off

        P07 = 0;        //LED On
        delay_ms(250);
        P07 = 1;        //LED Off
    }
}

//========================================================================
// 函数: void delay_ms(u8 ms)
// 描述: 延时函数。
// 参数: ms,要延时的ms数, 这里只支持1~255ms. 自动适应主时钟.
// 返回: none.
// 版本: VER1.0
// 日期: 2022-6-3
// 备注: 
//========================================================================
void delay_ms(u8 ms)
{
    u16 i;
    do{
        i = MAIN_Fosc / 6000;
        while(--i);   //6T per loop
    }while(--ms);
}
