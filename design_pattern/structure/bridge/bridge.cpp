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


class WindowImp {
public:
    virtual void drawReact(int, int, int, int) = 0;
protected:
    WindowImp() {};
};

class Window {
public:
    // requests handled by window
    virtual void open()
        { std::cout << "window opend" << std::endl; };
    virtual void DrawContents()
        { std::cout << "window DrawContents" << std::endl; };
    // requests forwarded to implementation
    virtual void drawReact(Point&, Point&);

protected:
    WindowImp* GetWindowImp();
    View* GetView();

private:
    WindowImp* _imp;
    View* _view;
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
    // XWindowImp* wWindowImp;
    // return wWindowImp;
    if (_imp == 0) {
        _imp = new XWindowImp;
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

/*
class ApplicationWindow : public Window {
public:
    // use window abstraciton's method
    virtual void DrawContents()
    {
        // WindowImp* imp = GetWindowImp();
        // if (imp != 0) {
        //     imp->drawReact(30, 30, 300, 300);
        // }
        View* view = GetView();
        if (view != 0 ) {
            view->Draw();
        }
    };
};
*/


class IconWindow : public Window {
public:
    //
    virtual void DrawContents()
    {
        WindowImp* imp = GetWindowImp();
        if (imp != 0) {
            imp->drawReact(30, 30, 300, 300);
        }
        // XWindowImp ximp;
        // ximp.drawReact(30, 30, 300 , 300);
    }
};


int main() {
    IconWindow iconW;
    iconW.DrawContents();

    // ApplicationWindow appW;
    // appW.DrawContents();
};
