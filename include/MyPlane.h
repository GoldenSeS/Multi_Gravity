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
    // �ɻ�����
    void accelerate();
    // �ɻ�����
    void decelerate();
    // �ɻ���ת
    void turnLeft();
    // �ɻ���ת
    void turnRight();
    // ��ȡ�ɻ������Զ���
    double getLinearPower() const;
    // ��ȡ�ɻ��ĽǶ���
    double getAngularPower() const;
    // ���÷ɻ������Զ���
    void setLinearPower(double LinearPower);
    // ���÷ɻ��ĽǶ���
    void setAngularPower(double AngularPower);

    // ��ȡ�ɻ��ĽǶ�
    double getAzimuthAngle() const;
    // ��ȡ�ɻ��Ľ��ٶȴ�С
    double getAngularVelocity() const;
    // ��ȡ�ɻ��Ľ�����
    Vector getAngularVector() const;

    // ���÷ɻ��ĽǶ�
    void setAzimuthAngle(double AzimuthAngle);
    // ���÷ɻ��Ľ��ٶȴ�С
    void setAngularVelocity(double AngularVelocity);

    // ���·ɻ���λ������
    void updatePosition(double deltaTime);
    // ���·ɻ����ٶ�ʸ��
    void updateVelocity(double deltaTime);
    // ���·ɻ��ļ��ٶ�ʸ��
    void updateAcceleration(std::list<FixedObject> fixedObjects);
    // ���·ɻ��ĽǶ�
    void updateAzimuthAngle(double deltaTime);

    // ���·ɻ�������״̬
    void updateSituations(double deltaTime, std::list<FixedObject> fixedObjects);

    //���ص��������
    MyPlane &operator=(const MyPlane &plane);
    // ���Ʒɻ�
    Bitmap draw() const;
private:
    double azimuthAngle;
    double AngularVelocity;
    double LinearPower;  // �ɻ������Զ��������������ɻ����Լ��ٶȵĴ�С
    double AngularPower; // �ɻ��ĽǶ��������������ɻ��Ǽ��ٶȵĴ�С
};

#endif // MYPLANE_H
