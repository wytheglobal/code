#include <iostream>
#include "defs.cpp"
using namespace std;


class MazeBuilder {
public:
    virtual void BuildMaze() {}
    virtual void BuildRoom(int room) {}
    virtual void BuildDoor(int roomFrom, int roomTo) {}

    virtual Maze* GetMaze() { return 0; }

protected:
    MazeBuilder() {};
};

class StandardMazeBuilder : public MazeBuilder {
public:
    StandardMazeBuilder();
    virtual void BuildMaze();
    virtual void BuildRoom(int);
    virtual void BuildDoor(int, int);

    virtual Maze* GetMaze ();

private:
    Direction CommonWall(Room*, Room*);
    Maze* _currentMaze;
};

StandardMazeBuilder::StandardMazeBuilder () {
    _currentMaze = 0;
}
void StandardMazeBuilder::BuildMaze () {
    _currentMaze = new Maze;
}
Maze* StandardMazeBuilder::GetMaze () {
    return _currentMaze;
}
void StandardMazeBuilder::BuildRoom(int n) {
    if (!_currentMaze->RoomNo(n)) {
        Room* room = new Room(n);
        _currentMaze->AddRoom(room);

        room->SetSide(North, new Wall);
        room->SetSide(South, new Wall);
        room->SetSide(East, new Wall);
        room->SetSide(West, new Wall);
    }
}
void StandardMazeBuilder::BuildDoor (int n1, int n2) {
    Room* r1 = _currentMaze->RoomNo(n1);
    Room* r2 = _currentMaze->RoomNo(n2);

    Door* d = new Door(r1, r2);

    r1->SetSide(CommonWall(r1,r2), d);
    r2->SetSide(CommonWall(r2,r1), d);
}
Direction StandardMazeBuilder::CommonWall(Room* r1, Room* r2) {
    return West;
}

class MazeGame {
public:
    MazeGame();
    Maze* CreateMaze(MazeBuilder&);

private:
    // string _date;
};

MazeGame::MazeGame() {
    // _date = "20220428";
}

Maze* MazeGame::CreateMaze(MazeBuilder & builder) {
    builder.BuildMaze();

    builder.BuildRoom(1);
    builder.BuildRoom(2);

    builder.BuildDoor(1, 2);

    return builder.GetMaze();
}

int main() {
    // Maze* maze;
    MazeGame game;
    StandardMazeBuilder builder;

    game.CreateMaze(builder);
    Maze* maze = builder.GetMaze();
    cout << "Hello Wor1d!" << endl;
    return 0;
}
