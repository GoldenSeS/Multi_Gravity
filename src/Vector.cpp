#include "Vector.h"
#include <cmath>

Vector::Vector(double xComp, double yComp) : x(xComp), y(yComp) {}

double Vector::getXComponent() const {
    return x;
}

double Vector::getYComponent() const {
    return y;
}

double Vector::getLength() const {
    return sqrt(pow(x, 2) + pow(y, 2));
}

Vector Vector::getUnitVector() const
{
    double length = getLength();
    return Vector(x / length, y / length);
}

void Vector::setLength(double length)
{
    double currentLength = getLength();
    x *= length / currentLength;
    y *= length / currentLength;
}

Vector Vector::rotate(double angle) const
{
    double xComp = x * cos(angle) - y * sin(angle);
    double yComp = x * sin(angle) + y * cos(angle);
    return Vector(xComp, yComp);
}

Vector Vector::operator+(const Vector& otherVector) const {
    return Vector(x + otherVector.x, y + otherVector.y);
}

Vector Vector::operator-(const Vector &otherVector) const
{
    return Vector(x - otherVector.x, y - otherVector.y);
}

Vector Vector::operator*(double scalar) const {
    return Vector(x * scalar, y * scalar);
}

Vector Vector::operator/(double scalar) const {
    return Vector(x / scalar, y / scalar);
}

Vector &Vector::operator+=(const Vector &otherVector)
{
    x += otherVector.x;
    y += otherVector.y;
    return *this;
}

Vector &Vector::operator-=(const Vector &otherVector)
{
    x -= otherVector.x;
    y -= otherVector.y;
    return *this;
}

Vector &Vector::operator*=(double scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector &Vector::operator/=(double scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

Point Vector::toPoint() const
{
    return Point(x, y);
}

Vector toVector(const Point &point)
{
    return Vector(point.getX(), point.getY());
}
