/*---------------------------------------------------------------------*/
/* --- Web: www.STCAI.com ---------------------------------------------*/
/*---------------------------------------------------------------------*/

#include "adc.h"

/*************** 功能说明 ****************

查询法读一次ADC结果.

******************************************/


//========================================================================
// 函数: u16 Get_ADC12bitResult(u8 channel)
// 描述: 查询法读一次ADC结果.
// 参数: channel: 选择要转换的ADC.
// 返回: 12位ADC结果.
// 版本: V1.0, 2012-10-22
//========================================================================
u16 Get_ADC12bitResult(u8 channel)  //channel = 0~15
{
    ADC_RES = 0;
    ADC_RESL = 0;

    ADC_CONTR = (ADC_CONTR & 0xf0) | channel; //设置ADC转换通道
    ADC_START = 1;//启动ADC转换
    _nop_();
    _nop_();
    _nop_();
    _nop_();

    while(ADC_FLAG == 0);   //wait for ADC finish
    ADC_FLAG = 0;     //清除ADC结束标志
    return  (((u16)ADC_RES << 8) | ADC_RESL);
}

