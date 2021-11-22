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
        if (!(this->allEntities[i]->getAlive()))
        {
            continue;
        }
        if (this->allEntities[i]->getX() >= 0 && this->allEntities[i]->getX() + this->allEntities[i]->getSprite()->width <= DISP_WIDTH)
        {
            if (this->allEntities[i]->getY() >= 0 && this->allEntities[i]->getY() + this->allEntities[i]->getSprite()->length <= DISP_HEIGHT)
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
    this->control.initialize();
    this->timer.reset();
    int x = 5;
    int y = 36;
    for (int i = 0; i < MAX_SINGLE_ALIEN; i++)
    {
        this->aliens[i].initialize(x, y, &OCTOPUS_SPRITE, Color::RED, OCTOPUS_SCORE);
        x += 15;
        this->allEntities[i] = &this->aliens[i];
    }
    y += 12;
    x = 5;
    for (int i = 0; i < MAX_SINGLE_ALIEN; i++)
    {
        this->aliens[(MAX_SINGLE_ALIEN) + i].initialize(x, y, &OCTOPUS_SPRITE, Color::RED, OCTOPUS_SCORE);
        x += 15;
        this->allEntities[(MAX_SINGLE_ALIEN) + i] = &this->aliens[(MAX_SINGLE_ALIEN) + i];
    }
    y += 12;
    x = 5;
    for (int i = 0; i < (MAX_SINGLE_ALIEN); i++)
    {
        this->aliens[(MAX_SINGLE_ALIEN * 2) + i].initialize(x, y, &CRAB_SPRITE, Color::BLUE, CRAB_SCORE);
        x += 15;
        this->allEntities[(MAX_SINGLE_ALIEN * 2) + i] = &this->aliens[(MAX_SINGLE_ALIEN * 2) + i];
    }
    y += 12;
    x = 5;
    for (int i = 0; i < (MAX_SINGLE_ALIEN); i++)
    {
        this->aliens[(MAX_SINGLE_ALIEN * 3) + i].initialize(x, y, &SQUID_SPRITE, Color::BLUE, SQUID_SCORE);
        x += 15;
        this->allEntities[(MAX_SINGLE_ALIEN * 3) + i] = &this->aliens[(MAX_SINGLE_ALIEN * 3) + i];
    }
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        this->bullets[i].initialize(0, 0, &BULLET_SPRITE, Color::GREEN);
        this->allEntities[MAX_ALIENS + i] = &this->bullets[i];
    }
    x = 42;
    y = DISP_HEIGHT - BUNKER_DISP_HEIGHT;
    for (int i = 0; i < MAX_BUNKERS; i++)
    {
        this->bunkers[i].initialize(x, y, &BUNKER_SPRITE, Color::PINK);
        x += 30;
        this->allEntities[MAX_ALIENS + MAX_BULLETS + i] = &this->bunkers[i];
    }
    x = (DISP_WIDTH / 2) - (PLAYER_SPRITE.width / 2);
    y = DISP_HEIGHT - PLAYER_SPRITE.length - PLAYER_DISP_HEIGHT;
    player.initialize(x, y, &PLAYER_SPRITE, Color::YELLOW);
    this->allEntities[MAX_ENTITIES - 1] = &player;
    Player::setBullets(bullets);
    Alien::setBullets(bullets);
    Bullet::setEntities(allEntities);
}

void Game::start()
{
    int score = 0;
    unsigned long previousAliens;
    unsigned long previousDisplay;
    unsigned long previousBullets;
    unsigned long previousBunkers;
    unsigned long previousPlayer;
    int numAliensAlive = MAX_ALIENS;
    bool gaming = true;
    initialize();
    previousAliens = timer.getMillis();
    previousDisplay = previousAliens;
    previousBullets = previousAliens;
    previousBunkers = previousAliens;
    previousPlayer = previousAliens;
    while (gaming)
    {
        if (this->timer.getMillis() - previousAliens > 15 + (485 * numAliensAlive / MAX_ALIENS))
        {
            numAliensAlive = 0;
            score = 0;
            previousAliens = this->timer.getMillis();
            for (int i = 0; i < MAX_ALIENS; i++)
            {
                if (this->aliens[i].getHealth() != 0)
                {
                    numAliensAlive++;
                    if(this->aliens[i].getY()  >= DISP_HEIGHT - BUNKER_DISP_HEIGHT - this->aliens[i].getSprite()->length + 1)
                    {
                        gaming = false;
                    }
                }
                else
                {
                    score += this->aliens[i].getScore();
                }
                this->aliens[i].act();
            }
            if (numAliensAlive == 0 || gaming == false)
            {
                gaming = false;
                break;
            }
        }
        if (this->timer.getMillis() - previousBullets > 10)
        {
            previousBullets = this->timer.getMillis();
            for (int i = 0; i < MAX_BULLETS; i++)
            {
                this->bullets[i].act();
            }
        }
        if (this->timer.getMillis() - previousBunkers > 500)
        {
            previousBunkers = this->timer.getMillis();
            for (int i = 0; i < MAX_BUNKERS; i++)
            {
                this->bunkers[i].act();
            }
        }
        if (this->timer.getMillis() - previousPlayer > 1000 / 30)
        {
            previousPlayer = this->timer.getMillis();
            if (player.getAlive() == false)
            {
                gaming = false;
            }
            else
            {
                this->control.getKeyPresses();
                this->player.act(this->control.getMoveRight(), this->control.getMoveLeft(), this->control.getShoot());
            }
        }
        if (this->timer.getMillis() - previousDisplay > 1000 / 60)
        {
            previousDisplay = this->timer.getMillis();
            display.setLives(this->player.getHealth());
            display.setScore(score);
            createFrame();
        }
    }
    this->control.deInitialize();
    display.gameOver();
}
