#include "MovingObject.h"

MovingObject::MovingObject(const Point &position, const Vector &velocity, const Vector &acceleration, double collisionRadius) : position(position), velocity(velocity), acceleration(acceleration), collisionBox(position, collisionRadius)
{
}

Point MovingObject::getPosition() const
{
    return position;
}

Vector MovingObject::getVelocity() const
{
    return velocity;
}

Vector MovingObject::getAcceleration() const
{
    return acceleration;
}

double MovingObject::getSpeed() const
{
    return velocity.getLength();
}

double MovingObject::getAccelerationModule() const
{
    return acceleration.getLength();
}

void MovingObject::setPosition(const Point &position)
{
    this->position = position;
    collisionBox.setCenterPoint(position);
}

void MovingObject::setVelocity(const Vector &velocity)
{
    this->velocity = velocity;
}

void MovingObject::setAcceleration(const Vector &acceleration)
{
    this->acceleration = acceleration;
}

Vector MovingObject::calculateAcceleration(std::list<FixedObject> fixedObjects) const
{
    Vector gravity(0, 0);
    for (auto fixedObject : fixedObjects)
    {
        Vector distance = toVector(fixedObject.getCenterPoint() - position);
        double distanceModule = distance.getLength();
        double gravityModule = fixedObject.getMass() / (distanceModule * distanceModule);
        gravity += distance.getUnitVector() * gravityModule * G * 30;
    }
    return gravity;
}

Circle MovingObject::getCollisionBox() const
{
    return collisionBox;
}

void MovingObject::setCollisionBox(const Circle &collisionBox)
{
    this->collisionBox = collisionBox;
}

double MovingObject::getMass() const
{
    return mass;
}

void MovingObject::setMass(double mass)
{
    this->mass = mass;
}