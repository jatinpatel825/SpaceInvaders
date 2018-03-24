#include "GameTimer.h"

double GetMin(double a, double b)
{
    return(a < b ? a : b);
}

GameTimer::GameTimer()
{

}

GameTimer::~GameTimer()
{

}

void GameTimer::Initialise()
{
    gettimeofday(&this->timeVal, NULL);
    this->currentTime = this->timeVal.tv_sec + (this->timeVal.tv_usec / 1000000.0);
}

void GameTimer::Update()
{
    gettimeofday(&this->timeVal, NULL);
    this->newTime = this->timeVal.tv_sec + (this->timeVal.tv_usec / 1000000.0);
    this->frameTime = this->newTime - this->currentTime;
    this->currentTime = this->newTime;
}

float GameTimer::GetDelta()
{
    float delta = 0.0f;

    delta = static_cast<float>(GetMin(this->frameTime, this->singleFrame));
    this->frameTime -= delta;

    return delta;
}

double GameTimer::GetFrameTime() const
{
    return this->frameTime;
}
