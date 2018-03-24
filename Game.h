#ifndef __GAME_H__
#define __GAME_H__

/* Local Includes */
#include "Player.h"
#include "Invader.h"
#include "GameTimer.h"

class Game
{
    /* Member functions */
public:
    Game();
    ~Game();

    void Update();
    void Initialise();
    void Draw();

    bool GetIsPlaying() const;
protected:
private:
    void ProcessInvaderBulletCollision(Invader* invader);
    void ProcessPlayerBulletCollection();
    void FireInvaderBullet();

    /* Member variables */
public:
protected:
private:
    int numInvadersX;
    int numInvadersY;
    bool playing;
    Player* player;
    Bullet* playerBullet;
    GameTimer* gameTimer;
    Bullet* invaderBullets[8][4];
    Invader* invaderList[8][4];
};

#endif // __GAME_H__
