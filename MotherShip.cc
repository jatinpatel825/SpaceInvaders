#include "MotherShip.h"

MotherShip::MotherShip()
: motherShipSpeed(40.0f)
, isAlive(false)
, startPosition(TPos(190.0f, 4.0f))
, spawnTimer(10.0f)
, currentTimer(0.0f)
{

}

MotherShip::~MotherShip()
{

}

void MotherShip::Initialise()
{
    /* Initialise the sprite */
    const int spriteSize = 7;
    char tempMotherShipSprite[spriteSize][spriteSize] =
    {
        {' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', '#', '#', '#', ' ', ' '},
        {' ', '#', '#', '#', '#', '#', ' '},
        {'#', ' ', '#', ' ', '#', ' ', '#'},
        {' ', '#', '#', '#', '#', '#', ' '},
        {' ', ' ', ' ', '#', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' '}
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
            tempArray.spriteArray[i][j] = tempMotherShipSprite[i][j];
        }
    }

    /* Set the values in the parent class */
    this->SetSpriteArray(tempArray);
    this->SetSpritePosition(this->startPosition);
}

void MotherShip::Update(const float deltaTime)
{
    this->ManageTimer(deltaTime);
    this->ManageMovement(deltaTime);
    this->DespawnShip();
}

void MotherShip::ManageTimer(const float deltaTime)
{
    /* Spawn the mothership if the timer reaches a threshold */
    if(this->currentTimer >= this->spawnTimer)
    {
        this->isAlive = true;
        this->currentTimer = 0.0f;
    }
    else
    {
        this->currentTimer += deltaTime;
    }
}

void MotherShip::ManageMovement(const float deltaTime)
{
    if(true == this->isAlive)
    {
        TPos tempPos(0.0f, 0.0f);
        tempPos = this->GetSpritePosition();
        tempPos.x -= (this->motherShipSpeed * deltaTime);
        this->SetSpritePosition(tempPos);
    }
}

void MotherShip::Draw()
{
    if(true == this->isAlive)
    {
        this->Wipe();
        Object::Draw();
    }
}

void MotherShip::Wipe()
{
    Object::Wipe();
}

void MotherShip::DespawnShip()
{
    if(true == this->isAlive)
    {
        /* Despawn the ship if it reaches the left side of the screen */
        if(this->GetSpritePosition().x <= 4)
        {
            this->isAlive = false;
            this->Wipe();
        }
    }
}

bool MotherShip::GetIsAlive() const
{
    return this->isAlive;
}

void MotherShip::SetIsAlive(const bool alive)
{
    this->isAlive = alive;
}
