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
    // 移动物体类构造函数
    MovingObject(const Point &position, const Vector &velocity, const Vector &acceleration,double collisionRadius);

    // 获取移动物体类位置坐标
    Point getPosition() const;
    // 获取移动物体类速度矢量
    Vector getVelocity() const;
    // 获取移动物体类加速度矢量
    Vector getAcceleration() const;
    
    // 获取移动物体类速度大小
    double getSpeed() const;
    // 获取移动物体类加速度大小
    double getAccelerationModule() const;
    // 设置移动物体类位置坐标
    virtual void setPosition(const Point &position);
    // 设置移动物体类速度矢量
    virtual void setVelocity(const Vector &velocity);
    // 设置移动物体类加速度矢量
    virtual void setAcceleration(const Vector &acceleration);
    // 更新移动物体类位置坐标
    virtual void updatePosition(double deltaTime) = 0;
    // 更新移动物体类速度矢量
    virtual void updateVelocity(double deltaTime) = 0;
    // 计算移动物体类所受加速度
    virtual Vector calculateAcceleration(std::list<FixedObject> fixedObjects) const;
    // 获取移动物体类碰撞盒
    Circle getCollisionBox() const;
    // 设置移动物体类碰撞盒
    void setCollisionBox(const Circle &collisionBox);

    // 设置移动物体类质量
    void setMass(double mass);
    // 获取移动物体类质量
    double getMass() const;
private:
    Point position;
    Vector velocity;
    Vector acceleration;
    Circle collisionBox;
    double mass = 10;
};

#endif // MOVINGOBJECT_H
