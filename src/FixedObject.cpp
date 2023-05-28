#include "FixedObject.h"

FixedObject::FixedObject(Point centerPoint, double radius, double mass): Circle(centerPoint, radius), mass(mass)
{
}

double FixedObject::getMass() const
{
    return mass;
}

void FixedObject::setMass(double mass)
{
    this->mass = mass;
}