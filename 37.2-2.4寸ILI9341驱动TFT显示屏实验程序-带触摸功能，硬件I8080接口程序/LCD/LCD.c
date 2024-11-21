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
//================================================================================================//
//不使用触摸或者模块本身不带触摸，则可不连接
//触摸屏使用的数据总线类型为SPI
//  T_CS         接        P15          //触摸屏片选控制信号
//  T_CLK        接        P32          //触摸屏SPI时钟信号
//  T_DO         接        P33          //触摸屏SPI读信号
//  T_DIN        接        P34          //触摸屏SPI写信号
//  T_IRQ        接        P14          //触摸屏响应检查信号
//================================================================================================//
// 本实验使用的2.4寸320*240的并口彩屏，由冲哥淘宝店提供：http://e.tb.cn/h.gIlbVqAOj8YXlwo?tk=vFIr3RGTy2n
//**************************************************************************************************/

#include "sys.h"
#include "lcd.h"

//LCD的画笔颜色和背景色       
u16 POINT_COLOR=0x0000;    //画笔颜色
u16 BACK_COLOR=0xFFFF;  //背景色 
//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

/*****************************************************************************
 * @name       :void LCM_Config(void)
 * @date       :2018-11-13 
 * @function   :Config LCM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCM_Config(void)
{
	LCMIFCFG = 0x00;	//bit7 1:Enable Interrupt, bit1 0:8bit mode; bit0 0:8080,1:6800
	LCMIFCFG2 = 0x25;	//RS:P45,E:P37,RW:P36; Setup Time=1,HOLD Time=1
	LCMIFSTA = 0x00;
	EA = 1;
}

/*****************************************************************************
 * @name       :void LCM_Interrupt(void)
 * @date       :2018-11-13 
 * @function   :None
 * @parameters :None
 * @retvalue   :
******************************************************************************/ 
void LCM_Interrupt(void) interrupt 13
{
	LCMIFSTA = 0x00;
	LCD_CS=1;
}

/*****************************************************************************
 * @name       :void LCD_WR_REG(u16 Reg)    
 * @date       :2018-08-09 
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :data:Command value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_REG(u16 Reg)     
{
	LCMIFDATL = Reg;
	LCD_CS=0;
	LCMIFCR = 0x84;		//Enable interface, write command out
    while(!LCMIFSTA);
    LCMIFSTA = 0x00;
    LCD_CS=1;
} 

/*****************************************************************************
 * @name       :void LCD_WR_DATA(u16 Data)
 * @date       :2018-08-09 
 * @function   :Write an 16-bit data to the LCD screen
 * @parameters :data:data value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_DATA(u16 Data)
{
	LCMIFDATL = Data;
	LCD_CS=0;
	LCMIFCR = 0x85;		//Enable interface, write data out
    while(!LCMIFSTA);
    LCMIFSTA = 0x00;
    LCD_CS=1;
}

/*****************************************************************************
 * @name       :u16 LCD_RD_DATA(void)
 * @date       :2018-11-13 
 * @function   :Read an 16-bit value from the LCD screen
 * @parameters :None
 * @retvalue   :read value
******************************************************************************/
u16 LCD_RD_DATA(void)
{
    u16 d;
    //LCM Read
    LCD_CS = 0;
    LCMIFCR = 0x87;		//Enable interface, Read data
    while(!LCMIFSTA);
    LCMIFSTA = 0x00;
    LCD_CS=1;
	d = LCMIFDATL;

    return (d);
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA_16Bit(u16 Data)
 * @date       :2018-08-09 
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/     
void LCD_WR_DATA_16Bit(u16 Data)
{
	LCD_WR_DATA((u8)(Data>>8));
	LCD_WR_DATA((u8)Data);
}

u16 Color_To_565(u8 r, u8 g, u8 b)
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
}

