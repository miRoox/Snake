#include "conmanip.h"
#include <stdio.h>
#include <stdlib.h>

void clearScreen(void)
{
    system("cls");
}

static const char hexDigits[] = "0123456789abcdef";
static ConColor _foreground = BrightWhite;
static ConColor _background = Black;

bool setColor(ConColor foreground, ConColor background)
{
    if(foreground == background)
        return false;
    else if(foreground == _foreground && background == _background) 
        return true;
    _foreground = foreground;
    _background = background;
    {
        char colorCmd[] = "color 0f";
        colorCmd[6] = hexDigits[(int)_background];
        colorCmd[7] = hexDigits[(int)_foreground];
        system(colorCmd);
    }
    return true;
}

bool setForeground(ConColor color)
{
    return setColor(color, _background);
}

bool setBackground(ConColor color)
{
    return setColor(_foreground, color);
}

ConColor foreground(void)
{
    return _foreground;
}

ConColor background(void)
{
    return _background;
}
