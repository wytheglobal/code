// Your First C++ Program

#include <iostream>
#include "defs.cpp"

class MazeFactory {
public:
    virtual Maze* MakeMaze() const
        { return new Maze; }
    virtual Wall* MakeWall() const
        { return new Wall; }
    virtual Room* MakeRoom(int n) const
        { return new Room(n); }
    virtual Door* MakeDoor(Room* r1, Room* r2) const
        { return new Door(r1, r2); }
};

class BombedMazeFactory : public MazeFactory {
    virtual Wall* MakeWall() const
        { return new BombedWall; }
    virtual Room* MakeRoom(int n) const
        { return new RoomWithABomb(n); }
};


class MazeGame {
public:
    Maze* CreateMaze(MazeFactory&);
};

Maze* MazeGame::CreateMaze(MazeFactory& factory) {
    Maze* aMaze = factory.MakeMaze();
    Room* r1 = factory.MakeRoom(1);
    Room* r2 = factory.MakeRoom(2);

    Door* theDoor = factory.MakeDoor(r1, r2);

    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);

    r1->SetSide(North, factory.MakeWall());
    r1->SetSide(East, theDoor);
    r1->SetSide(South, factory.MakeWall());
    r1->SetSide(West, factory.MakeWall());

    r2->SetSide(North, factory.MakeWall());
    r2->SetSide(East, factory.MakeWall());
    r2->SetSide(South, factory.MakeWall());
    r2->SetSide(West, theDoor);

    return aMaze;
};


int main() {
    MazeGame game;
    MazeFactory factory;
    BombedMazeFactory bFactory;
    Maze* aMaze = game.CreateMaze(factory);
    Maze* bMaze = game.CreateMaze(bFactory);
    std::cout << "Hello Wor1d!" << std::endl;
    return 0;
}

// game.CreateMaze();

