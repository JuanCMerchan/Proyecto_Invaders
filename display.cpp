#include "display.h"

Display::Display()
{
    cleanFrame();
}

/**************************************************************************
 *  Funcion: byteToBraille()
 *  Proposito: Transformar la representacion en byte de un caracter braile
 *             al codigo uncicode que representa el caracter
 *  Argumentos:
 *      destination - Arreglo de chars donde se va a guardar el codigo
 *                    del caracter braile
 *      byte - Byte que representa el caracter braile
 *  Retorno:
 *      void
 * ***********************************************************************/
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

/**************************************************************************
 *  Funcion: cleanFrame()
 *  Proposito: Limpiar la matriz frame llenandola de 0's
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Display::cleanFrame()
{
    memset(frame, 0, sizeof(frame));
}

/**************************************************************************
 *  Funcion: clearScreen()
 *  Proposito: Imprimir los caracteres ANSI para limpiar la terminal de 
 *             linux y reiniciar la posicion del cursor de texto
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Display::clearScreen()
{
    printf("\033[2J");
    printf("\033[H");
}

/**************************************************************************
 *  Funcion: gameOver()
 *  Proposito: Imprimir la pantalla de game over y el score final del
 *             jugador
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Display::gameOver()
{
    clearScreen();
    printf("\n\n\n\n");
    printf("            ___    __    __  __  ____    _____  _  _  ____  ____ \n");
    printf("           / __)  /__\\  (  \\/  )( ___)  (  _  )( \\/ )( ___)(  _ \\\n");
    printf("          ( (_-. /(__)\\  )    (  )__)    )(_)(  \\  /  )__)  )   /\n");
    printf("           \\___/(__)(__)(_/\\/\\_)(____)  (_____)  \\/  (____)(_)\\_)\n");
    printf("\n\n          FINAL SCORE: %d\n\n\n\n\n\n", this->score);
}

/**************************************************************************
 *  Funcion: print()
 *  Proposito: Funcion que toma la matriz frame que representa visualmente
 *             al juego de manera binaria en donde cada celda representa 
 *             un pixel con un booleano que indica si este esta prendido
 *             o apagado, transforma este frame a un frame en braile e 
 *             imprime la pantalla ademas de otros datos de la interfaz 
 *             como el puntaje, vidas y limites del juego
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
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
    printf("\n Score: %d\n Lives: %d\n", this->score, this->lives);
    fflush(stdout);
    cleanFrame();
}

/**************************************************************************
 *  Funcion: setFrame()
 *  Proposito: Guardar la matriz frame que representa visualmente al juego
 *             en el atributo frame de Display
 *  Argumentos:
 *      frame - Matriz de unsigned char que representa visualmente al juego
 *  Retorno:
 *      void
 * ***********************************************************************/
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

/**************************************************************************
 *  Funcion: setLives()
 *  Proposito: Guardar las vidas del jugador en el atributo lives de Display
 *  Argumentos:
 *      lives - Vidas restantes del jugador
 *  Retorno:
 *      void
 * ***********************************************************************/
void Display::setLives(int lives)
{
    this->lives = lives;
}

/**************************************************************************
 *  Funcion: setScore()
 *  Proposito: Guardar el puntaje del jugador en el atributo score de Display
 *  Argumentos:
 *      score - Puntaje del jugador
 *  Retorno:
 * ***********************************************************************/
void Display::setScore(int score)
{
    this->score = score;
}

/**************************************************************************
 *  Funcion: stringByteToChar
 *  Proposito: Transformar un byte representado en un arreglo de unsigned
 *             char a un unico byte
 *  Argumentos:
 *      stringByte - Arreglo de unsigned char que representan un byte
 *  Retorno:
 *      unsigned char - Byte equivalente a stringByte
 * ***********************************************************************/
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