#include "control.h"

Control::Control()
{
}

void Control::initialize()
{
    tcgetattr(STDIN_FILENO, &(this->oldt));
    this->newt = this->oldt;
    this->newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &(this->newt));
}

void Control::deInitialize()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &(this->oldt));
}

void Control::getKeyPresses()
{
    char keyPressed;
    this->moveLeft = false;
    this->moveRight = false;
    this->shoot = false;
    this->tv.tv_sec = 0;
    this->tv.tv_usec = 5;

    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &(this->rdfs));
    select(STDIN_FILENO + 1, &(this->rdfs), NULL, NULL, &tv);
    do
    {
        keyPressed = 0;
        if (FD_ISSET(STDIN_FILENO, &(this->rdfs)))
        {
            keyPressed = getchar();
            switch (keyPressed)
            {
            case 'j':
                this->moveLeft = true;
                break;
            case 'l':
                this->moveRight = true;
                break;
            case 'i':
                this->shoot = true;
                break;
            default:
                break;
            }
            select(STDIN_FILENO + 1, &(this->rdfs), NULL, NULL, &tv);
        }
    }while(keyPressed);
    fflush(stdin);
}

bool Control::getMoveLeft()
{
    return moveLeft;
}

bool Control::getMoveRight()
{
    return moveRight;
}

bool Control::getShoot()
{
    return shoot;
}
