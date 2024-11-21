/********************
点阵：128x64
取模方式：垂直扫描，从左到右，从上到下，高位在前。
#define IMG_WIDTH       128
#define IMG_HEIGHT      64
#define IMG_DEPTH       1
*********************/

    //128*64点阵图形数据
u8 const gImage_picture2[1024] =
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x02,0xFE,
    0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,
    0x00,0x00,0xFE,0x02,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x02,
    0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,
    0x40,0x40,0x40,0x40,0xC0,0x40,0x40,0x40,0x40,0x40,0x40,0xC0,0x00,0x00,0x00,0x00,
    0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xC0,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0x00,
    0x00,0xFE,0xFE,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x07,0x06,0x06,0x06,0x06,0x07,
    0x06,0x06,0x06,0x06,0x06,0x06,0x07,0x06,0x06,0x06,0x06,0x07,0x06,0x06,0x06,0x06,
    0x06,0x06,0x07,0x06,0x06,0x06,0x06,0x07,0x06,0x06,0x06,0x06,0x06,0x06,0x07,0x06,
    0x06,0x06,0x06,0x07,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0xFE,0xFE,0x00,0x00,0xFF,
    0x40,0x48,0x44,0x26,0xAB,0x92,0x2A,0x26,0x42,0x40,0x40,0xFF,0x00,0x00,0x00,0x00,
    0x00,0xFF,0x44,0x44,0x44,0x44,0x44,0x47,0xC4,0x04,0x04,0x04,0x00,0x00,0x00,0x40,
    0x80,0x1F,0x12,0xF2,0x12,0x12,0x12,0xF2,0x12,0x1F,0x00,0xC0,0x00,0x00,0x00,0x04,
    0x04,0x84,0x64,0x04,0x04,0x04,0xFC,0x04,0x04,0x04,0x24,0x44,0x84,0x04,0x00,0x00,
    0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x1F,
    0x08,0x08,0x08,0x0A,0x0A,0x0C,0x0D,0x08,0x08,0x08,0x08,0x1F,0x00,0x00,0x00,0x10,
    0x0C,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x08,0x08,
    0x08,0x0B,0x08,0x0F,0x08,0x08,0x08,0x0F,0x08,0x0A,0x09,0x08,0x08,0x00,0x00,0x02,
    0x01,0x00,0x00,0x00,0x04,0x08,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,
    0x00,0xFF,0xFF,0x00,0xC0,0xE0,0x30,0x30,0xE0,0xC0,0x00,0x00,0x00,0x10,0xF0,0xF0,
    0x10,0x00,0x00,0x00,0xE0,0xF0,0x90,0x10,0xF0,0xE0,0x00,0x00,0x00,0xE0,0xF0,0x10,
    0xD0,0xF0,0xE0,0x00,0xF0,0xF0,0x10,0x10,0x10,0x10,0x00,0x00,0x40,0x40,0x60,0xF0,
    0xF0,0x00,0x00,0x00,0xF0,0xF0,0x00,0x00,0xF0,0xF0,0x00,0xFF,0xFF,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0xC0,0xC0,0x80,0x80,
    0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0xE0,0xE0,0xE0,0xE0,0xE0,0xC0,
    0xC0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xFF,0xFF,0x00,0x1F,0x1F,0x02,0x02,0x1F,0x1F,0x00,0x00,0x00,0x10,0x1F,0x1F,
    0x10,0x00,0x00,0x00,0x0E,0x1F,0x11,0x13,0x1F,0x0E,0x00,0x00,0x00,0x0F,0x1F,0x16,
    0x10,0x1F,0x0F,0x00,0x11,0x11,0x11,0x19,0x0F,0x06,0x00,0x00,0x00,0x00,0x00,0x1F,
    0x1F,0x00,0x00,0x00,0x0F,0x1F,0x10,0x10,0x1F,0x0F,0x00,0xFF,0xFF,0x00,0x00,0x00,
    0x00,0xC0,0xF0,0x78,0x1C,0x0E,0x07,0x03,0x03,0x01,0x01,0xFD,0xFD,0x01,0x01,0x01,
    0x03,0x03,0x07,0x0E,0x1C,0x78,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xC0,0xF0,0xFC,0xFE,0xFF,0x3F,0x3F,0x3F,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,
    0x3F,0x3F,0x3F,0xFF,0xFE,0xFC,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,
    0x1E,0x7F,0xFF,0xDE,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x0C,0x0C,0x0C,
    0x0C,0x0C,0x00,0x00,0x0C,0xDE,0xFF,0x7F,0x1E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0x9F,0x1F,0x1F,0x1F,0x1F,0x1F,0x9F,
    0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
    0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
    0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
    0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xFF,0xFF,0x00,0x00,0x00,
    0x00,0x00,0x01,0x03,0x07,0x0E,0x1C,0x18,0x38,0x30,0x78,0x7C,0x7C,0x78,0x30,0x30,
    0x38,0x18,0x1C,0x0E,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x1F,0x1F,0x3F,0x3E,0x3E,0x3E,0x3F,0x1F,
    0x1F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x80,0x80,0x80,0x80,0xFF,
    0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x80,0x80,0x80,0x80,0xFF,0x00,0x00,0x00,0x00,
    0x00,0x00,0xFF,0x80,0x80,0x80,0x80,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x80,
    0x80,0x80,0x80,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

