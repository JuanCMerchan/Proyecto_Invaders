#include "game.h"

Game::Game()
{
    cleanFrame();
}

/**************************************************************************
 *  Funcion: cleanFrame()
 *  Proposito: Limpiar la matriz frame que representa visualmente al juego
 *             llenandola de 0's
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Game::cleanFrame()
{
    memset(frame, 0, sizeof(frame));
}

/**************************************************************************
 *  Funcion: createFrame()
 *  Proposito: Crear la matriz que representara visualmente al juego para
 *             lo que se va a recorrer todas las entidades, obtener su 
 *             sprite y dadas la posicion de la entidad y los datos del 
 *             sprite este se pinta en la matriz.
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Game::createFrame()
{
    const Sprites *sprite;
    Entity *entity;
    for (int i = 0; i < MAX_ENTITIES; i++)
    {
        if (!(this->allEntities[i]->getAlive()))
        {
            //Si la entidad no esta viva esta se salta y no se pinta
            continue;
        }
        if (this->allEntities[i]->getX() >= 0 && this->allEntities[i]->getX() + this->allEntities[i]->getSprite()->width <= DISP_WIDTH)
        {
            if (this->allEntities[i]->getY() >= 0 && this->allEntities[i]->getY() + this->allEntities[i]->getSprite()->length <= DISP_HEIGHT)
            {
                //Se recorren las entidades y se pintan solo si existen dentro de los limites de la pantalla
                entity = this->allEntities[i];
                sprite = entity->getSprite();
                for (int j = 0; j < sprite->length; j++)
                {
                    for (int k = 0; k < sprite->width; k++)
                    {
                        //Se recorre es sprite de la entidad y se pinta cada "pixel" en su respectiva posicion
                        if (sprite->sprites[entity->getSpriteIndex()][j][k])
                        {
                            //Solo se pintan los pixeles verdaderos/encendidos
                            this->frame[entity->getY() + j][entity->getX() + k] = sprite->sprites[entity->getSpriteIndex()][j][k];
                        }
                    }
                }
            }
        }
    }
    //Se manda el frame al display
    this->display.setFrame(this->frame);
    //Se le indica al display que imprima
    this->display.print();
    //Se limpia el frame
    cleanFrame();
}

/**************************************************************************
 *  Funcion: initialize()
 *  Proposito: Funcion que inicializa los atributos del juego incluidas
 *             todas las entidades.
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Game::initialize()
{
    this->control.initialize();
    this->timer.reset();

    //Inicializacion de aliens, cada for es una fila de aliens
    int x = 5;
    int y = 12;
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

    //Inicializacion de las balas
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        this->bullets[i].initialize(0, 0, Color::GREEN);
        this->allEntities[MAX_ALIENS + i] = &this->bullets[i];
    }

    //Inicializacion de los bunkers
    x = 42;
    y = DISP_HEIGHT - BUNKER_DISP_HEIGHT;
    for (int i = 0; i < MAX_BUNKERS; i++)
    {
        this->bunkers[i].initialize(x, y, Color::PINK);
        x += 30;
        this->allEntities[MAX_ALIENS + MAX_BULLETS + i] = &this->bunkers[i];
    }

    //Inicializacion del ovni
    this->ufo.initialize(Color::RED);
    this->allEntities[MAX_ENTITIES - 2] = &ufo;

    //Inicializacion del jugador
    x = (DISP_WIDTH / 2) - (PLAYER_SPRITE.width / 2);
    y = DISP_HEIGHT - PLAYER_SPRITE.length - PLAYER_DISP_HEIGHT;
    this->player.initialize(x, y, Color::YELLOW);
    this->allEntities[MAX_ENTITIES - 1] = &(this->player);
    this->ufo.setPlayer(&(this->player));

    //Fijar referencias para las clases/objetos que las necesitan
    Ufo::setBullets(this->bullets);
    Player::setBullets(this->bullets);
    Alien::setBullets(this->bullets);
    Bullet::setEntities(this->allEntities);
}

/**************************************************************************
 *  Funcion: start()
 *  Proposito: Funcion que representa el juego en donde cada cierta cantidad
 *             de milisegundos dependiendo del tipo de entidad invoca la 
 *             funcion act() de dicha entidad. Si se llega a la condicion de
 *             victoria o derrota se acaba el ciclo del juego y se imprime
 *             la pantalla de game over.
 *  Argumentos:
 *      void
 *  Retorno:
 *      void
 * ***********************************************************************/