/*****************************************************************************
 * @name       :u16 Lcd_ReadData_16Bit(void)
 * @date       :2018-11-13 
 * @function   :Read an 16-bit value from the LCD screen
 * @parameters :None
 * @retvalue   :read value
******************************************************************************/    
u16 Lcd_RD_DATA_16Bit(void)
{
    u16 r,g,b;

    //dummy data
    r = LCD_RD_DATA();
    //dummy data
    r = LCD_RD_DATA();
    //8bit:red data
    //16bit:red and green data
    r = LCD_RD_DATA();
    //8bit:green data
    //16bit:blue data
    g = LCD_RD_DATA();

    b = LCD_RD_DATA();

    return Color_To_565((u8)r, (u8)g, (u8)b);
}

/*****************************************************************************
 * @name       :void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
 * @date       :2018-08-09 
 * @function   :Write data into registers
 * @parameters :LCD_Reg:Register address
                LCD_RegValue:Data to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
{
    LCD_WR_REG(LCD_Reg);
    LCD_WR_DATA(LCD_RegValue);
}

/*****************************************************************************
 * @name       :u16 LCD_ReadReg(u16 LCD_Reg)
 * @date       :2018-11-13 
 * @function   :read value from specially registers
 * @parameters :LCD_Reg:Register address
 * @retvalue   :read value
******************************************************************************/
void LCD_ReadReg(u16 LCD_Reg,u8 *Rval,int n)
{
    LCD_WR_REG((u8)LCD_Reg);
    while(n--)
    {		
        *(Rval++) = LCD_RD_DATA();
    }
}

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09 
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/    
void LCD_WriteRAM_Prepare(void)
{
     LCD_WR_REG(lcddev.wramcmd);      
}

/*****************************************************************************
 * @name       :void LCD_ReadRAM_Prepare(void)
 * @date       :2018-11-13 
 * @function   :Read GRAM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/     
void LCD_ReadRAM_Prepare(void)
{
    LCD_WR_REG(lcddev.rramcmd);
}

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09 
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
******************************************************************************/    
void LCD_Clear(u16 Color)
{
    u16 i,j;
    LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);    
    for(i=0;i<lcddev.width;i++)
    {
        for (j=0;j<lcddev.height;j++)
        {
            LCD_WR_DATA_16Bit(Color);
        }
    }
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09 
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/    
void LCD_DrawPoint(u16 x,u16 y)
{
    LCD_SetWindows(x,y,x,y);//设置光标位置 
    LCD_WR_DATA_16Bit(POINT_COLOR);         
}      

/*****************************************************************************
 * @name       :u16 LCD_ReadPoint(u16 x,u16 y)
 * @date       :2018-11-13 
 * @function   :Read a pixel color value at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :the read color value
******************************************************************************/    
u16 LCD_ReadPoint(u16 x,u16 y)
{
    u16 color;
    if(x>=lcddev.width||y>=lcddev.height)
    {
        return 0;	//超过了范围,直接返回	
    }
    LCD_SetCursor(x,y);//设置光标位置 
    LCD_ReadRAM_Prepare();
    color = Lcd_RD_DATA_16Bit();
    return color;
}

/*****************************************************************************
 * @name       :void LCD_Set_GPIO(void)
 * @date       :2018-11-13 
 * @function   :Set the gpio to push-pull mode
 * @parameters :None
 * @retvalue   :None
******************************************************************************/    
void LCD_Set_GPIO(void)
{
    //P2口设置成准双向口
    P2M0=0x00;
    P2M1=0x00;

    //P0.4口设置成高阻输入,P0.5推挽输出
    P0M0=0x20;
    P0M1=0x10;

    //P1.4口设置成高阻输入
    P1M0=0x00;
    P1M1=0x10;

//    //P6口设置成高阻输入(8bit)
//    P6M0=0x00;
//    P6M1=0xff;

    //P3.3口设置成高阻输入
    //P3.7,P3.6,P3.4,P3.2口设置成推挽输出
    P3M0=0xd4;
    P3M1=0x08;

    //P4.7,P4.5口设置成推挽输出
    P4M0=0xa0;
    P4M1=0x00;

    //P5.3口设置成推挽输出
    P5M0=0x08;
    P5M1=0x00;
}

