#ifndef MYPLANE_H
#define MYPLANE_H

#include "MovingObject.h"
#include <list>
#include "Bitmap.h"
#include "FixedObject.h"
class MyPlane : public MovingObject
{
public:
    MyPlane(const Point &position, const Vector &velocity, const Vector &acceleration, double azimuthAngle, double AngularVelocity, double LinearPower, double AngularPower);
    // 飞机加速
    void accelerate();
    // 飞机减速
    void decelerate();
    // 飞机左转
    void turnLeft();
    // 飞机右转
    void turnRight();
    // 获取飞机的线性动力
    double getLinearPower() const;
    // 获取飞机的角动力
    double getAngularPower() const;
    // 设置飞机的线性动力
    void setLinearPower(double LinearPower);
    // 设置飞机的角动力
    void setAngularPower(double AngularPower);

    // 获取飞机的角度
    double getAzimuthAngle() const;
    // 获取飞机的角速度大小
    double getAngularVelocity() const;
    // 获取飞机的角向量
    Vector getAngularVector() const;

    // 设置飞机的角度
    void setAzimuthAngle(double AzimuthAngle);
    // 设置飞机的角速度大小
    void setAngularVelocity(double AngularVelocity);

    // 更新飞机的位置坐标
    void updatePosition(double deltaTime);
    // 更新飞机的速度矢量
    void updateVelocity(double deltaTime);
    // 更新飞机的加速度矢量
    void updateAcceleration(std::list<FixedObject> fixedObjects);
    // 更新飞机的角度
    void updateAzimuthAngle(double deltaTime);

    // 更新飞机的总体状态
    void updateSituations(double deltaTime, std::list<FixedObject> fixedObjects);

    //重载等于运算符
    MyPlane &operator=(const MyPlane &plane);
    // 绘制飞机
    Bitmap draw() const;
private:
    double azimuthAngle;
    double AngularVelocity;
    double LinearPower;  // 飞机的线性动力，用来衡量飞机线性加速度的大小
    double AngularPower; // 飞机的角动力，用来衡量飞机角加速度的大小
};

#endif // MYPLANE_H
