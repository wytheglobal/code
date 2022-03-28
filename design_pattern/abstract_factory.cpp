// Your First C++ Program

#include <iostream>
#include "defs.cpp"

class MazeGame {
public:
    MazeGame() {};

    Maze* CreateMaze();
};

Maze* MazeGame::CreateMaze() {
    Maze* aMaze = new Maze; 
    Room* r1 = new Room(1);
    Room* r2 = new Room (2);

    Door* theDoor = new Door(r1, r2);

    aMaze->AddRoom(r1); 
    aMaze->AddRoom(r2);

    r1->SetSide(North, new Wall); 
    r1->SetSide(East, theDoor); 
    r1->SetSide(South, new Wall); 
    r1->SetSide(West, new Wall);

    r2->SetSide(North, new Wall); 
    r2->SetSide(East, new Wall); 
    r2->SetSide(South, new Wall); 
    r2->SetSide(West, theDoor);

    return aMaze;
}


int main() {
    MazeGame game;
    Maze* aMaze = game.CreateMaze();
    
    std::cout << "Hello Wor1d!" << std::endl;
    return 0;
}

// game.CreateMaze();
// class MazeFactory { 
// public: 
//     MazeFactory();

//     virtual Maze* MakeMazeO const 
//         { return new Maze; } 
        
//     virtual Wall* MakeWall() const
//         { return new Wall; } 
        
//     virtual Room* MakeRoom(int n) const
//         { return new Room(n); } 
        
//     virtual Door* MakeDoor(Room* r1, Room* r2) const
//         { return new Door(r1, r2); }
// }
