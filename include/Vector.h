#ifndef VECTOR_H
#define VECTOR_H

#include "Point.h"
#include <cmath>
class Vector
{
public:
    friend Vector toVector(const Point &point);
    Vector(double xComp, double yComp);
    // ��ȡ������x����
    double getXComponent() const;
    // ��ȡ������y����
    double getYComponent() const;
    // ��ȡ������ģ
    double getLength() const;
    // ��ȡ�����ĵ�λ����
    Vector getUnitVector() const;
    // �ڲ��ı䷽�������¸ı�������ģ
    void setLength(double length);
    // ��������ת
    Vector rotate(double angle) const;

    Vector operator+(const Vector &otherVector) const;
    Vector operator-(const Vector &otherVector) const;
    Vector operator*(double scalar) const;
    Vector operator/(double scalar) const;
    Vector &operator+=(const Vector &otherVector);
    Vector &operator-=(const Vector &otherVector);
    Vector &operator*=(double scalar);
    Vector &operator/=(double scalar);
    // ������ת��Ϊ��
    Point toPoint() const;

private:
    double x; // ������x����
    double y; // ������y����
};

// ����ת��Ϊ����
Vector toVector(const Point &point);

#endif // VECTOR_H
