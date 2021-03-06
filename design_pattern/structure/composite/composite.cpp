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
    ListIterator(const List<Item> aList);
    virtual void First();
    virtual void Next();
    virtual bool IsDone() const;
    virtual Item CurrentItem() const;
private:
    const List<Item> _list;
    long _current;
};

template <class Item>
ListIterator<Item>::ListIterator (const List<Item> aList) : _list(aList), _current(0) {};

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
    return _current >= _list.Count();
};

template <class Item>
Item ListIterator<Item>::CurrentItem () const {
    if (IsDone()) {
        std::cout << "itrator CurrentItem done" << std::endl;
        // throw IteratorOutOfBounds;
        throw std::range_error("AddPositiveIntege");
    }
    std::cout << "itrator index" << _current << " total count:" << _list.Count() << std::endl;

    return _list.Get(_current);
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
    virtual Iterator<Equipment*>* CreateIterator() {};
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
    virtual Iterator<Equipment*>* CreateIterator();

protected:
    CompositeEquipment(const char* name) : Equipment(name) {
        // _equipment = new List<Equipment*>;
        List<Equipment*> _equipment;
    };
private:
    List<Equipment*> _equipment;
};

Iterator<Equipment*>* CompositeEquipment::CreateIterator() {
    return new ListIterator<Equipment*>(_equipment);
};

void CompositeEquipment::Add(Equipment * item){
    // _equipment->Append(item);
    std::cout <<  Name() << " add -> " << item->Name() << std::endl;
    _equipment.Append(item);
}
void CompositeEquipment::Remove(Equipment* item) {

}


Currency CompositeEquipment::NetPrice() {
    Iterator<Equipment*>* i = CreateIterator();
    Currency total = 0;

    std::cout << "CompositeEquipment::NetPrice loop >>>>" << std::endl;
    for (i->First(); !i->IsDone(); i->Next()) {
        Equipment* item = i->CurrentItem();
        std::cout << "name: " << item->Name() << std::endl;
        // https://stackoverflow.com/questions/21978512/c-casting-from-parent-to-child-after-passing-as-a-function
        CompositeEquipment* compositeItemPtr = dynamic_cast<CompositeEquipment*>(item);
        if (compositeItemPtr) {
            Currency p1 = compositeItemPtr->NetPrice();
            std::cout << "CompositeEquipment converted " << total << '|' << p1 << std::endl;
            total += p1;
        } else {
            Currency p2 = item->NetPrice();
            std::cout << "CompositeEquipment converted failed" << total << '|' << p2 << std::endl;
            total += p2;
        }
    }
    std::cout << "CompositeEquipment::NetPrice loop <<<<" << total << std::endl;
    delete i;
    return total;
}

/*
 * Chassis ???????????????
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

// Cabinet ??????
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
    // cabinet ?????? CompositeEquipment
    Cabinet* cabinet = new Cabinet("PC Cabinet");
    // chasis ?????? CompositeEquipment
    Chassis* chassis = new Chassis("PC Chassis");
    /*
    */
    cabinet->Add(chassis);

    // bus CompositeEquipment
    Bus* bus = new Bus("MCA Bus");
    Card* card = new Card("16Mbs Token Ring");

    bus->Add(card);
    chassis->Add(bus);

    FloppyDisk* floppydisk = new FloppyDisk("3.5in Floppy");
    chassis->Add(floppydisk);

    cout << "The net price is " << std::endl;
    cout << cabinet->NetPrice() << endl;
}
