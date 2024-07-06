

#include "polygon.h"

Polygon::Polygon(int width, int height) : width(width), height(height) {}

ostream& operator<<(ostream& os, Polygon& x)
{
    os << x.str() << "(" << x.width << "," << x.height << ") Area=" << x.area();
    return os;
};

Square::Square(int x) : Polygon(x, x){};

string Square::str() const { return "Square"; }

int Square::area() const
{
    return width * height;
}

Triangle::Triangle(int x, int y) : Polygon(x, y){};

int Triangle::area() const
{
    return (width * height) / 2;
};

string Triangle::str() const { return "Triangle"; }

int main()
{
    Square square(10);
    Triangle triangle(10, 2);

    cout << square << endl;
    cout << triangle << endl;
};
