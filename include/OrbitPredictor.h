#ifndef ORBITPREDICTOR_H
#define ORBITPREDICTOR_H

#include "MyPlane.h"
#include "Point.h"
#include "Vector.h"
#include <list>
#include "Bitmap.h"
#include "ScreenManager.h"
#include "FixedObject.h"
#include "Bullet.h"
class OrbitPredictor
{
public:
    OrbitPredictor();
    void orbit_predict(MyPlane plane,int step,std::list<FixedObject> fixedObjects);
    void bullet_predict(MyPlane plane,int step,std::list<FixedObject> fixedObjects);
    std::list<Point> getOrbitList();
private:
    MyPlane ghostPlane;
    std::list<Point> orbit;
};

#endif // ORBITPREDICTOR_H