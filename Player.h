#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Object.h"
#include "GetKey.h"
#include "Bullet.h"

class Player : public Object
{
    /* Member functions */
public:
    Player();
    ~Player();

    void Initialise();
    void Update(const float deltaTime);
    void Draw();

    void AddToScore(int score);
    int GetScore() const;

    Bullet* GetBullet() const ;
protected:
private:
    void GetInput();
    void ManageMovement(const float deltaTime);
    void RestrictMovement(TPos& currentPos);

    /* Member variables */
public:
protected:
private:
    int score;
    bool isKeyPressed;
    float direction;
    float minPlayerPos;
    float maxPlayerPos;
    float moveTimer;
    const float playerSpeed;
    GetKey keyPress;
    Bullet* bullet;
};

#endif // __PLAYER_H__
