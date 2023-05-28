#ifndef VECTOR_H
#define VECTOR_H

#include "Point.h"
#include <cmath>
class Vector
{
public:
    friend Vector toVector(const Point &point);
    Vector(double xComp, double yComp);
    // 获取向量的x分量
    double getXComponent() const;
    // 获取向量的y分量
    double getYComponent() const;
    // 获取向量的模
    double getLength() const;
    // 获取向量的单位向量
    Vector getUnitVector() const;
    // 在不改变方向的情况下改变向量的模
    void setLength(double length);
    // 向量的旋转
    Vector rotate(double angle) const;

    Vector operator+(const Vector &otherVector) const;
    Vector operator-(const Vector &otherVector) const;
    Vector operator*(double scalar) const;
    Vector operator/(double scalar) const;
    Vector &operator+=(const Vector &otherVector);
    Vector &operator-=(const Vector &otherVector);
    Vector &operator*=(double scalar);
    Vector &operator/=(double scalar);
    // 将向量转换为点
    Point toPoint() const;

private:
    double x; // 向量的x分量
    double y; // 向量的y分量
};

// 将点转换为向量
Vector toVector(const Point &point);

#endif // VECTOR_H
