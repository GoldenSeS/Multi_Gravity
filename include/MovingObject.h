#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include "Point.h"
#include "Vector.h"
#include "FixedObject.h"
#include <list>
#include "Circle.h"
class MovingObject
{
public:
    // �ƶ������๹�캯��
    MovingObject(const Point &position, const Vector &velocity, const Vector &acceleration,double collisionRadius);

    // ��ȡ�ƶ�������λ������
    Point getPosition() const;
    // ��ȡ�ƶ��������ٶ�ʸ��
    Vector getVelocity() const;
    // ��ȡ�ƶ���������ٶ�ʸ��
    Vector getAcceleration() const;
    
    // ��ȡ�ƶ��������ٶȴ�С
    double getSpeed() const;
    // ��ȡ�ƶ���������ٶȴ�С
    double getAccelerationModule() const;
    // �����ƶ�������λ������
    virtual void setPosition(const Point &position);
    // �����ƶ��������ٶ�ʸ��
    virtual void setVelocity(const Vector &velocity);
    // �����ƶ���������ٶ�ʸ��
    virtual void setAcceleration(const Vector &acceleration);
    // �����ƶ�������λ������
    virtual void updatePosition(double deltaTime) = 0;
    // �����ƶ��������ٶ�ʸ��
    virtual void updateVelocity(double deltaTime) = 0;
    // �����ƶ����������ܼ��ٶ�
    virtual Vector calculateAcceleration(std::list<FixedObject> fixedObjects) const;
    // ��ȡ�ƶ���������ײ��
    Circle getCollisionBox() const;
    // �����ƶ���������ײ��
    void setCollisionBox(const Circle &collisionBox);

    // �����ƶ�����������
    void setMass(double mass);
    // ��ȡ�ƶ�����������
    double getMass() const;
private:
    Point position;
    Vector velocity;
    Vector acceleration;
    Circle collisionBox;
    double mass = 10;
};

#endif // MOVINGOBJECT_H
