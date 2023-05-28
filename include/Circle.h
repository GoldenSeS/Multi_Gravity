#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

class Circle
{
public:
    Circle(Point centerPoint, double radius);
    
    double getRadius() const;
    Point getCenterPoint() const;
    void setRadius(double radius);
    void setCenterPoint(Point centerPoint);

private:
    Point center;
    double radius;
};

#endif // CIRCLE_H
