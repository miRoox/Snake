#ifndef CONMANIP_H
#define CONMANIP_H

#include <conio.h>

#include <stdbool.h>

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