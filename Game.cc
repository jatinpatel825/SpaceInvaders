#include "Game.h"

Game::Game()
: numInvadersX(8)
, numInvadersY(4)
, deadInvaders(0)
{
    /* Allocate memory for the player */
    this->player = new Player();

    /* Set the player bullet */
    this->playerBullet = player->GetBullet();

    /* Allocate memory for the game timer */
    this->gameTimer = new GameTimer();

    /* Allocate memory for the invaders */
    for(int i = 0; i < this->numInvadersX; ++i)
    {
        for(int j = 0; j < this->numInvadersY; ++j)
        {
            this->invaderList[i][j] = new Invader();

            /* Set the invader bullets */
            this->invaderBullets[i][j] = this-> invaderList[i][j]->GetBullet();
        }
    }

    std::cout << "Max: " << this->totalInvaders << std::endl;
}

Game::~Game()
{
    /* Delete the memory allocated to the player */
    delete(this->player);
    this->player = 0;

    /* Delete the memory allocated for the game timer */
    delete(this->gameTimer);
    this->gameTimer = 0;

    /* Delete the memory allocated to each invader */
    for(int i = 0; i < this->numInvadersX; ++i)
    {
        for(int j = 0; j < this->numInvadersY; ++j)
        {
            delete(this->invaderList[i][j]);
            this->invaderList[i][j] = 0;
        }
    }
}

void Game::Initialise()
{
    /* Initialise the player */
    this->player->Initialise();

    /* Initialise the game timer */
    this->gameTimer->Initialise();

    /* Initialise the invaders, setting a unique starting position for each one */
    for(int i = 0; i < this->numInvadersX; ++i)
    {
        for(int j = 0; j < this->numInvadersY; ++j)
        {
            TPos startPos;
            startPos.x = static_cast<float>( (10.0f * i) + 60.0f);
            startPos.y = static_cast<float>( (5.0f * j) + 5.0f );
            this->invaderList[i][j]->Initialise(startPos);
        }
    }

    this->playing = true;
}

void Game::Update()
{
    /* Update the game timer */
    this->gameTimer->Update();

    /* Only update every so often */
    while(this->gameTimer->GetFrameTime() > 0.0)
    {
        /* Get the time delta from the game timer */
        float deltaTime = this->gameTimer->GetDelta();

        /* Exit the game when all invaders are dead */
        if(this->deadInvaders == this->totalInvaders)
        {
            this->playing = false;
        }

        /* Update the player */
        this->player->Update(deltaTime);

        /* Update the bullet */
        this->playerBullet->Update(deltaTime);

        /*
         * Update the invaders and their bullets.
         * Check for collisions between player-bullet and invader.
        */
        for(int i = 0; i < this->numInvadersX; ++i)
        {
            for(int j = 0; j < this->numInvadersY; ++j)
            {
                this->invaderList[i][j]->Update(deltaTime);
                this->ProcessInvaderBulletCollision(invaderList[i][j]);

                this->invaderBullets[i][j]->Update(deltaTime);
            }
        }

        /* Check for collisions between invader-bullet and player. */
        this->ProcessPlayerBulletCollection();

        /* Make a random invader fire a bullet */
        this->FireInvaderBullet();
    }
}

void Game::Draw()
{
    /* Draw the player */
    this->player->Draw();

    /* Draw the bullet */
    this->playerBullet->Draw();

    /* Draw each invader */
    for(int i = 0; i < this->numInvadersX; ++i)
    {
        for(int j = 0; j < this->numInvadersY; ++j)
        {
            this->invaderList[i][j]->Draw();
            this->invaderBullets[i][j]->Draw();
        }
    }
}

void Game::FireInvaderBullet()
{
    /* Check if a bullet is already alive for an invader */
    for(int i = 0; i < this->numInvadersX; ++i)
    {
        for(int j = 0; j < this->numInvadersY; ++j)
        {
            if(true == this->invaderBullets[i][j]->GetIsAlive())
            {
                return;
            }
        }
    }

    /* Set a random invader to fire */
    int randX = 0;
    int randY = 0;
    randX = (rand() % this->numInvadersX);
    randY = (rand() % this->numInvadersY);

    /* Keep randomising numbers if a dead invader is picked */
    while(false == this->invaderList[randX][randY]->GetIsAlive())
    {
        randX = (rand() % this->numInvadersX);
        randY = (rand() % this->numInvadersY);
    }

    /* Fire a bullet from a random invader's position */
    TPos tempInvaderPos = invaderList[randX][randY]->GetSpritePosition();
    this->invaderBullets[randX][randY]->FireInvaderBullet(tempInvaderPos);
}

void Game::ProcessInvaderBulletCollision(Invader* invader)
{
    /*
     * Check for collision between player-bullet and invader,
     * If collision then kill off both
    */
    if( (true == invader->GetIsAlive()) && (true == this->playerBullet->GetIsAlive()) )
    {
        int startPos = -(invader->GetSpriteArraySize() / 2);
        int endPos = (invader->GetSpriteArraySize() / 2);
        for(int i = startPos; i < endPos + 1; ++i)
        {
            for(int j = startPos; j < endPos + 1; ++j)
            {
                int bulletPosX = static_cast<int>(this->playerBullet->GetSpritePosition().x);
                int bulletPosY = static_cast<int>(this->playerBullet->GetSpritePosition().y);
                int invaderPosX = static_cast<int>(invader->GetSpritePosition().x) + j;
                int invaderPosY = static_cast<int>(invader->GetSpritePosition().y) + i;
                if( (bulletPosX == invaderPosX) && (bulletPosY == invaderPosY) )
                {
                    /* Collision occurred! */
                    this->playerBullet->Wipe();
                    this->playerBullet->SetAlive(false);
                    invader->Wipe();
                    invader->SetAlive(false);

                    /* Increase the player's score */
                    this->player->AddToScore(10);

                    /* Increment the number of dead invaders */
                    this->deadInvaders += 1;
                }
            }
        }
    }
}

void Game::ProcessPlayerBulletCollection()
{
    /*
     * Check for collision between invader-bullet and player,
     * If collision then kill both
    */

    for(int i = 0; i < numInvadersX; ++i)
    {
        for(int j = 0; j < numInvadersY; ++j)
        {
            if(true == this->invaderBullets[i][j]->GetIsAlive())
            {
                /* AABB Collision because it's simple */
                int startPos = -(this->player->GetSpriteArraySize() / 2);
                int endPos = (this->player->GetSpriteArraySize() / 2);
                for(int a = startPos; a < endPos + 1; ++a)
                {
                    for(int b = startPos; b < endPos + 1; ++b)
                    {
                        int bulletPosX = static_cast<int>(this->invaderBullets[i][j]->GetSpritePosition().x);
                        int bulletPosY = static_cast<int>(this->invaderBullets[i][j]->GetSpritePosition().y);
                        int playerPosX = static_cast<int>(this->player->GetSpritePosition().x) + b;
                        int playerPosY = static_cast<int>(this->player->GetSpritePosition().y) + a;
                        if( (bulletPosX == playerPosX) && (bulletPosY == playerPosY) )
                        {
                            /* Collision occurred! */
                            this->invaderBullets[i][j]->Wipe();
                            this->invaderBullets[i][j]->SetAlive(false);

                            this->playing = false;
                        }
                    }
                }
            }
        }
    }
}

bool Game::GetIsPlaying() const
{
    return(this->playing);
}
