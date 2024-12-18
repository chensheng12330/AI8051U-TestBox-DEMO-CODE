#ifndef __USB_REQ_CLASS_H__
#define __USB_REQ_CLASS_H__

#define SET_LINE_CODING         0x20
#define GET_LINE_CODING         0x21
#define SET_CONTROL_LINE_STATE  0x22

#define NONE_PARITY             0
#define ODD_PARITY              1
#define EVEN_PARITY             2
#define MARK_PARITY             3
#define SPACE_PARITY            4

void usb_req_class();
void usb_uart_settings();

void usb_set_line_coding();
void usb_get_line_coding();
void usb_set_ctrl_line_state();

typedef struct
{
    DWORD   dwDTERate;
    BYTE    bCharFormat;
    BYTE    bParityType;
    BYTE    bDataBits;
}LINECODING;

extern LINECODING LineCoding1;
extern LINECODING LineCoding2;


#endif
