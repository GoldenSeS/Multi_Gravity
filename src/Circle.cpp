#include "Circle.h"
#include <cmath>

Circle::Circle(Point centerPoint, double radius) : center(centerPoint), radius(radius) {}

double Circle::getRadius() const {
    return radius;
}

Point Circle::getCenterPoint() const {
    return center;
}

void Circle::setRadius(double radius) {
    this->radius = radius;
}

void Circle::setCenterPoint(Point centerPoint) {
    center = centerPoint;
}
