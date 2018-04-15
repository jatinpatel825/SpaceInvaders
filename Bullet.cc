#include "Bullet.h"

Bullet::Bullet()
{
    this->isAlive = false;
}

Bullet::~Bullet()
{

}

void Bullet::Initialise()
{
    /* Set the bullet position and speed */
    TPos tempPos;
    tempPos.x = 0.0f;
    tempPos.y = 0.0f;

    this->bulletSpeed = 80.0f;
    this->isAlive = false;
    this->direction = 0.0f;

    /* Sprite for the bullet */
    const int spriteSize = 3;
    char tempBulletSprite[spriteSize][spriteSize] =
    {
        {' ', ' ', ' '},
        {' ', '*', ' '},
        {' ', ' ', ' '}
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
            tempArray.spriteArray[i][j] = tempBulletSprite[i][j];
        }
    }

    /* Set the values in the parent class */
    this->SetSpriteArray(tempArray);
    this->SetSpritePosition(tempPos);
}

void Bullet::Update(const float deltaTime)
{
    /* Only process the bullet if it's alive */
    if(true == this->isAlive)
    {
        /* Move the bullet up*/
        TPos tempPos = this->GetSpritePosition();
        tempPos.y += (this->bulletSpeed * deltaTime * this->direction);
        this->SetSpritePosition(tempPos);
        this->CheckBoundaryCollision();
    }
}

void Bullet::Draw()
{
    /* Only draw the bullet if it's alive */
    if(true == this->isAlive)
    {
        Object::Draw();
    }
}

void Bullet::Wipe()
{
    Object::Wipe();
}

void Bullet::FirePlayerBullet(const TPos& playerPos)
{
    /* Don't try to fire a bullet if there's already a bullet */
    if(false == this->isAlive)
    {
        /* Set the bullet as alive */
        this->isAlive = true;

        /* Set the bullet to the player's location */
        this->SetSpritePosition(playerPos);
        this->direction = -1.0f;
    }
}

void Bullet::FireInvaderBullet(const TPos& invaderPos)
{
    /* Don't try to fire a bullet if there's already a bullet */
    if(false == this->isAlive)
    {
        /* Set the bullet as alive */
        this->isAlive = true;

        /* Set the bullet to the player's location */
        this->SetSpritePosition(invaderPos);
        this->direction = 1.0f;
    }
}

/* Check if the bullet is out of bounds */
void Bullet::CheckBoundaryCollision()
{
    /*
     * Check if the bullet is out of bounds,
     * "2" represents the top of the terminal.
    */
    if( ((this->GetSpritePosition().y < 2) || (this->GetSpritePosition().y > (this->terminalHeight - 1))) && (true == this->isAlive) )
    {
        this->isAlive = false;
        this->Wipe();
    }
}

void Bullet::SetAlive(bool alive)
{
    this->isAlive = alive;
}

bool Bullet::GetIsAlive() const
{
    return(this->isAlive);
}

void Bullet::SetBulletSpeed(float tempBulletSpeed)
{
    this->bulletSpeed = tempBulletSpeed;
}
