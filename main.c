// to run this program in terminal> make run


#include <stdio.h>
#include "raylib.h"

int main(void){
    printf("Hellow");
    // setting constants
    const int screenWidth = 800;
    const int screenHeight = 800;

    Vector2 topLeft = {0, 0};
    Vector2 topRight = {screenWidth, 0};
    Vector2 bottomLeft = {0, screenHeight};
    Vector2 bottomRight = {screenWidth, screenHeight};


    // Vector2 bottom = {screenHeight, screenWidth+screenWidth};

    InitWindow(screenWidth, screenHeight, "raylib sandbox");

    SetTargetFPS(60);

    const int paddleWidth = 30;
    const int paddleHeight = 90;
    const int playerSpeed = 4;

    Vector2 velocity = {-5,-10};


    Vector2 ballPosition = {300, 300};
    int radius = 50;
    Color ballColor = {100, 100, 100, 100};

    Rectangle playerOne = {10,180,paddleWidth,paddleHeight};
    Color playerOneColor = {100, 100, 100, 255};

    Rectangle playerTwo = {750, 110, paddleWidth, paddleHeight};
    Color playerTwoColor = {100, 100, 100, 255};

    bool collisionOne;
    bool collisionTwo;
    bool topCollision;
    bool bottomCollision;
    bool leftGoal;
    bool rightGoal;



    while(!WindowShouldClose()){

        if(IsKeyDown(KEY_UP)) playerOne.y -= playerSpeed;
        if(IsKeyDown(KEY_DOWN)) playerOne.y += playerSpeed;

        if(IsKeyDown(KEY_W)) playerTwo.y -= playerSpeed;
        if(IsKeyDown(KEY_S)) playerTwo.y += playerSpeed;

        collisionOne = CheckCollisionCircleRec(ballPosition, radius, playerOne);
        collisionTwo = CheckCollisionCircleRec(ballPosition, radius, playerTwo);
        topCollision =  CheckCollisionCircleLine(ballPosition, radius, topLeft, topRight);
        bottomCollision =  CheckCollisionCircleLine(ballPosition, radius, bottomLeft, bottomRight);

        leftGoal = CheckCollisionCircleLine(ballPosition, radius, topLeft, bottomLeft);
        rightGoal = CheckCollisionCircleLine(ballPosition, radius, topRight, bottomRight);


        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("HELLOW",190 ,200 , 20, LIGHTGRAY);
            DrawCircle(ballPosition.x, ballPosition.y, radius, ballColor);

            DrawRectangle(playerOne.x, playerOne.y, playerOne.width, playerOne.height, playerOneColor);
            DrawRectangle(playerTwo.x, playerTwo.y, paddleWidth, paddleHeight, playerTwoColor);

            if (topCollision){
                DrawText("HIT TOP",300, 300 , 20, LIGHTGRAY);
                velocity.y *= -1;
            }
            if (bottomCollision){
                DrawText("HIT bottom",300, 300 , 20, LIGHTGRAY);
                velocity.y *= -1;
            }
            if (leftGoal){
                DrawText("P2 GOALLL",300, 300 , 20, LIGHTGRAY);
                ballPosition.x = 300;
                ballPosition.y = 300;
            }
            if (rightGoal){
                DrawText("P1 GOALLLL",300, 300 , 20, LIGHTGRAY);
                ballPosition.x = 300;
                ballPosition.y = 300;

            }


            if (collisionOne || collisionTwo) {
                playerOneColor.r = 255;
                velocity.x *= -1;
            }
            else playerOneColor.r = 100;

            ballPosition.x = ballPosition.x + velocity.x;
            ballPosition.y = ballPosition.y + velocity.y;



        EndDrawing();
    }

    CloseWindow();
        return 0;
    }
