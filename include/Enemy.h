#ifndef ENEMY_H
#define ENEMY_H

#include "FixedObject.h"
#include "Point.h"
#include "Vector.h"
#include "Bitmap.h"
class Enemy
{
public:
    Enemy(double angle_speed, double angle, FixedObject base_star, double radius, double collision_radius);
    //获取当前位置
    Point getPosition();
    //获取环游半径
    double getRadius() const;
    //获取围绕星体角度
    double getAngle() const;
    //更新角度
    void updateAngle(double time);
    //获取围绕星体角速度
    double getAngleSpeed() const;
    //获取围绕星体
    FixedObject getBaseStar() const;
    //设置围绕星体
    void setBaseStar(FixedObject base_star);
    //设置围绕星体角度
    void setAngle(double angle);
    //设置围绕星体角速度
    void setAngleSpeed(double angle_speed);
    //设置环游半径
    void setRadius(double radius);
    //获取碰撞半径
    double getCollisionRadius() const;
    //设置碰撞半径
    void setCollisionRadius(double collision_radius);
    //获取敌机贴图
    Bitmap getBitmap();
private:
    //围绕星体角速度
    double angle_speed;
    //当前围绕星体角度
    double angle;
    //围绕星体
    FixedObject base_star;
    //环游半径
    double radius;
    //碰撞半径
    double collision_radius;
};

#endif // ENEMY_H
