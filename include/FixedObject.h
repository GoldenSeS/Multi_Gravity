#ifndef FIXEDOBJECT_H
#define FIXEDOBJECT_H

#include "Point.h"
#include "Circle.h"
#define G 9.8
class FixedObject: public Circle
{
public:
	FixedObject(Point centerPoint,double radius, double mass);

	double getMass() const;
	void setMass(double mass);

protected:
	double mass;
};

#endif // FIXOBJECT_H