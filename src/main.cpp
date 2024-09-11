#include <iostream>
#include <cmath>
#include <vector>
#include <raylib.h>
#include <raymath.h>

using namespace std;

Color white = {255, 255, 255, 250};
Color green={157, 222, 139,250};
Color dgreen={64, 165, 120,250};
Color blue={0, 103, 105,255};
Color gray={183,183,183,250};
Color red={237, 198, 177,250};
Color yellow={230, 255, 148,250};
int score1 = 0;
int score2 = 0;

class Ball {
public:
    float x, y;
    Vector2 speed;
    int r;

    Ball(int rad, Vector2 s) : r(rad), speed(s) {
        x = (GetScreenWidth() - 1) / 2;
        y = (GetScreenHeight() - 1) / 2;
    }

    void Draw() {
        DrawCircle(x, y, r, yellow);
    }

    void Update() {
        if (y + r >= GetScreenHeight() || y - r <= 0)
            speed.y *= -1;
        if (x + r >= GetScreenWidth() || x - r <= 0)
            Reset();
        x += speed.x;
        y += speed.y;
    }

    void Accelerate(double t) {
        speed.x += t * (speed.x / abs(speed.x));
        speed.y += t * (speed.y / abs(speed.y));
    }

    void Reset() {
        x = (GetScreenWidth() - 1) / 2;
        y = (GetScreenHeight() - 1) / 2;
        speed = Vector2Scale(speed, -1);
    }
};

void UpdateScore(int x, int r) {
    if (x - r <= 0)
        score1++;
    if (x + r >= GetScreenWidth())
        score2++;
}

class Racket {
public:
    int v = GetScreenHeight() / 2;
    int l = GetScreenHeight() / 10;

    void Draw() {
        DrawRectangleRounded({(float)GetScreenWidth() * 98 / 100, (float)v - l, (float)2 * GetScreenWidth() / 100, (float)2 * l},10,5,blue);
    }

    void Move() {
        if (v - l <= 0) {
            v += 5;
        } else if (v + l >= GetScreenHeight()) {
            v -= 5;
        }
        if (IsKeyDown(KEY_DOWN))
            v += 5;
        if (IsKeyDown(KEY_UP))
            v -= 5;
    }
};

class AI {
public:
    int v = GetScreenHeight() / 2;
    int l = GetScreenHeight() / 10;

    void Draw() {
        DrawRectangleRounded({(float)0,(float) v - l, (float)2 * GetScreenWidth() / 100, (float)2 * l},10,5,blue);
            }

    void Move(Vector2 s) {
        if (v - l <= 0) {
            v += 6.5;
        } else if (v + l >= GetScreenHeight()) {
            v -= 6.5;
        }
        if (s.x <= 0) {
            v += (s.y > 0) ? 6.5 : -6.5;
        }
    }
};

int main() {
    InitWindow(1200, 700, "AI Will Win");
    SetTargetFPS(90);

    Ball b(20, {7, 6});
    Racket rac;
    AI ai;
    bool scene2=false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        scene2=(score1 == 10 || score2 == 10);
        if (scene2){
            ClearBackground(gray);
            DrawText((score2==10?"AI WINS":"YOU WIN"),GetScreenWidth()*2/7,GetScreenHeight()/3,100,blue);
            int w=120;
            Rectangle rec={(float) GetScreenWidth()/2-w,(float)GetScreenHeight()*6/10,(float)2*w,(float)w*2/3};
            
            //DrawRectangle(GetScreenWidth()/2-w,GetScreenHeight()*6/10,2*w,w*2/3,RED);
            
            if (CheckCollisionPointRec(GetMousePosition(),rec)){
                DrawRectangleRounded(rec,10,100,green);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    scene2=false;
                    score1=0;
                    score2=0;
                }
                    
            }
            else {
                DrawRectangleRounded(rec,10,100,dgreen);
            }
            DrawText("Play Again",GetScreenWidth()/2-w+16,GetScreenHeight()*6.3/10,40,BLACK);

        }else {

        ClearBackground(dgreen);

        DrawRectangle((GetScreenWidth() - 10) / 2, 0, 10, GetScreenHeight(), green);
        DrawCircle((GetScreenWidth()) / 2, GetScreenHeight() / 2, 50,green);

        b.Draw();
        b.Update();
        UpdateScore(b.x, b.r);

        rac.Draw();
        ai.Draw();
        rac.Move();
        ai.Move(b.speed);

        DrawText(TextFormat("Score: %01i", score2), GetScreenWidth() / 5, GetScreenHeight() / 20, 20, red);
        DrawText(TextFormat("Score: %01i", score1), 3 * GetScreenWidth() / 5, GetScreenHeight() / 20, 20, red);

        if (CheckCollisionCircleRec({b.x, b.y}, b.r, {(float)(GetScreenWidth() * 98 / 100), (float)(rac.v - rac.l), (float)(2 * GetScreenWidth() / 100), (float)(2 * rac.l)}))
            b.speed.x *= -1;

        if (CheckCollisionCircleRec({b.x, b.y}, b.r, {(float)(GetScreenWidth() * 2 / 100), (float)(ai.v - ai.l), (float)(2 * GetScreenWidth() / 100), (float)(2 * ai.l)}))
            b.speed.x *= -1;

       
        
        }
        
         EndDrawing();
    }

    CloseWindow();
    return 0;
}