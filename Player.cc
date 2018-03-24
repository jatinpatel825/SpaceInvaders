#include "Player.h"

Player::Player()
: playerSpeed(5.0f)
{
    this->score = 0;
    this->minPlayerPos = 0.0f;
    this->maxPlayerPos = 0.0f;
    this->direction = 0;
    this->isKeyPressed = false;
    bullet = new Bullet();
}

Player::~Player()
{
    delete(this->bullet);
    this->bullet  = 0;
}

void Player::Initialise()
{
    /* Set the starting position, speed and score */
    TPos tempPos;
    tempPos.x = 102.0f;
    tempPos.y = 55.0f;

    this->score = 0;

    /* Set min and max player pos */
    this->minPlayerPos = 10.0f;
    this->maxPlayerPos = 194.0f;

    /* (1 = right), (-1 = left) */
    this->direction = 1.0f;

    /* Sprite for the player */
    const int spriteSize = 3;
    char tempPlayerSprite[spriteSize][spriteSize] =
    {
        {' ','O',' '},
        {'O','O','O'},
        {'O','O','O'}
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
            tempArray.spriteArray[i][j] = tempPlayerSprite[i][j];
        }
    }

    /* Set the values in the parent class */
    this->SetSpriteArray(tempArray);
    this->SetSpritePosition(tempPos);

    /* Initialise the bullet */
    bullet->Initialise();
}

void Player::Update(const float deltaTime)
{
    this->GetInput();
    this->ManageMovement();
    fprintf(stderr, "\033[%d;%dH", 1, 1);
    fprintf(stderr, "Score: %d, %f", this->score, deltaTime);

}

void Player::Draw()
{
    /* Draw the score */
    fprintf(stderr, "\033[%d;%dH", 1, 1);
    fprintf(stderr, "Score: %d", this->score);

    /* Call the parent class Draw() */
    Object::Draw();
}

void Player::GetInput()
{
    /* Get keyboard input */
    KEY tempKey = keyPress.GetKeyPress();

    switch(tempKey)
    {
        case KEY::KEY_LEFT:
        {
            /* Set direction left */
            this->direction = -1.0f;
            this->isKeyPressed = true;
        }
        break;

        case KEY::KEY_RIGHT:
        {
            /* Set direction right */
            this->direction = 1.0f;
            this->isKeyPressed = true;
        }
        break;

        case KEY::KEY_UP:
        {
            /* Fire a bullet from the player's position */
            bullet->FirePlayerBullet(this->GetSpritePosition());
        }
        break;

        default:
        {
            /* Do nothing */
        }
        break;
    }
}

void Player::RestrictMovement(TPos& pos)
{
    /* Restrict how far the player can go right */
    if(pos.x > this->maxPlayerPos)
    {
        pos.x = this->maxPlayerPos;
    }

    /* Restrict how far the player can go left */
    if(pos.x < this->minPlayerPos)
    {
        pos.x = this->minPlayerPos;
    }
}

void Player::ManageMovement()
{
    /* Only move the player if a valid key was pressed */
    if(true == this->isKeyPressed)
    {
        /* Create a temporary position variable that's set the the player's current position */
        TPos tempPos;
        tempPos = this->GetSpritePosition();

        /* Update the x position for the player */
        tempPos.x += (this->playerSpeed * this->direction);

        /* Restrict the player's movement so they can't go too far left or right */
        this->RestrictMovement(tempPos);

        /* Clean the area where the player is BEFORE setting the new position */
        Object::Wipe();

        /* Set the new player position */
        this->SetSpritePosition(tempPos);

        /* The key is no longer pressed, this will avoid the player from continually moving if the key isn't pressed */
        this->isKeyPressed = false;
    }
}

Bullet* Player::GetBullet() const
{
    return(this->bullet);
}

void Player::AddToScore(int scoreIncrement)
{
    this->score += scoreIncrement;
}

int Player::GetScore() const
{
    return(this->score);
}