void Game::start()
{
    int score = 0;
    unsigned long previousAliens;
    unsigned long previousDisplay;
    unsigned long previousBullets;
    unsigned long previousBunkers;
    unsigned long previousPlayer;
    unsigned long previousUfo;
    int numAliensAlive = MAX_ALIENS;
    int numUfoKills = 0;
    bool gaming = true;
    initialize();
    previousAliens = timer.getMillis();
    previousDisplay = previousAliens;
    previousBullets = previousAliens;
    previousBunkers = previousAliens;
    previousPlayer = previousAliens;
    previousUfo = previousAliens;
    while (gaming)
    {
        if(this->timer.getMillis() - previousUfo >= TIME_UFO)
        {
            //Se llama la funcion act del ovni
            previousUfo = timer.getMillis();
            this->ufo.act();
            if(this->ufo.getHealth() == 0)
            {
                //Si la vida del ovni es 0 se incrementa el numero de ovnis muertos
                numUfoKills ++;
            }
        }

        if (this->timer.getMillis() - previousAliens >= BASE_TIME_ALIEN + (VARIABLE_TIME_ALIEN * numAliensAlive / MAX_ALIENS))
        {
            //Se llama la funcion act de todos los alien
            score = 0;
            numAliensAlive = 0;
            previousAliens = this->timer.getMillis();
            for (int i = 0; i < MAX_ALIENS; i++)
            {
                //Tambien se reviza si el alien esta vivo o muerto
                //Si esta vivo se reviza si llego a la altura de los bunker, de ser verdad acaba el juego
                //Si esta muerto se actualiza el score
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
            score += (numUfoKills * this->ufo.getScore());
            this->display.setScore(score);
            if (numAliensAlive == 0 || gaming == false)
            {
                //Si el numero de aliens vivos es 0 o gaming es falso se sale del ciclo y se cambia gaming a false
                gaming = false;
                break;
            }
            //Se actualiza el score con el numero de ovnis muertos
        }

        if (this->timer.getMillis() - previousBullets >= TIME_BULLET)
        {
            //Se llama a la funcion act de las balas
            previousBullets = this->timer.getMillis();
            for (int i = 0; i < MAX_BULLETS; i++)
            {
                this->bullets[i].act();
            }
        }

        if (this->timer.getMillis() - previousBunkers >= TIME_BUNKER)
        {
            //Se llama a la funcion act de los bunkers
            previousBunkers = this->timer.getMillis();
            for (int i = 0; i < MAX_BUNKERS; i++)
            {
                this->bunkers[i].act();
            }
        }

        if (this->timer.getMillis() - previousPlayer >= TIME_PLAYER)
        {
            previousPlayer = this->timer.getMillis();
            if (player.getAlive() == false)
            {
                //Si el jugador esta muerto se cambia gaming a false para que acabe el juego
                gaming = false;
            }
            else
            {
                //Se toma el input del control y se llama a la funcion act del jugador
                this->control.getKeyPresses();
                this->player.act(this->control.getMoveRight(), this->control.getMoveLeft(), this->control.getShoot());
            }
        }

        if (this->timer.getMillis() - previousDisplay >= TIME_DISPLAY)
        {
            //Se manda el numero de vidas del jugador y el score al display y se crea el frame que representa visualmente al juego
            previousDisplay = this->timer.getMillis();
            display.setLives(this->player.getHealth());
            createFrame();
        }
    }
    //Se llama a la funcion deInitialize del control (Linux: Restaurar el estado de la terminal)
    this->control.deInitialize();
    //Se le indica al display que imprima la pantalla de gameOver
    display.gameOver();
}
