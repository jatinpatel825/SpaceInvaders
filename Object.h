#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <iostream>

struct TSpriteArray
{
    int spriteSize;
    char** spriteArray;
};

struct TPos
{
    float x;
    float y;
};

class Object
{
    /* Member functions */
public:
    Object();
    virtual ~Object() = 0;

    /* Pure virtual because this should be implemented in the child class */
    virtual void Update(const float deltaTime) = 0;

    /* Virtual since either implementation (parent/child) can be used */
    virtual void Initialise();
    virtual void Initialise(const TPos& startPos);
    virtual void Draw();

    TPos GetSpritePosition() const;
    int GetSpriteArraySize() const;

protected:
    void SetSpriteArraySize(int size);
    void SetSpritePosition(const TPos& newPos);

    void SetSpriteArray(const TSpriteArray& spriteArray);

    void Wipe();

private:

    /* Member variables */
public:
protected:
    TPos spritePosition;
    TSpriteArray spriteArray;

private:
};

#endif // __OBJECT_H__
