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
        if (!(allEntities[i]->getAlive()))
        {
            continue;
        }
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
                        if (sprite->sprites[entity->getSpriteIndex()][j][k])
                        {
                            this->frame[entity->getY() + j][entity->getX() + k] = sprite->sprites[entity->getSpriteIndex()][j][k];
                        }
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
    int x = 5;
    int y = 12;
    for (int i = 0; i < MAX_SINGLE_ALIEN; i++)
    {
        this->aliens[i].initialize(x, y, &OCTOPUS_SPRITE, Color::RED);
        x += 15;
        allEntities[i] = &this->aliens[i];
    }
    y += 12;
    x = 5;
    for (int i = 0; i < (MAX_SINGLE_ALIEN); i++)
    {
        this->aliens[(MAX_SINGLE_ALIEN) + i].initialize(x, y, &CRAB_SPRITE, Color::BLUE);
        x += 15;
        allEntities[(MAX_SINGLE_ALIEN) + i] = &this->aliens[(MAX_SINGLE_ALIEN) + i];
    }
    y += 12;
    x = 5;
    for (int i = 0; i < (MAX_SINGLE_ALIEN); i++)
    {
        this->aliens[(MAX_SINGLE_ALIEN * 2) + i].initialize(x, y, &SQUID_SPRITE, Color::BLUE);
        x += 15;
        allEntities[(MAX_SINGLE_ALIEN * 2) + i] = &this->aliens[(MAX_SINGLE_ALIEN * 2) + i];
    }
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        this->bullets[i].initialize(0, 0, &BULLET_SPRITE, Color::GREEN);
        allEntities[MAX_ALIENS + i] = &this->bullets[i];
    }
    x = 40;
    y = DISP_HEIGHT - 30;
    for (int i = 0; i < MAX_BUNKERS; i++)
    {
        this->bunkers[i].initialize(x, y, &BUNKER_SPRITE, Color::PINK);
        x += 30;
        allEntities[MAX_ALIENS + MAX_BULLETS + i] = &this->bunkers[i];
    }
    Alien::setBullets(bullets);
    Bullet::setEntities(allEntities);
}

void Game::start()
{
    Timer timer;
    unsigned long previousAliens;
    unsigned long previousDisplay;
    unsigned long previousBullets;
    unsigned long previousBunkers;
    initialize();
    previousAliens = timer.getMillis();
    previousDisplay = previousAliens;
    previousBullets = previousAliens;
    previousBunkers = previousAliens;
    while (true)
    {

        if (timer.getMillis() - previousAliens > 500)
        {
            previousAliens = timer.getMillis();
            for (int i = 0; i < MAX_ALIENS; i++)
            {

                this->aliens[i].act();
            }
        }
        if (timer.getMillis() - previousBullets > 150)
        {
            previousBullets = timer.getMillis();
            for (int i = 0; i < MAX_BULLETS; i++)
            {
                this->bullets[i].act();
            }
        }
        if (timer.getMillis() - previousBunkers > 500)
        {
            previousBunkers = timer.getMillis();
            for (int i = 0; i < MAX_BUNKERS; i++)
            {
                this->bunkers[i].act();
            }
        }
        if (timer.getMillis() - previousDisplay > 1000 / 60)
        {
            previousDisplay = timer.getMillis();
            createFrame();
        }
    }
}
