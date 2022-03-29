#include <iostream>
#include "defs.cpp"
using namespace std;

class MazeGame {
public:
    // MazeGame() {};
    Maze* CreateMaze();

    // factory methods:
    virtual Maze* MakeMaze() const
        { return new Maze; }
    virtual Room* MakeRoom(int n) const
        { return new Room(n); }
    virtual Wall* MakeWall() const
        { return new Wall; }
    virtual Door* MakeDoor(Room* rl, Room* r2) const
        { return new Door(rl, r2); }
};

class BombedMazeGame : public MazeGame {
public:
    virtual Wall* MakeWall() const
        { return new BombedWall; }
    virtual Room* MakeRoom(int n) const
        { return new RoomWithABomb(n); }
};

Maze* MazeGame::CreateMaze () {
    Maze* aMaze = MakeMaze ();

    Room* r1 = MakeRoom (1);
    Room* r2 = MakeRoom(2);

    Door* theDoor = MakeDoor(r1, r2);

    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);

    r1->SetSide(North, MakeWall());
    r1->SetSide(East, theDoor);
    r1->SetSide(South, MakeWall());
    r1->SetSide(West, MakeWall());

    r2->SetSide(North, MakeWall());
    r2->SetSide(East, MakeWall());
    r2->SetSide(South, MakeWall());
    r2->SetSide(West, theDoor);

    return aMaze;
};



int main() {
    MazeGame game;

    Maze* aMaze = game.CreateMaze();

    BombedMazeGame bombedGame;
    Maze* bMaze = bombedGame.CreateMaze();
    return 0;
}
