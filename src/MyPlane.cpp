#include "MyPlane.h"
#include <cmath>

MyPlane::MyPlane(const Point &position, const Vector &velocity, const Vector &acceleration, double azimuthAngle, double AngularVelocity, double LinearPower, double AngularPower)
    : MovingObject(position, velocity, acceleration, 1), azimuthAngle(azimuthAngle), AngularVelocity(AngularVelocity), LinearPower(LinearPower), AngularPower(AngularPower)
{
}

void MyPlane::accelerate()
{
    Vector addVelocity = getAngularVector() * LinearPower;
    this->setVelocity(Vector(this->getVelocity() + Vector(addVelocity.getXComponent(), addVelocity.getYComponent()*0.5)));
}

void MyPlane::decelerate()
{
    this->setVelocity(this->getVelocity() * 0.8);
}

void MyPlane::turnLeft()
{
    this->AngularVelocity -= AngularPower;
}

void MyPlane::turnRight()
{
    this->AngularVelocity += AngularPower;
}

double MyPlane::getLinearPower() const
{
    return LinearPower;
}

double MyPlane::getAngularPower() const
{
    return AngularPower;
}

void MyPlane::setLinearPower(double LinearPower)
{
    this->LinearPower = LinearPower;
}

void MyPlane::setAngularPower(double AngularPower)
{
    this->AngularPower = AngularPower;
}

double MyPlane::getAzimuthAngle() const
{
    return azimuthAngle;
}

double MyPlane::getAngularVelocity() const
{
    return AngularVelocity;
}

Vector MyPlane::getAngularVector() const
{
    return Vector(cos(azimuthAngle), sin(azimuthAngle));
}

void MyPlane::setAzimuthAngle(double azimuthAngle)
{
    this->azimuthAngle = azimuthAngle;
}

void MyPlane::setAngularVelocity(double AngularVelocity)
{
    this->AngularVelocity = AngularVelocity;
}

void MyPlane::updatePosition(double deltaTime)
{
    Point tem = Vector(this->getVelocity() * deltaTime).toPoint();
    this->setPosition(Point(this->getPosition() + tem));
    this->setCollisionBox(Circle(this->getPosition(),this->getCollisionBox().getRadius()));
}

void MyPlane::updateVelocity(double deltaTime)
{
    this->setVelocity(Vector(this->getVelocity() + this->getAcceleration() * deltaTime));
}

void MyPlane::updateAcceleration(std::list<FixedObject> fixedObjects)
{
    this->setAcceleration(this->calculateAcceleration(fixedObjects));
}

void MyPlane::updateAzimuthAngle(double deltaTime)
{
    const double Epsilon = 0.001;
    this->azimuthAngle += this->AngularVelocity * deltaTime;

    if (fabs(this->AngularVelocity) < Epsilon) // ������ٶ�С������С��Epsilon������Ϊ���ٶ�Ϊ0
    {
        this->AngularVelocity = 0;
        return;
    }
    else if (this->AngularVelocity > 0) // Ĭ�Ͻ��ٶ�����Ϊ0.5
    {
        this->AngularVelocity -= AngularPower * 0.5;
    }
    else
    {
        this->AngularVelocity += AngularPower * 0.5;
    }
    if (this->azimuthAngle > 2 * PI)
        this->azimuthAngle -= 2 * PI;
    if (this->azimuthAngle < 0)
        this->azimuthAngle += 2 * PI;
}

void MyPlane::updateSituations(double deltaTime, std::list<FixedObject> fixedObjects)
{
    updatePosition(deltaTime);
    updateVelocity(deltaTime);
    this->setAcceleration(this->calculateAcceleration(fixedObjects));
    updateAzimuthAngle(deltaTime);
}

MyPlane &MyPlane::operator=(const MyPlane &plane)
{
    this->setPosition(plane.getPosition());
    this->setVelocity(plane.getVelocity());
    this->setAcceleration(plane.getAcceleration());
    this->setAzimuthAngle(plane.getAzimuthAngle());
    this->setAngularVelocity(plane.getAngularVelocity());
    this->setLinearPower(plane.getLinearPower());
    this->setAngularPower(plane.getAngularPower());
    this->setCollisionBox(plane.getCollisionBox());
    return *this;
}

Bitmap MyPlane::draw() const
{
    // �ַ���ƴ�ӣ���ȡ�ɻ���ǰ�Ƕȵ�ͼƬ
    std::string picture_str = "PlanePicture2/";
    int picture_num = int(getAzimuthAngle() * PI_ * 6 + PI * 0.083);
    if (picture_num > 11)
    {
        picture_num = 0;
    }
    std::string angle_str = std::to_string(picture_num);
    picture_str += angle_str;
    picture_str += ".txt";
    return Bitmap(picture_str);
}
