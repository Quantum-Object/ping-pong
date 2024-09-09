#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include<cmath>
#include <vector>

using namespace std;

int main()
{
    
    InitWindow("Game of Life");
    SetTargetFPS(12);


    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(DARKBLUE);
  
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}