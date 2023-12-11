#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

// Function to set the cursor position
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to draw a paddle
void drawPaddle(int x, int y) {
    gotoxy(x, y);
    cout << "▓▓▓";
}

// Function to draw the ball
void drawBall(int x, int y) {
    gotoxy(x, y);
    cout << "O";
}

int main() {
    // Set up the console window
    system("cls");
    system("title ATARI 800XL - CLASSIC PONG");
    system("color F0");
    srand(time(NULL));

    // Initialize variables
    int width = 40;
    int height = 20;
    int paddleLength = 3;
    int ballX = width / 2;
    int ballY = height / 2;
    int ballDeltaX = 1;
    int ballDeltaY = 1;
    int paddleAY = height / 2 - paddleLength / 2;
    int paddleBY = height / 2 - paddleLength / 2;
    int scoreA = 0;
    int scoreB = 0;

    // Main game loop
    while (true) {
        // Draw paddles and ball
        system("cls");
        drawPaddle(0, paddleAY);
        drawPaddle(width - 3, paddleBY);
        drawBall(ballX, ballY);

        // Move the ball
        ballX += ballDeltaX;
        ballY += ballDeltaY;

        // Border checking - top and bottom
        if (ballY == 0 || ballY == height - 1)
            ballDeltaY *= -1;

        // Border checking - right and left
        if (ballX == width - 1) {
            ballX = width / 2;
            ballY = height / 2;
            ballDeltaX *= -1;
            scoreA++;
        }

        if (ballX == 0) {
            ballX = width / 2;
            ballY = height / 2;
            ballDeltaX *= -1;
            scoreB++;
        }

        // Paddle and ball collision
        if ((ballX == width - 4) && (ballY >= paddleBY && ballY < paddleBY + paddleLength))
            ballDeltaX *= -1;

        if ((ballX == 3) && (ballY >= paddleAY && ballY < paddleAY + paddleLength))
            ballDeltaX *= -1;

        // Update score
        gotoxy(width / 2, 0);
        cout << "Player A: " << scoreA << "  ||  Player B: " << scoreB;

        // Input handling
        if (_kbhit()) {
            char key = _getch();
            if (key == 'w' && paddleAY > 0)
                paddleAY--;
            if (key == 's' && paddleAY < height - paddleLength)
                paddleAY++;
            if (key == 'o' && paddleBY > 0)
                paddleBY--;
            if (key == 'l' && paddleBY < height - paddleLength)
                paddleBY++;
        }

        // Pause to make the game playable
        Sleep(50);
    }

    return 0;
}
