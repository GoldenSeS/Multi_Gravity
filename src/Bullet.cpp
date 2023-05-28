#include "Bullet.h"

Bullet::Bullet(const Point &position, const Vector &velocity, const Vector &acceleration, double collisionRadius, const std::chrono::time_point<std::chrono::high_resolution_clock> &createTime)
    : MovingObject(position, velocity, acceleration, collisionRadius), createTime(createTime)
{
}

void Bullet::updatePosition(double deltaTime)
{
    Point tem = Vector(this->getVelocity() * deltaTime).toPoint();
    this->setPosition(Point(this->getPosition() + tem));
    this->setCollisionBox(Circle(this->getPosition(), this->getCollisionBox().getRadius()));
}

void Bullet::updateVelocity(double deltaTime)
{
    this->setVelocity(Vector(this->getVelocity() + this->getAcceleration() * deltaTime));
}

void Bullet::updateSituations(double deltaTime, std::list<FixedObject> fixedObjects)
{
    this->updateVelocity(deltaTime);
    this->updatePosition(deltaTime);
    this->setAcceleration(this->calculateAcceleration(fixedObjects));
}

bool Bullet::should_exist()
{
    auto now = std::chrono::high_resolution_clock::now();
    if(now-createTime>std::chrono::seconds(10))
    return false;
    return true;
}

Bullet::~Bullet()
{
}

