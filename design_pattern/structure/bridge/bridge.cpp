#include <iostream>

struct Point
{
    int x;
    int y;
};
class View {
public:
    virtual void Draw()
        { std::cout << "drow some thing on view" << std::endl; };
};

// window implementation
class WindowImp {
public:
    virtual void drawReact(int, int, int, int) = 0;
};

// window abstraction
class Window {
public:
    // requests handled by window
    virtual void open()
        { std::cout << "window opend" << std::endl; };

    // requests forwarded to implementation
    virtual void drawReact(Point&, Point&);

protected:
    WindowImp* GetWindowImp();
    View* GetView();

private:
    WindowImp* _imp = 0;
    View* _view = 0;
};


class XWindowImp : public WindowImp {
public:
    virtual void drawReact(int x, int y, int width, int height)
    {
        std::cout << "Xwindow drawReact: (" << x << "," << y << ")";
        std::cout << "width: " << width << ", height: " << height << std::endl;
    };
};

class PMWindowImp : public WindowImp {
public:
    virtual void drawReact(int x, int y, int width, int height)
    {
        std::cout << "PMwindow drawReact: (" << x << "," << y << ")";
        std::cout << "width: " << width << ", height: " << height << std::endl;
    };
};


WindowImp* Window::GetWindowImp() {
    // TODO abstract factory to return different Windou instance;
    if (_imp == 0) {
        // TEST
        _imp = new PMWindowImp();
    }
    return _imp;
};
View* Window::GetView() {
    if (_view == 0) {
        _view = new View;
    }
    return _view;
};
void Window::drawReact(Point& topLeft, Point& bottomRight) {
    WindowImp* imp = GetWindowImp();
    imp->drawReact(topLeft.x, topLeft.y, bottomRight.x - topLeft.x, bottomRight.y - topLeft.y);
}

class ApplicationWindow : public Window {
public:
    // use window abstraciton's method
    virtual void DrawContents()
    {
        View* view = GetView();
        if (view != 0 ) {
            view->Draw();
        }
    };
};


class IconWindow : public Window {
public:
    virtual void DrawContents()
    {
        WindowImp* imp = GetWindowImp();
        if (imp != 0) {
            imp->drawReact(30, 30, 300, 300);
        }
    }
};


int main() {
    // client code, platform-independent
    ApplicationWindow appW;
    appW.DrawContents();

    Point p1 = {12, 12};
    Point p2 = { 100, 122 };
    appW.drawReact(p1, p2);

    IconWindow iconW;
    iconW.DrawContents();
};
