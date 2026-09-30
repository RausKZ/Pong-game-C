#include "raylib.h"

void Movement(Rectangle *Player){
    if(IsKeyDown(KEY_W)){
        Player->y-=3;
        if(Player->y <= 0)
            Player->y = 0;
    }
    if(IsKeyDown(KEY_S)){
        Player->y+=3;
        if(Player->y >= 300)
        Player->y = 300;
    }
}

void Movement2(Rectangle *Player){
    if(IsKeyDown(KEY_UP)){
        Player->y-=3;
        if(Player->y <= 0)
            Player->y = 0;
    }
    if(IsKeyDown(KEY_DOWN)){
        Player->y+=3;
        if(Player->y >= 300)
        Player->y = 300;
    }
}

void Ballphysics(int *BallposX, int *BallposY,int check){
    int static count = 0;
    int static count2 = 0;
    if(check == 1){
        count2++;
    }
    if(count%2==0){
        *BallposY -= 3;
    }else{
        *BallposY += 3;
    }
    if(count2%2==0){
        *BallposX -= 3;
    }else{
        *BallposX += 3;
    }
    if((*BallposY + 10) >= 450 || (*BallposY - 10) <= 0){
        count++;
    }
    if((*BallposX - 10) <= 0 ||(*BallposX + 10) >= 800){
        count2++;
    }
}

void Scoreboard(int Score){
    int static Score1 = 0;
    int static Score2 = 0;
    if(Score == 0){
        Score1++;
    }else if (Score == 1){
        Score2++;
    }
    DrawText(TextFormat("%d", Score1),350, 20, 20, WHITE);
    DrawText(TextFormat("%d", Score2),450, 20, 20, WHITE);
}

void ResetPos(int *BallposX, int *BallposY){
    *BallposX = 400;
    *BallposY = 225;
}

int main(){
    InitWindow(800, 450, "Pong");
    int BallposX = 400;
    int BallposY = 225;
    int Ballspeed = 3;
    int gamespeed = 60;
    Rectangle PLAYER1 = {50,150,20,150};
    Rectangle PLAYER2 = {750,150,20,150};
    SetTargetFPS(gamespeed);
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
                Scoreboard(3);
            DrawRectangleRec(PLAYER1,WHITE);
                Movement(&PLAYER1);
            DrawRectangleRec(PLAYER2,WHITE);
                Movement2(&PLAYER2);
            DrawCircle(BallposX,BallposY,10,WHITE);
                Ballphysics(&BallposX,&BallposY,0);
        Vector2 Ball = {BallposX,BallposY};
        if(CheckCollisionCircleRec(Ball,10,PLAYER1)){
            Ballphysics(&BallposX,&BallposY,1);
            gamespeed*=2;
            if(gamespeed >= 240){
                gamespeed = 240;
            }
            SetTargetFPS(gamespeed);
        }
        if(CheckCollisionCircleRec(Ball,10,PLAYER2)){
            Ballphysics(&BallposX,&BallposY,1);
            gamespeed*=2;
            if(gamespeed >= 240){
                gamespeed = 240;
            }
            SetTargetFPS(gamespeed);
        }
        if((BallposX -10) == 0){
            ResetPos(&BallposX,&BallposY);
            Scoreboard(1);
            gamespeed = 60;
            SetTargetFPS(gamespeed);
        }else if((BallposX + 10) == 800){
            ResetPos(&BallposX,&BallposY);
            Scoreboard(0);
            gamespeed = 60;
            SetTargetFPS(gamespeed);
        }
            EndDrawing();    
    };

    CloseWindow();

    return 0;
}