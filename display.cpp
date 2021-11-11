#include "display.h"

Display::Display()
{
    cleanFrame();
}

void Display::byteToBraille(char destination[4], unsigned char byte)
{
    int numBraille;
    if (byte < 64)
    {
        numBraille = BRAILLE0;
    }
    else if (byte < 128)
    {
        numBraille = BRAILLE1;
    }
    else if (byte < 196)
    {
        numBraille = BRAILLE2;
    }
    else
    {
        numBraille = BRAILLE3;
    }
    byte %= 64;
    char *charPtr;
    char temp;
    charPtr = (char *)&numBraille;
    numBraille += byte;

    temp = charPtr[0];
    charPtr[0] = charPtr[2];
    charPtr[2] = temp;
    for (int i = 0; i < 3; i++)
    {
        destination[i] = charPtr[i];
    }
    destination[4] = '\0';
}

void Display::cleanFrame()
{
    memset(frame, 0, sizeof(frame));
}

void Display::clearScreen()
{
    printf("\033[2J");
    printf("\033[H");
}

void Display::print()
{
    unsigned char stringByte[8];
    unsigned char byte;
    clearScreen();
    for (int i = 0; i < DISP_HEIGHT / 4; i++)
    {
        for (int j = 0; j < DISP_WIDTH / 2; j++)
        {
            stringByte[7] = this->frame[(i * 4) + 0][(j * 2)];
            stringByte[6] = this->frame[(i * 4) + 1][(j * 2)];
            stringByte[5] = this->frame[(i * 4) + 2][(j * 2)];
            stringByte[4] = this->frame[(i * 4) + 0][(j * 2) + 1];
            stringByte[3] = this->frame[(i * 4) + 1][(j * 2) + 1];
            stringByte[2] = this->frame[(i * 4) + 2][(j * 2) + 1];
            stringByte[1] = this->frame[(i * 4) + 3][(j * 2) + 0];
            stringByte[0] = this->frame[(i * 4) + 3][(j * 2) + 1];
            byte = stringByteToChar(stringByte);
            byteToBraille(this->brailleFrame[i][j], byte);
        }
    }
    printf(" ");
    for(int i = 0; i < DISP_WIDTH / 2; i++)
    {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < DISP_HEIGHT / 4; i++)
    {
        printf("|");
        for (int j = 0; j < DISP_WIDTH / 2; j++)
        {
            printf("%s", (char *)this->brailleFrame[i][j]);
            //fflush(stdout);
        }
        printf("|\n");
    }
    printf(" ");
    for(int i = 0; i < DISP_WIDTH / 2; i++)
    {
        printf("-");
    }
    fflush(stdout);
    cleanFrame();
}

void Display::setFrame(unsigned char frame[DISP_HEIGHT][DISP_WIDTH])
{
    for (int i = 0; i < DISP_HEIGHT; i++)
    {
        for (int j = 0; j < DISP_WIDTH; j++)
        {
            this->frame[i][j] = frame[i][j];
        }
    }
}

unsigned char Display::stringByteToChar(unsigned char stringByte[8])
{
    unsigned char result = 0;
    for (int i = 0; i < 8; i++)
    {
        result = result | stringByte[i];
        if (i != 7)
        {
            result <<= 1;
        }
    }
    return result;
}