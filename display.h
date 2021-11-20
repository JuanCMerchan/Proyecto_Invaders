#pragma once

#include <stdio.h>
#include <string.h>

#define BRAILLE0 '\u2800'
#define BRAILLE1 '\u2840'
#define BRAILLE2 '\u2880'
#define BRAILLE3 '\u28c0'
#define DISP_HEIGHT 192
#define DISP_WIDTH 192

class Display
{
private:
    unsigned char frame[DISP_HEIGHT][DISP_WIDTH];
    void cleanFrame();
    static void clearScreen();
    char brailleFrame[DISP_HEIGHT / 4][DISP_WIDTH / 2][4];

public:
    Display();
    void byteToBraille(char destination[4], unsigned char byte);
    void print();
    void setFrame(unsigned char frame[DISP_HEIGHT][DISP_WIDTH]);
    unsigned char stringByteToChar(unsigned char stringByte[8]);
};