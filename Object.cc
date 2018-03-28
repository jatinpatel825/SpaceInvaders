#include "Object.h"

Object::Object()
{
    this->spritePosition.x = 0;
    this->spritePosition.y = 0;
}

Object::~Object()
{
    for(int i = 0; i < this->spriteArray.spriteSize; ++i)
    {
        delete[] this->spriteArray.spriteArray[i];
        this->spriteArray.spriteArray[i] = 0;
    }

    delete[] this->spriteArray.spriteArray;
    this->spriteArray.spriteArray = 0;
}

void Object::Initialise()
{

}

void Object::Initialise(const TPos& startPos)
{

}

void Object::Draw()
{
    for(int i = 0; i < this->spriteArray.spriteSize; ++i)
    {
        for(int j = 0; j < this->spriteArray.spriteSize; ++j)
        {
            /* Position offset to take the "sprite" grid into account */
            int posY = static_cast<int>(this->spritePosition.y) - (this->spriteArray.spriteSize / 2) + i;
            int posX = static_cast<int>(this->spritePosition.x) - (this->spriteArray.spriteSize / 2) + j;

            /* Set the cursor position and draw there */
            fprintf(stderr, "\033[%d;%dH", posY, posX);
            fprintf(stderr, "%c", this->spriteArray.spriteArray[i][j]);
        }
    }

    /* TEMP: This is used to make sure the player sprite is centered properly */
    //fprintf(stderr, "\033[%d;%dHX", static_cast<int>(this->spritePosition.y), static_cast<int>(this->spritePosition.x));
}

void Object::Wipe()
{
    /* Clear the screen? */
    //printf("\e[1;1H\e[2J");

    /* Clear the area that the sprite is on */
    int startPos = -(this->spriteArray.spriteSize / 2);
    int endPos = (this->spriteArray.spriteSize / 2);
    for(int i = startPos; i < endPos + 1; ++i)
    {
        for(int j = startPos; j < endPos + 1; ++j)
        {
            int drawX = static_cast<int>(this->spritePosition.x) + j;
            int drawY = static_cast<int>(this->spritePosition.y) + i;
            fprintf(stderr, "\033[%d;%dH", drawY, drawX);
            fprintf(stderr, " ");
        }
    }
}

void Object::SetSpriteArraySize(int size)
{
    /* Set the size of the sprite in the struct */
    this->spriteArray.spriteSize = size;
}

int Object::GetSpriteArraySize() const
{
    /* Return the size of the array from the struct */
    return(this->spriteArray.spriteSize);
}

void Object::SetSpritePosition(const TPos& newPos)
{
    this->spritePosition = newPos;
}

TPos Object::GetSpritePosition() const
{
    return(this->spritePosition);
}

void Object::SetSpriteArray(const TSpriteArray& tempSpriteArray)
{
    /* Set the struct which holds the sprite size and the array */
    this->spriteArray = tempSpriteArray;
}
