/*---------------------------------------------------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/*---------------------------------------------------------------------*/

/*************  功能说明    **************

本例程基于AI8051U为主控芯片的实验箱进行编写测试。

使用Keil C251编译器，Memory Model推荐设置XSmall模式，默认定义变量在edata，单时钟存取访问速度快。

edata建议保留1K给堆栈使用，空间不够时可将大数组、不常用变量加xdata关键字定义到xdata空间。

HID(Human Interface Device)协议范例

示例代码名称的字符1-4为相应USB设备的VID,字符6-9为相应USB设备的PID

将代码下载到试验箱后，可使用最新的STC-ISP下载软件中的HID助手检测测试

下载时, 设置IRC工作频率为 24MHz.

******************************************/

#include "usb.h"

void main()
{
    WTST = 0;  //设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
    EAXFR = 1; //扩展寄存器(XFR)访问使能
    CKCON = 0; //提高访问XRAM速度

    usb_init();
    EA = 1;
    
    while (1);
}
