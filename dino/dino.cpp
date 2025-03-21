#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

void moveTo(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void pause(unsigned int milliseconds) {
    clock_t goal = milliseconds + clock();
    while (goal > clock());
}

void displayGameInfo() {
    system("cls");
    moveTo(10, 2);
    cout << "Press X to Exit, Press Space to Jump";
    moveTo(62, 2);
    cout << "SCORE : ";
    moveTo(1, 25);
    for (int x = 0; x < 79; x++)
        cout << "п";
}

int jumpHeight = 0, gameSpeed = 40;

void displayCharacter(int jumpType = 0) {
    static int animationState = 1;
    
    if (jumpType == 0)
        jumpHeight = 0;
    else if (jumpType == 2)
        jumpHeight--;
    else
        jumpHeight++;
    
    moveTo(2, 15 - jumpHeight);
    cout << "                ";
    moveTo(2, 16 - jumpHeight);
    cout << "     мллл      ";
    moveTo(2, 17 - jumpHeight);
    cout << "    ллллллл     ";
    moveTo(2, 18 - jumpHeight);
    cout << "   ллллллллл    ";
    moveTo(2, 19 - jumpHeight);
    cout << "  лллллплллл   ";
    moveTo(2, 20 - jumpHeight);
    cout << " млллллппллллм  ";
    moveTo(2, 21 - jumpHeight);
    cout << " ллллллпплллллл ";
    moveTo(2, 22 - jumpHeight);
    cout << " пллллллппллллп ";
    moveTo(2, 23 - jumpHeight);
    
    if (jumpType == 1 || jumpType == 2) {
        cout << "   ллп плпппл   ";
        moveTo(2, 24 - jumpHeight);
        cout << "   лм   лм      ";
    }
    else if (animationState == 1) {
        cout << "  пллп  ппп     ";
        moveTo(2, 24 - jumpHeight);
        cout << "     лм         ";
        animationState = 2;
    }
    else {
        cout << "   плм пл       ";
        moveTo(2, 24 - jumpHeight);
        cout << "         лм     ";
        animationState = 1;
    }
    
    moveTo(2, 25 - jumpHeight);
    cout << (jumpType != 0 ? "                " : "ппппппппппппппппп");
    
    pause(gameSpeed);
}

void displayObstacle() {
    static int obstaclePosition = 0, score = 0;
    
    if (obstaclePosition == 56 && jumpHeight < 4) {
        score = 0;
        gameSpeed = 40;
        moveTo(36, 8);
        cout << "Game Over";
        getch();
        moveTo(36, 8);
        cout << "         ";
    }
    
    moveTo(74 - obstaclePosition, 20);
    cout << "л    л ";
    
    obstaclePosition++;
    if (obstaclePosition == 73) {
        obstaclePosition = 0;
        score++;
        moveTo(70, 2);
        cout << "     ";
        moveTo(70, 2);
        cout << score;
        if (gameSpeed > 20)
            gameSpeed--;
    }
}

int main() {
    system("mode con: lines=29 cols=82");
    char input;
    int i;
    displayGameInfo();
    
    while (true) {
        while (!_kbhit()) {
            displayCharacter();
            displayObstacle();
        }
        
        input = _getch();
        if (input == ' ') {
            for (i = 0; i < 10; i++) {
                displayCharacter(1);
                displayObstacle();
            }
            for (i = 0; i < 10; i++) {
                displayCharacter(2);
                displayObstacle();
            }
        }
        else if (input == 'x') {
            return 0;
        }
    }
}
