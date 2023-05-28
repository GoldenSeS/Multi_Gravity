#include "Enemy.h"

Enemy::Enemy(double angle_speed, double angle, FixedObject base_star, double radius, double collision_radius)
    : angle_speed(angle_speed), angle(angle), base_star(base_star), radius(radius), collision_radius(collision_radius)
{
}

Point Enemy::getPosition()
{
    double tem_angle = cos(angle) * cos(angle) + 4 * sin(angle) * sin(angle);
    return base_star.getCenterPoint() + Vector(2 * radius, 0).rotate(angle).toPoint() / sqrt(tem_angle);
}

double Enemy::getRadius() const
{
    return radius;
}

double Enemy::getAngle() const
{
    return angle;
}

void Enemy::updateAngle(double time)
{
    angle += angle_speed * time * 20 / toVector(this->getPosition() - base_star.getCenterPoint()).getLength();
    if (angle < 0)
    {
        angle += 2 * PI;
    }
    if (angle > 2 * PI)
    {
        angle -= 2 * PI;
    }
}

double Enemy::getAngleSpeed() const
{
    return angle_speed;
}

FixedObject Enemy::getBaseStar() const
{
    return base_star;
}

void Enemy::setBaseStar(FixedObject base_star)
{
    this->base_star = base_star;
}

void Enemy::setAngle(double angle)
{
    this->angle = angle;
}

void Enemy::setAngleSpeed(double angle_speed)
{
    this->angle_speed = angle_speed;
}

void Enemy::setRadius(double radius)
{
    this->radius = radius;
}

double Enemy::getCollisionRadius() const
{
    return collision_radius;
}

void Enemy::setCollisionRadius(double collision_radius)
{
    this->collision_radius = collision_radius;
}

Bitmap Enemy::getBitmap()
{
    return Bitmap("enemy.txt");
}
