#ifndef __MOTHERSHIP_H__
#define __MOTHERSHIP_H__

#include "Object.h"

class MotherShip : public Object
{
    /* Member functions */
public:
    MotherShip();
    ~MotherShip();

    void Initialise();
    void Update(const float deltaTime);
    void Draw();
    void SetIsAlive(const bool alive);
    void Wipe();
    void DespawnShip();

    bool GetIsAlive() const;
protected:
private:
    void ManageMovement(const float deltaTime);
    void ManageTimer(const float deltaTime);

    /* Member variables */
public:
protected:
private:
    bool isAlive;
    const float motherShipSpeed;
    const float spawnTimer;
    float currentTimer;
    const float leftBoundary;
    const TPos startPosition;
};

#endif // __MOTHERSHIP_H__
