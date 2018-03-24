#ifndef __INVADER_H__
#define __INVADER_H__

#include "Object.h"

class Bullet;

enum EDirection
{
    RIGHT = 0,
    LEFT = 1,
    DOWN = 2
};

class Invader : public Object
{
    /* Member functions */
public:
    Invader();
    ~Invader();

    void Initialise(const TPos& startPos);
    void Update(const float deltaTime);
    void Draw();

    void SetAlive(bool alive);
    bool GetIsAlive() const;

    void PrepareInvaderBullet();
    void Wipe();

    Bullet* GetBullet();

protected:
private:
    void MoveInvader();
    void UpdateSprite();
    void FireBullet();

    /* Member variables */
public:
protected:
private:
    float moveTimer;
    float timerThreshold;
    float movementThreshold;
    float moveAmount;
    bool isAlive;
    EDirection currentDirection;
    Bullet* bullet;
};

#endif // __INVADER_H__
