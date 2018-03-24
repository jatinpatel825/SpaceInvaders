#include "Bullet.h"
#include "Invader.h"

Invader::Invader()
{
    this->bullet = new Bullet();
}

Invader::~Invader()
{
    delete(this->bullet);
    this->bullet = 0;
}

void Invader::Initialise(const TPos& startPos)
{
    /* Initialise the movement threashold and how much to move */
    this->movementThreshold = 0.0f;
    this->moveAmount = 5.0f;

    /* Initialise the timers */
    this->moveTimer = 0.0f;
    this->timerThreshold = 1.0f;

    this->currentDirection = EDirection::RIGHT;
    this->isAlive = true;

    /* Sprite for the bullet */
    const int spriteSize = 5;
    char tempInvaderSprite[spriteSize][spriteSize] =
    {
        /*{' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ','X','X','X',' ',' ',' '},
        {' ',' ',' ','X',' ','X',' ',' ',' '},
        {' ',' ',' ','X','X','X',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' '}*/

        {' ', ' ', ' ',' ',' '},
        {'X', 'X', 'X','X','X'},
        {'X', ' ', 'X',' ','X'},
        {'X', 'X', 'X','X','X'},
        {' ', ' ', ' ',' ',' '}

    };

    /* Create a temporary struct and use it to set the parent classes struct */
    TSpriteArray tempArray;
    tempArray.spriteSize = spriteSize;
    tempArray.spriteArray = new char*[spriteSize];
    for(int i = 0; i < spriteSize; ++i)
    {
        tempArray.spriteArray[i] = new char[spriteSize];
    }

    /* Set each _spriteArray_ element */
    for(int i = 0; i < spriteSize; ++i)
    {
        for(int j = 0; j < spriteSize; ++j)
        {
            tempArray.spriteArray[i][j] = tempInvaderSprite[i][j];
        }
    }

    /* Set the values in the parent class */
    this->SetSpriteArray(tempArray);
    this->SetSpritePosition(startPos);

    /* Initialise the bullet then set the bullet speed */
    this->bullet->Initialise();
    this->bullet->SetBulletSpeed(20.0f);
}

void Invader::Update(const float deltaTime)
{
    /* Invader should only move every second */
    this->moveTimer += deltaTime;
    if(this->moveTimer >= this->timerThreshold)
    {
        /* Reset the timer */
        this->moveTimer = 0.0f;

        /* Clear the space the invader is on before moving it*/
        Object::Wipe();

        /* Move the invader */
        this->MoveInvader();
    }
}

void Invader::Draw()
{
    /* Only draw the sprite if it's alive */
    if(true == this->isAlive)
    {
        Object::Draw();
    }
}

void Invader::Wipe()
{
    /* Only wipe the sprite if it's alive */
    if(true == this->isAlive)
    {
        Object::Wipe();
    }
}

void Invader::MoveInvader()
{
    TPos tempPos;
    tempPos.x = 0;
    tempPos.y = 0;
    tempPos = this->GetSpritePosition();
    switch(this->currentDirection)
    {
        case EDirection::RIGHT:
        {
            tempPos.x += this->moveAmount;
            this->movementThreshold += this->moveAmount;
            if(this->movementThreshold >= 50.0f)
            {
                this->currentDirection = EDirection::DOWN;
            }
        }
        break;

        case EDirection::LEFT:
        {
            tempPos.x -= this->moveAmount;
            this->movementThreshold -= this->moveAmount;
            if(this->movementThreshold <= -50.0f)
            {
                this->currentDirection = EDirection::DOWN;
            }
        }
        break;

        case EDirection::DOWN:
        {
            tempPos.y += 3.0f;
            if(this->movementThreshold >= 50.0f)
            {
                this->currentDirection = EDirection::LEFT;
            }
            else
            {
                this->currentDirection = EDirection::RIGHT;
            }
        }
        break;

        default:
        {
            /* Do nothing */
        }
        break;
    }

    this->SetSpritePosition(tempPos);
}

void Invader::PrepareInvaderBullet()
{
    this->bullet->FireInvaderBullet(this->GetSpritePosition());
}

void Invader::SetAlive(bool alive)
{
    this->isAlive = alive;
}

bool Invader::GetIsAlive() const
{
    return(this->isAlive);
}

Bullet* Invader::GetBullet()
{
    return(this->bullet);
}
