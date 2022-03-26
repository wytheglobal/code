#include <vector>

enum Direction {North, South, East, West};

class MapSite { 
public:
    virtual void Enter() = 0;
};

class Room : public MapSite { 
public:
    Room(int roomNo);

    MapSite* GetSide(Direction) const; 
    void SetSide(Direction, MapSite*);

    virtual void Enter();

private:
    MapSite* _sides[4]; 
    int _roomNumber;
};
Room::Room(int roomNo) {
    _roomNumber = roomNo;
};
void Room::SetSide(Direction direction, MapSite* mapSite) {
    _sides[direction] = mapSite;
};
void Room::Enter() {

};

class Wall: public MapSite {
public:
    Wall();

    virtual void Enter();
}; 
Wall::Wall(){

};
void Wall::Enter(){

};

class Door : public MapSite {
public:
    Door(Room* = 0, Room* = 0);

    virtual void Enter(); 
    Room* OtherSideFrom(Room*);

private:
    Room* _room1; 
    Room* _room2; 
    bool _isOpen; 
};
Door::Door(Room* r1, Room* r2) {
    _room1 = r1;
    _room2 = r2;
};
void Door::Enter() {

};

class Maze { 
public:

    Maze();

    void AddRoom(Room* ) ; 
    // what's this const stand for 
    // https://stackoverflow.com/questions/751681/meaning-of-const-last-in-a-function-declaration-of-a-class
    Room* RoomNo(int) const; 

private:
    // Room* _rooms[100];
    std::vector< Room* > _rooms;
};  

Maze::Maze() {
};
Room* Maze::RoomNo(int rId) const{
    //can have other data types instead of int but must same datatype as item 
    for (Room* room : _rooms) {
        // if (room->_roomNumber == rId) {
        //     return room;
        // }
    }
};
void Maze::AddRoom(Room* room){
    _rooms.push_back(room);
};


