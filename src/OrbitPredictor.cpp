#include "OrbitPredictor.h"

OrbitPredictor::OrbitPredictor():ghostPlane(Point(0,0),Vector(0,0),Vector(0,0),0,0,0,0)
{
}

void OrbitPredictor::orbit_predict(MyPlane plane, int step, std::list<FixedObject> fixedObjects)
{
    double deltaTime = 0.05;
    orbit.clear();
    ghostPlane = plane;
    for (int i = 0; i < step; i++)
    {
        ghostPlane.updatePosition(deltaTime);
        ghostPlane.updateVelocity(deltaTime);
        ghostPlane.setAcceleration(ghostPlane.calculateAcceleration(fixedObjects));
        orbit.push_back(ghostPlane.getPosition()-plane.getPosition()+Point(SCREEN_WIDTH*0.5,SCREEN_HEIGHT*0.5));
    }
    ghostPlane = plane;
    deltaTime = -0.05;
    for (int i = 0; i < step*0.5; i++)
    {
        ghostPlane.updatePosition(deltaTime);
        ghostPlane.updateVelocity(deltaTime);
        ghostPlane.setAcceleration(ghostPlane.calculateAcceleration(fixedObjects));
        orbit.push_back(ghostPlane.getPosition()-plane.getPosition()+Point(SCREEN_WIDTH*0.5,SCREEN_HEIGHT*0.5));
    }
}

void OrbitPredictor::bullet_predict(MyPlane plane, int step, std::list<FixedObject> fixedObjects)
{
    double deltaTime = 0.016;
    orbit.clear();
    ghostPlane = MyPlane(plane.getPosition(),plane.getVelocity() + plane.getAngularVector().getUnitVector() * BULLET_SPEED,plane.getAcceleration(),0,0,0,0);
    for(int i=0;i<step;i++)
    {
        ghostPlane.updatePosition(deltaTime);
        ghostPlane.updateVelocity(deltaTime);
        ghostPlane.setAcceleration(ghostPlane.calculateAcceleration(fixedObjects));
        orbit.push_back(ghostPlane.getPosition()-plane.getPosition()+Point(SCREEN_WIDTH*0.5,SCREEN_HEIGHT*0.5));
    }
}

std::list<Point> OrbitPredictor::getOrbitList()
{
    return orbit;
}