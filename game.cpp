#include "game.h"

Game::Game()
{
    cleanFrame();
}

void Game::cleanFrame()
{
    memset(frame, 0, sizeof(frame));
}

void Game::createFrame()
{
    const Sprites *sprite;
    Entity *entity;
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        if (this->allEntities[i]->getX() >= 0 && this->allEntities[i]->getX() <= DISP_WIDTH)
        {
            if (this->allEntities[i]->getY() >= 0 && this->allEntities[i]->getY() <= DISP_HEIGHT)
            {
                entity = this->allEntities[i];
                sprite = entity->getSprite();
                for (int j = 0; j < sprite->length; j++)
                {
                    for (int k = 0; k < sprite->width; k++)
                    {
                        this->frame[entity->getY() + j][entity->getX() + k] = sprite->sprites[entity->getSpriteIndex()][j][k];
                    }
                }
            }
        }
    }
    this->display.setFrame(this->frame);
    this->display.print();
    cleanFrame();
}

void Game::initialize()
{
    int x = 10;
    int y = 0;
    for (int i = 0; i < 10; i++)
    {
        this->aliens[i].initialize(x, y, &SQUID_SPRITE, Color::RED);
        x += aliens[i].getSprite()->width + 3;
        allEntities[i] = &this->aliens[i];
    }
}

void Game::start()
{
    Timer timer;
    unsigned long previousAliens;
    unsigned long previousDisplay;
    initialize();
    previousAliens = timer.getMillis();
    previousDisplay = previousAliens;
    while (true)
    {

        if (timer.getMillis() - previousAliens > 500)
        {
            previousAliens = timer.getMillis();
            for (int i = 0; i < NUM_ALIENS; i++)
            {
                this->aliens[i].act();
            }
        }
        if (timer.getMillis() - previousDisplay > 1000 / 60)
        {
            previousDisplay = timer.getMillis();
            createFrame();
        }
    }
}