/*****************************************************************************
 * @name       :void LCDReset(void)
 * @date       :2018-08-09 
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/    
void LCDReset(void)
{
    delay_ms(50);    
    LCD_RESET=0;
    delay_ms(50);
    LCD_RESET=1;
    delay_ms(50);
}

/*****************************************************************************
 * @name       :void LCD_Init(void)
 * @date       :2018-08-09 
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/          
void LCD_Init(void)
{
    LCD_Set_GPIO();
    LCM_Config();
    LCDReset(); //初始化之前复位
//*************2.4inch ILI9341初始化**********//
    LCD_WR_REG(0xCF);  
    LCD_WR_DATA(0x00); 
    LCD_WR_DATA(0xD9); //0xC1 
    LCD_WR_DATA(0X30); 
    LCD_WR_REG(0xED);  
    LCD_WR_DATA(0x64); 
    LCD_WR_DATA(0x03); 
    LCD_WR_DATA(0X12); 
    LCD_WR_DATA(0X81); 
    LCD_WR_REG(0xE8);  
    LCD_WR_DATA(0x85); 
    LCD_WR_DATA(0x10); 
    LCD_WR_DATA(0x7A); 
    LCD_WR_REG(0xCB);  
    LCD_WR_DATA(0x39); 
    LCD_WR_DATA(0x2C); 
    LCD_WR_DATA(0x00); 
    LCD_WR_DATA(0x34); 
    LCD_WR_DATA(0x02); 
    LCD_WR_REG(0xF7);  
    LCD_WR_DATA(0x20); 
    LCD_WR_REG(0xEA);  
    LCD_WR_DATA(0x00); 
    LCD_WR_DATA(0x00); 
    LCD_WR_REG(0xC0);    //Power control 
    LCD_WR_DATA(0x1B);   //VRH[5:0] 
    LCD_WR_REG(0xC1);    //Power control 
    LCD_WR_DATA(0x12);   //SAP[2:0];BT[3:0] 0x01
    LCD_WR_REG(0xC5);    //VCM control 
    LCD_WR_DATA(0x08);      //30
    LCD_WR_DATA(0x26);      //30
    LCD_WR_REG(0xC7);    //VCM control2 
    LCD_WR_DATA(0XB7); 
    LCD_WR_REG(0x36);    // Memory Access Control 
    LCD_WR_DATA(0x08);
    LCD_WR_REG(0x3A);   
    LCD_WR_DATA(0x55); 
    LCD_WR_REG(0xB1);   
    LCD_WR_DATA(0x00);   
    LCD_WR_DATA(0x1A); 
    LCD_WR_REG(0xB6);    // Display Function Control 
    LCD_WR_DATA(0x0A); 
    LCD_WR_DATA(0xA2); 
    LCD_WR_REG(0xF2);    // 3Gamma Function Disable 
    LCD_WR_DATA(0x00); 
    LCD_WR_REG(0x26);    //Gamma curve selected 
    LCD_WR_DATA(0x01); 
    LCD_WR_REG(0xE0);    //Set Gamma 
    LCD_WR_DATA(0x0F); 
    LCD_WR_DATA(0x1D); 
    LCD_WR_DATA(0x1A); 
    LCD_WR_DATA(0x0A); 
    LCD_WR_DATA(0x0D); 
    LCD_WR_DATA(0x07); 
    LCD_WR_DATA(0x49); 
    LCD_WR_DATA(0X66); 
    LCD_WR_DATA(0x3B); 
    LCD_WR_DATA(0x07); 
    LCD_WR_DATA(0x11); 
    LCD_WR_DATA(0x01); 
    LCD_WR_DATA(0x09); 
    LCD_WR_DATA(0x05); 
    LCD_WR_DATA(0x04);          
    LCD_WR_REG(0XE1);    //Set Gamma 
    LCD_WR_DATA(0x00); 
    LCD_WR_DATA(0x18); 
    LCD_WR_DATA(0x1D); 
    LCD_WR_DATA(0x02); 
    LCD_WR_DATA(0x0F); 
    LCD_WR_DATA(0x04); 
    LCD_WR_DATA(0x36); 
    LCD_WR_DATA(0x13); 
    LCD_WR_DATA(0x4C); 
    LCD_WR_DATA(0x07); 
    LCD_WR_DATA(0x13); 
    LCD_WR_DATA(0x0F); 
    LCD_WR_DATA(0x2E); 
    LCD_WR_DATA(0x2F); 
    LCD_WR_DATA(0x05); 
    LCD_WR_REG(0x2B); 
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x01);
    LCD_WR_DATA(0x3f);
    LCD_WR_REG(0x2A); 
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0xef);     
    LCD_WR_REG(0x11); //Exit Sleep
    delay_ms(120);
    LCD_WR_REG(0x29); //display on    

    //设置LCD属性参数
    LCD_direction(USE_HORIZONTAL);//设置LCD显示方向 
