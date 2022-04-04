#include <iostream>

class People {
public:
    virtual void greeting()
        { std::cout << "hello world" << std::endl; };
};

int main() {
    People p;
    p.greeting();
}
