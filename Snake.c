#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define HEIGHT 20
#define WIDTH 60
#define MAX_TAIL 1000

enum Direction { UP, DOWN, LEFT, RIGHT, STOP };
enum Direction dir;

int Score = 0;
int fruit_x, fruit_y;
int head_x, head_y;
int tail_x[MAX_TAIL], tail_y[MAX_TAIL];
int tail_length = 0;

CHAR_INFO buffer[(HEIGHT + 2) * (WIDTH + 2)];
COORD bufferSize = { WIDTH + 2, HEIGHT + 2 };
COORD bufferCoord = { 0, 0 };
SMALL_RECT writeRegion = { 0, 0, WIDTH + 1, HEIGHT + 1 };

void setup();
void draw();
void game_loop();
void input();

int main() {
    srand(time(NULL));
    setup();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTitle("Snake Game");

    while (1) {
        input();
        game_loop();
        draw();
        WriteConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &writeRegion);

        // Print score and controls below the game area
        COORD infoPos = { 0, HEIGHT + 2 };
        SetConsoleCursorPosition(hConsole, infoPos);
        printf("Score: %d\tControls: W A S D | X = Stop\n", Score);

        Sleep(100);
    }

    return 0;
}

void setup() {
    head_x = WIDTH / 2;
    head_y = HEIGHT / 2;
    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HEIGHT;
    dir = STOP;
    tail_length = 0;
}

void draw() {
    for (int i = 0; i < HEIGHT + 2; i++) {
        for (int j = 0; j < WIDTH + 2; j++) {
            int index = i * (WIDTH + 2) + j;
            buffer[index].Char.AsciiChar = ' ';
            buffer[index].Attributes = FOREGROUND_GREEN;

            // Borders
            if (i == 0 || i == HEIGHT + 1 || j == 0 || j == WIDTH + 1) {
                buffer[index].Char.AsciiChar = '#';
                buffer[index].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
            }
            // Fruit
            else if (i - 1 == fruit_y && j - 1 == fruit_x) {
                buffer[index].Char.AsciiChar = 'F';
                buffer[index].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            }
            // Snake head
            else if (i - 1 == head_y && j - 1 == head_x) {
                buffer[index].Char.AsciiChar = 'O';
                buffer[index].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            }
            // Snake tail
            else {
                int isTail = 0;
                for (int k = 0; k < tail_length; k++) {
                    if (i - 1 == tail_y[k] && j - 1 == tail_x[k]) {
                        buffer[index].Char.AsciiChar = 'o';
                        buffer[index].Attributes = FOREGROUND_BLUE;
                        isTail = 1;
                        break;
                    }
                }
                if (!isTail) {
                    buffer[index].Char.AsciiChar = ' ';
                    buffer[index].Attributes = FOREGROUND_GREEN;
                }
            }
        }
    }
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
            case 'w': if (dir != DOWN) dir = UP; break;
            case 's': if (dir != UP) dir = DOWN; break;
            case 'a': if (dir != RIGHT) dir = LEFT; break;
            case 'd': if (dir != LEFT) dir = RIGHT; break;
            case 'x': dir = STOP; break;
        }
    }
}

void game_loop() {
    // Move tail
    for (int i = tail_length - 1; i > 0; i--) {
        tail_x[i] = tail_x[i - 1];
        tail_y[i] = tail_y[i - 1];
    }
    if (tail_length > 0) {
        tail_x[0] = head_x;
        tail_y[0] = head_y;
    }

    // Move head
    switch (dir) {
        case UP: head_y--; break;
        case DOWN: head_y++; break;
        case LEFT: head_x--; break;
        case RIGHT: head_x++; break;
        case STOP: break;
    }

    // Wrap around
    if (head_x < 0) head_x = WIDTH - 1;
    else if (head_x >= WIDTH) head_x = 0;
    if (head_y < 0) head_y = HEIGHT - 1;
    else if (head_y >= HEIGHT) head_y = 0;

    // Eat fruit
    if (head_x == fruit_x && head_y == fruit_y) {
        Score += 10;
        if (tail_length < MAX_TAIL) tail_length++;
        fruit_x = rand() % WIDTH;
        fruit_y = rand() % HEIGHT;
    }
}