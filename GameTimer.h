#ifndef __GAMETIMER_H__
#define __GAMETIMER_H__

/* Library Includes */
#include <sys/time.h>
#include <iostream>

class GameTimer
{
    /* Member functions */
public:
    GameTimer();
    ~GameTimer();

    void Initialise();
    void Update();

    float GetDelta();
    double GetFrameTime() const;
protected:
private:

    /* Member variables */
public:
protected:
private:
    struct timeval timeVal;
    double currentTime;
    double newTime;
    double frameTime;
    const double singleFrame = 1.0 / 60.0;
};

#endif // __GAMETIMER_H__
