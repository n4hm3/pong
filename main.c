

#include <stdio.h>
#include "raylib.h"


typedef enum State {
    PLAY,
    GOAL
    // add a paused state
} state_t;

void drawScore(int scoreOne, int scoreTwo){
    char scoreOneString [20];
    char scoreTwoString [20];

    sprintf(scoreOneString, "%d", scoreOne);
    sprintf(scoreTwoString, "%d", scoreTwo);

    DrawText(scoreOneString, 250 ,10 , 20, LIGHTGRAY);
    DrawText(scoreTwoString, 350 ,10 , 20, LIGHTGRAY);
}



int main(void){
    printf("Hellow");



    state_t gameState = PLAY;

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
    const int paddleHeight = 110;
    const int playerSpeed = 4;

    Vector2 velocity = {-5,-6};


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

    int playerOneScore = 0;
    int playerTwoScore = 0;

    double startTime;


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
            switch (gameState) {
                case PLAY:
                    DrawText("HELLOW",190 ,200 , 20, LIGHTGRAY);
                    drawScore(playerOneScore, playerTwoScore);

                    DrawCircle(ballPosition.x, ballPosition.y, radius, ballColor);

                    DrawRectangle(playerOne.x, playerOne.y, playerOne.width, playerOne.height, playerOneColor);
                    DrawRectangle(playerTwo.x, playerTwo.y, paddleWidth, paddleHeight, playerTwoColor);

                    if (topCollision){
                        velocity.y *= -1;
                    }
                    if (bottomCollision){
                        velocity.y *= -1;
                    }
                    if (leftGoal){
                        ballPosition.x = 300;
                        ballPosition.y = 300;
                        playerTwoScore++;
                        startTime = GetTime();
                        gameState = GOAL;
                    }
                    if (rightGoal){
                        ballPosition.x = 300;
                        ballPosition.y = 300;
                        playerOneScore++;
                        startTime = GetTime();
                        gameState = GOAL;
                    }


                    if (collisionOne || collisionTwo) {
                        playerOneColor.r = 255;
                        velocity.x *= -1;
                        velocity.y *= -1;
                    }
                    else playerOneColor.r = 100;

                    ballPosition.x = ballPosition.x + velocity.x;
                    ballPosition.y = ballPosition.y + velocity.y;
                    break;
                case GOAL:
                    if ((GetTime() - startTime) > 1){
                        gameState = PLAY;
                    }
                    ClearBackground(BLACK);
                    DrawText("GOALLLLL",190 ,200 , 100, LIGHTGRAY);
                    break;
        }
        EndDrawing();

    }

    CloseWindow();
        return 0;
    }
