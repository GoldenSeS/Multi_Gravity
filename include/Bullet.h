#ifndef BULLET_H
#define BULLET_H

#include "MovingObject.h"
#include <chrono>
#define BULLET_SPEED 200

class Bullet : public MovingObject
{
public:
    Bullet(const Point &position, const Vector &velocity, const Vector &acceleration, double collisionRadius, const std::chrono::time_point<std::chrono::high_resolution_clock> &createTime);
    void updatePosition(double deltaTime);
    void updateVelocity(double deltaTime);
    void updateSituations(double deltaTime,std::list<FixedObject> fixedObjects);
    bool should_exist();
    ~Bullet();

private:
    const std::chrono::time_point<std::chrono::high_resolution_clock> createTime;

};

#endif // BULLET_H