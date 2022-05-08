const long DEFAULT_LIST_CAPACITY = 200;

/*
*/
//typedef int bool;
//const int true = 1;
//const int false = 0;
/*
template <class Item>
class List {
public:
    List(long size = DEFAULT_LIST_CAPACITY);
    List(List&);
    ~List();
    List& operator=(const List&);

    long Count() const;
    Item& Get(long index) const;
    Item& First() const;
    Item& Last() const;
    bool Includes(const Item&) const;

    void Append(const Item&);
    void Prepend(const Item&);

    void Remove(const Item&);
    void RemoveLast();
    void RemoveFirst();
    void RemoveAll();

    Item& Top() const;
    void Push(const Item&);
    Item& Pop();
};
*/
template <class Item>
class Node {
public:
    Node(const Item item) : data(item) {};
    Node *next;
    const Item data;
};

// TODO
// why struct doesn't work in my case
// https://gist.github.com/unreadable/fcf83725fb80a6790a43426940644523
template <class Item>
class List {
public:
    List();
    const Item& Get(long index) const;
    void Append(const Item);

    long Count() const;
private:
    Node<Item> *head;
    Node<Item> *tail;
    long _count;
};

template <class Item>
List<Item>::List() {
    head = NULL;
    tail = NULL;
    _count = 0;
};

template <class Item>
const Item& List<Item>::Get(long index) const {
    Node<Item> *ptr = head;
    while (index > 0) {
        index--;
        ptr = ptr->next;
    }
    const Item& item = ptr->data;
    return item;
};

template <class Item>
void List<Item>::Append(const Item item) {
    Node<Item> *n = new Node<Item>(item);
    std::cout << _count << std::endl;
    if (_count == 0) {
        n->next = NULL;
        head = n;
        tail = n;
    } else {
        tail->next = n;
        tail = n;
    }
    _count++;
};

template <class Item>
long List<Item>::Count() const {
    return _count;
};


/*
template <typename T>
struct Node {
  T& data;
  Node *next;
};

template <typename T> class List{
private:
    Node<T> *head;
public:
    List(){
        head = NULL;
    }

    void push(T& val){
        Node<T> *n = new Node<T>();
        n->data = val;
        n->next = head;
        head = n;
    }

    T pop(){
      if(head) {
        T p = head->data;
        head = head->next;
        return p;
      }
    }

    bool search(T val) {
      Node<T> *temp = head;
      while(temp->next) {
        if(temp->data == val) return true;
        else temp = temp->next;
      }
      delete temp;
      return false;
    }
};
*/
