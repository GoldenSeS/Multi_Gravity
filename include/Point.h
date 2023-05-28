#ifndef POINT_H
#define POINT_H
#define PI 3.14159
#define PI_ 0.318309
class Point {
public:
    Point(double xCoord, double yCoord);
    double getX() const;
    double getY() const;
    void setX(double xCoord);
    void setY(double yCoord);
    Point operator+(const Point& point) const;
    Point operator-(const Point& point) const;
    Point operator*(double factor) const;
    Point operator/(double factor) const;
    Point& operator+=(const Point& point);
    Point& operator-=(const Point& point);

private:
    double x;
    double y;
};

#endif // POINT_H
