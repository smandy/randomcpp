#include <iostream>

using namespace std;

class Polygon {
protected:
    int width;
    int height;

    Polygon(int width, int height);
    
    virtual int area() const = 0;

    virtual string str() const = 0;

    friend ostream& operator<<( ostream &os, Polygon &x);
};


class Square : public Polygon {
public:
    Square(int x);

    string str() const override;
    
    int area() const override;
};


class Triangle : public Polygon {
public:
    Triangle(int x, int y);

    int area() const override;

    string str() const override;
};
