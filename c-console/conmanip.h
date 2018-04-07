#ifndef CONMANIP_H
#define CONMANIP_H

#include <conio.h>

#include <stdbool.h>

enum
{
    //ASCII control
    ASCII_NUL = 0x00,
    ASCII_BEL = 0x07,
    ASCII_BS  = 0x08,
    ASCII_HT  = 0x09,
    ASCII_LF  = 0x0a,
    ASCII_VT  = 0x0b,
    ASCII_FF  = 0x0c,
    ASCII_CR  = 0x0d,
    ASCII_CAN = 0x18,
    ASCII_ESC = 0x1b,
    ASCII_DEL = 0x7f
};

typedef enum  
{
    Black = 0x0,
    Blue = 0x1,
    Green = 0x2,
    Aqua = 0x3,
    Red = 0x4,
    Purple = 0x5,
    Yellow = 0x6,
    White = 0x7,
    Gray = 0x8,
    LightBlue = 0x9,
    LightGreen = 0xa,
    LightAqua = 0xb,
    LightRed = 0xc,
    LightPurple = 0xd,
    LightYellow = 0xe,
    BrightWhite = 0xf
} ConColor;

extern void clearScreen(void);
extern bool setColor(ConColor foreground, ConColor background);
extern bool setForeground(ConColor color);
extern bool setBackground(ConColor color);
extern ConColor foreground(void);
extern ConColor background(void);

#endif //CONMANIP_H