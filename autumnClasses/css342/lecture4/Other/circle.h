#ifndef CIRCLE_H_
#define CIRCLE_H_
typedef struct 
{
    int x,y;
} Point;
class Circle
{
public:
    Circle();
    Circle(double radius);
    Circle(double radius, Point center);

    bool setCenter(const Point center);
    bool SetRadius(double r);

    Point center() const;
    double radius() const;

    bool ContainsPoint(const Point test_for) const;

    double Area() const;
    double Circumference() const;

private:
    Point center;
    double radius_;
};
#endif