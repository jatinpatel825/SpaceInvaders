#ifndef __BULLET_H__
#define __BULLET_H__

#include "Object.h"

class Bullet : public Object
{
    /* Member functions */
public:
    Bullet();
    ~Bullet();

    void Update(const float deltaTime);
    void Initialise();
    void Draw();

    void FirePlayerBullet(const TPos& playerPos);
    void FireInvaderBullet(const TPos& invaderPos);

    void SetAlive(bool alive);
    bool GetIsAlive() const;

    void SetBulletSpeed(float bulletSpeed);

    void Wipe();
protected:
private:
    void CheckBoundaryCollision();

    /* Member variables */
public:
protected:
private:
    float bulletSpeed;
    float direction;
    bool isAlive;
};


#endif // __BULLET_H__
