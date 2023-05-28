#include "Point.h"

Point::Point(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

void Point::setX(double xCoord)
{
    x = xCoord;
}

void Point::setY(double yCoord)
{
    y = yCoord;
}

Point Point::operator+(const Point &point) const
{
    return Point(x + point.x, y + point.y);
}

Point Point::operator-(const Point &point) const
{
    return Point(x - point.x, y - point.y);
}

Point Point::operator*(double factor) const
{
    return Point(x * factor, y * factor);
}

Point Point::operator/(double factor) const
{
    return Point(x / factor, y / factor);
}

Point &Point::operator+=(const Point &point)
{
    x += point.x;
    y += point.y;
    return *this;
}

Point &Point::operator-=(const Point &point)
{
    x -= point.x;
    y -= point.y;
    return *this;
}