//    LCD_BL=1;//点亮背光     
}

/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09 
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
                                yStar:the bebinning y coordinate of the LCD display window
                                xEnd:the endning x coordinate of the LCD display window
                                yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{
    LCD_WR_REG(lcddev.setxcmd);    
    LCD_WR_DATA(xStar>>8);
    LCD_WR_DATA(0x00FF&xStar);        
    LCD_WR_DATA(xEnd>>8);
    LCD_WR_DATA(0x00FF&xEnd);

    LCD_WR_REG(lcddev.setycmd);    
    LCD_WR_DATA(yStar>>8);
    LCD_WR_DATA(0x00FF&yStar);        
    LCD_WR_DATA(yEnd>>8);
    LCD_WR_DATA(0x00FF&yEnd);    

    LCD_WriteRAM_Prepare();    //开始写入GRAM
}

/*****************************************************************************
 * @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * @date       :2018-08-09 
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
                                Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
    LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);    
}

/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09 
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
                                                    2-180 degree
                                                    3-270 degree
 * @retvalue   :None
******************************************************************************/ 
void LCD_direction(u8 direction)
{
    lcddev.setxcmd=0x2A;
    lcddev.setycmd=0x2B;
    lcddev.wramcmd=0x2C;
    lcddev.rramcmd=0x2E;
    switch(direction){
        case 0:
            lcddev.width=LCD_W;
            lcddev.height=LCD_H;
            LCD_WriteReg(0x36,(1<<3));
        break;
        case 1:
            lcddev.width=LCD_H;
            lcddev.height=LCD_W;
            LCD_WriteReg(0x36,(1<<3)|(1<<5)|(1<<6));
        break;
        case 2:
            lcddev.width=LCD_W;
            lcddev.height=LCD_H;    
            LCD_WriteReg(0x36,(1<<3)|(1<<4)|(1<<6)|(1<<7));
        break;
        case 3:
            lcddev.width=LCD_H;
            lcddev.height=LCD_W;
            LCD_WriteReg(0x36,(1<<3)|(1<<7)|(1<<5)|(1<<4));
        break;
        default:break;
    }
}

/*****************************************************************************
 * @name       :u16 LCD_Read_ID(void)
 * @date       :2018-11-13 
 * @function   :Read ID
 * @parameters :None
 * @retvalue   :ID value
******************************************************************************/ 
u16 LCD_Read_ID(void)
{
    u8 val[5] = {0};
    LCD_ReadReg(0xD3,val,5);
    return (val[3]<<8)|val[4];
}
