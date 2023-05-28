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
    //��ȡ��ǰλ��
    Point getPosition();
    //��ȡ���ΰ뾶
    double getRadius() const;
    //��ȡΧ������Ƕ�
    double getAngle() const;
    //���½Ƕ�
    void updateAngle(double time);
    //��ȡΧ��������ٶ�
    double getAngleSpeed() const;
    //��ȡΧ������
    FixedObject getBaseStar() const;
    //����Χ������
    void setBaseStar(FixedObject base_star);
    //����Χ������Ƕ�
    void setAngle(double angle);
    //����Χ��������ٶ�
    void setAngleSpeed(double angle_speed);
    //���û��ΰ뾶
    void setRadius(double radius);
    //��ȡ��ײ�뾶
    double getCollisionRadius() const;
    //������ײ�뾶
    void setCollisionRadius(double collision_radius);
    //��ȡ�л���ͼ
    Bitmap getBitmap();
private:
    //Χ��������ٶ�
    double angle_speed;
    //��ǰΧ������Ƕ�
    double angle;
    //Χ������
    FixedObject base_star;
    //���ΰ뾶
    double radius;
    //��ײ�뾶
    double collision_radius;
};

#endif // ENEMY_H
