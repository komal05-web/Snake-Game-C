#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 60
#define HEIGHT 20

typedef struct SnakeSegment {
    int x, y;
    struct SnakeSegment* next;
} SnakeSegment;

SnakeSegment* head = NULL;
int fruit_x, fruit_y;
int score = 0;
enum Direction { UP, DOWN, LEFT, RIGHT, STOP };
enum Direction dir = STOP;

CHAR_INFO buffer[(HEIGHT + 2) * (WIDTH + 2)];
COORD bufferSize = { WIDTH + 2, HEIGHT + 2 };
COORD bufferCoord = { 0, 0 };
SMALL_RECT writeRegion = { 0, 0, WIDTH + 1, HEIGHT + 1 };

void setup();
void draw();
void input();
void update();
void add_head(int x, int y);
void remove_tail();
int check_collision(int x, int y);

int main() {
    srand(time(NULL));
    setup();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTitle("Snake Game with Linked List");

    while (1) {
        input();
        update();
        draw();
        WriteConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &writeRegion);

        COORD infoPos = { 0, HEIGHT + 2 };
        SetConsoleCursorPosition(hConsole, infoPos);
        printf("Score: %d\tControls: W A S D | X = Stop\n", score);

        Sleep(100);
    }

    return 0;
}

void setup() {
    add_head(WIDTH / 2, HEIGHT / 2);
    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HEIGHT;
}

void add_head(int x, int y) {
    SnakeSegment* newSegment = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    newSegment->x = x;
    newSegment->y = y;
    newSegment->next = head;
    head = newSegment;
}

void remove_tail() {
    if (!head || !head->next) return;

    SnakeSegment* current = head;
    while (current->next->next) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
}

int check_collision(int x, int y) {
    SnakeSegment* current = head->next;
    while (current) {
        if (current->x == x && current->y == y) return 1;
        current = current->next;
    }
    return 0;
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

void update() {
    if (!head) return;

    int new_x = head->x;
    int new_y = head->y;

    switch (dir) {
        case UP: new_y--; break;
        case DOWN: new_y++; break;
        case LEFT: new_x--; break;
        case RIGHT: new_x++; break;
        case STOP: return;
    }

    if (new_x < 0) new_x = WIDTH - 1;
    else if (new_x >= WIDTH) new_x = 0;
    if (new_y < 0) new_y = HEIGHT - 1;
    else if (new_y >= HEIGHT) new_y = 0;

    if (check_collision(new_x, new_y)) {
        system("cls");
        printf("Game Over! Final Score: %d\n", score);
        exit(0);
    }

    add_head(new_x, new_y);

    if (new_x == fruit_x && new_y == fruit_y) {
        score += 10;
        fruit_x = rand() % WIDTH;
        fruit_y = rand() % HEIGHT;
    } else {
        remove_tail();
    }
}

void draw() {
    for (int i = 0; i < HEIGHT + 2; i++) {
        for (int j = 0; j < WIDTH + 2; j++) {
            int index = i * (WIDTH + 2) + j;
            buffer[index].Char.AsciiChar = ' ';
            buffer[index].Attributes = FOREGROUND_GREEN;

            if (i == 0 || i == HEIGHT + 1 || j == 0 || j == WIDTH + 1) {
                buffer[index].Char.AsciiChar = '#';
                buffer[index].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
            } else if (i - 1 == fruit_y && j - 1 == fruit_x) {
                buffer[index].Char.AsciiChar = 'F';
                buffer[index].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            } else {
                int found = 0;
                SnakeSegment* current = head;
                while (current) {
                    if (i - 1 == current->y && j - 1 == current->x) {
                        buffer[index].Char.AsciiChar = (current == head) ? 'O' : 'o';
                        buffer[index].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                        found = 1;
                        break;
                    }
                    current = current->next;
                }
                if (!found) {
                    buffer[index].Char.AsciiChar = ' ';
                    buffer[index].Attributes = FOREGROUND_GREEN;
                }
            }
        }
    }
}
