#include <iostream>

#include "../../foundation_class.cpp"


using namespace std;

typedef int Watt;
typedef int Currency;

// class IteratorOutOfBounds : public exception {};
/**
 * This is abstract class
 * There is no need to implement abstract class
 * It's implemented by it's sub class
 */
template <class Item>
class Iterator {
public:
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual Item CurrentItem() const = 0;
};

template <class Item>
class ListIterator : public Iterator<Item> {
public:
    ListIterator(const List<Item>* aList);
    virtual void First();
    virtual void Next();
    virtual bool IsDone() const;
    virtual Item CurrentItem() const;
private:
    const List<Item>* _list;
    long _current;
};

template <class Item>
ListIterator<Item>::ListIterator (const List<Item>* aList) : _list(aList), _current(0) {};

template <class Item>
void ListIterator<Item>::First() {
    _current = 0;
};

template <class Item>
void ListIterator<Item>::Next() {
    _current++;
};

template <class Item>
bool ListIterator<Item>::IsDone () const {
    return _current >= _list->Count();
};

template <class Item>
Item ListIterator<Item>::CurrentItem () const {
    if (IsDone()) {
        // throw IteratorOutOfBounds;
        throw std::range_error("AddPositiveIntege");
    }
    std::cout << "itrator" << _current << "total:" << _list->Count() << std::endl;
    return _list->Get(_current);
}

class Equipment {
public:
    const char* Name() const
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
    virtual Iterator<Equipment>* CreateIterator() {};
protected:
    Equipment(const char* n) : _name(n) {};
private:
    const char* _name;
};

class CompositeEquipment: public Equipment {
public:
    // virtual ~CompositeEquipment();

    // virtual Watt Power();
    virtual Currency NetPrice();
    // virtual Currency DiscountPrice();

    virtual void Add(Equipment*);
    virtual void Remove(Equipment*);
    virtual Iterator<Equipment>* CreateIterator();

protected:
    CompositeEquipment(const char* name) : Equipment(name) {
        _equipment = new List<Equipment>;
    };
private:
    List<Equipment>* _equipment = nullptr;
};

Iterator<Equipment>* CompositeEquipment::CreateIterator() {
    return new ListIterator<Equipment>(_equipment);
};

void CompositeEquipment::Add(Equipment * item){
    // _equipment->Append(item);
    // std::cout <<  Name() << " add -> " << item->Name() << std::endl;
    _equipment->Append(*item);
}
void CompositeEquipment::Remove(Equipment* item) {

}


Currency CompositeEquipment::NetPrice() {
    Iterator<Equipment>* i = CreateIterator();
    Currency total = 0;

    for (i->First(); !i->IsDone(); i->Next()) {
        Equipment item = i->CurrentItem();
        std::cout << "name: " << item.Name() << " price:" << item.NetPrice() << std::endl;
        total += item.NetPrice();
    }
    delete i;
    return total;
}

/*
 * Chassis 底盘、底架
 */
class Chassis : public CompositeEquipment {
public:
    Chassis(const char* name) : CompositeEquipment(name) {};
    // virtual ~Chassis();
/*
*/
    // virtual Watt Power();
    // virtual Currency NetPrice();
    // virtual Currency DiscountPrice();
};

// Cabinet 机箱
class Cabinet  : public CompositeEquipment {
public:
    Cabinet(const char* name) : CompositeEquipment(name) {};
};
class Bus  : public CompositeEquipment {
public:
    Bus(const char* name) : CompositeEquipment(name) {};
};
class Card  : public Equipment {
public:
    Card(const char* name) : Equipment(name) {};
};


class FloppyDisk : public Equipment {
public:
    FloppyDisk(const char* name) : Equipment(name) {};
    // virtual ~FloppyDisk();
/*
*/
    // virtual Watt Power();
    // virtual Currency NetPrice();
    // virtual Currency DiscountPrice();
};

int main() {
    // CompositeEquipment* e = new CompositeEquipment("mother_board");
    // cabinet 机箱
    Cabinet* cabinet = new Cabinet("PC Cabinet");
    // chasis 底盘
    Chassis* chassis = new Chassis("PC Chassis");
    /*
    */
    cabinet->Add(chassis);

    Bus* bus = new Bus("MCA Bus");
    bus->Add(new Card("16Mbs Token Ring"));

    FloppyDisk* floppydisk = new FloppyDisk("3.5in Floppy");

    chassis->Add(bus);
    chassis->Add(floppydisk);

    cout << "The net price is " << std::endl;
    cout << chassis->NetPrice() << endl;
}
