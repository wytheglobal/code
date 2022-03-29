#include <iostream>

struct Point {
    int x;
    int y;
};
class Manipulator
{
    // Static, because it's class member.
    // Constexpr, because you initialize it in class definition.
    // static constexpr char name[] = "manipulator";
public:
    Manipulator(std::string n) {
        name = n;
    }
    std::string name;
};


class Shape {
public:
    virtual void BoundingBox(Point& bottomLeft, Point& topRight) const
        { bottomLeft = { 10, 20 }; topRight = { 30, 60 }; };
    virtual Manipulator* CreateManipulator() const
        { return new Manipulator("test"); };
};

class TextView {
public:
    void GetOrigin(int& x, int& y) const
        { x = 10; y = 20; };
    void GetExtent(int& width, int& height) const
        { width = 100; height = 200; };
    virtual bool isEmpty() const
        { return false; };
};

// class adapter
class TextShape : public Shape, private TextView {
public:
    virtual void BoundingBox(Point& bottomLeft, Point& topRight) const;
    virtual bool isEmpty() const;
    virtual Manipulator* CreateManipulator() const;
};
void TextShape::BoundingBox(Point& bottomLeft, Point& topRight) const{
    int x, y, w, h;
    GetOrigin(x, y);
    GetExtent(w, h);
    bottomLeft = { x, y };
    topRight = { x + w, y + h };
};
Manipulator* TextShape::CreateManipulator() const {
    // return new Manipulator { "hello" };
    return new Manipulator("hello");
};
bool TextShape::isEmpty() const {
    return TextView::isEmpty();
}



int main() {
    TextShape textshape;
    Point bl, tp;
    textshape.BoundingBox(bl, tp);
    Manipulator* mp = textshape.CreateManipulator();

    std::cout << "hello world" << std::endl;
}
