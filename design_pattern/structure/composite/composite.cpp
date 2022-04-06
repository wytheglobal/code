#include <iostream>
#include <iterator>

using namespace std;

typedef int Watt;
typedef int Currency;

template <class Item>
class Iterator {
public:
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual Item Currentltem() const = 0;
};

class Equipment {
public:
    const char* Name()
        { return _name; };
    virtual Watt Power()
        {  return 10; };
    virtual Currency NetPrice()
        { return 100; };
    virtual Currency DiscountPrice()
        { return 20; };

    virtual void Add(Equipment*)
        { cout << "add equipment" << endl ;  };
    virtual void Remove(Equipment*)
        { cout << "Remove equipment" << endl ;  };
    virtual Iterator<Equipment*>* Createlterator()
        { return Iterator; };
// protected:
    Equipment(const char* n) : _name(n) {};
private:
    const char* _name;
};


int main() {
    Equipment* e = new Equipment("hello");
}
