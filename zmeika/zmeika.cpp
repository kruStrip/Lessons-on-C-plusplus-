#include <list>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <iostream>

enum Direction {
    up = 1,
    down = -1,
    left = 2,
    right = -2,
    none = 0
};

int w = 48;
int h = 20;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //возвращает

COORD apple() {
    COORD apple;
    apple.X = rand();
    apple.Y = rand();
    if (apple.X > 48) {
        apple.X %= 48;
    }

    if (apple.X == 0) {
        apple.X += 1;
    }
    else if (apple.X == 48) {
        apple.X -= 1;
    }
    if (apple.Y > 20) {
        apple.Y %= 20;
    }

    if (apple.Y == 0) {
        apple.Y += 1;
    }
    else if (apple.Y == 20) {
        apple.Y -= 1;
    };

    SetConsoleCursorPosition(console, apple);
    printf("\033[104m%c\033[0m", '@');
    SetConsoleCursorPosition(console, { short(48), short(20) });
    return apple;
}

struct Snake {
    std::list<COORD> snake; //.front - голова .back - конец, push_front, push_back, pop_front, pop_back
    Direction direction;

    Snake() {
        snake = { {20, 8}, {20, 9}, { 20, 10} };
        direction = Direction::up;
    }
    void move() {
        COORD b;
        COORD a = snake.front();
        if (direction == Direction::right) {
            b.X = a.X+1;
            b.Y = a.Y;
            snake.push_front(b);
            snake.pop_back();
        }
        else if (direction == Direction::up) {
            b.X = a.X;
            b.Y = a.Y - 1;
            snake.push_front(b);
            snake.pop_back();
        }
        else if (direction == Direction::left) {
            b.X = a.X - 1;
            b.Y = a.Y;
            snake.push_front(b);
            snake.pop_back();
        }
        else if (direction == Direction::down) {
            b.X = a.X;
            b.Y = a.Y+1;
            snake.push_front(b);
            snake.pop_back();
        }
        else if (direction == Direction::none) {
            b.X = a.X;
            b.Y = a.Y;
            snake.push_front(b);
            snake.pop_back();
        }
    }
    void cleanSnake() {
        SetConsoleCursorPosition(console, snake.back());
        printf("%c", ' ');
    }
    void drawSnake() {
        for (COORD c : snake) {
            SetConsoleCursorPosition(console, c);
            printf("\033[105m%c\033[0m", ' ');
        }
    }
    bool check() {
        COORD c = snake.front();
        COORD pos = { 0, 0 };
        if (c.X == 0 || c.Y == 0 || c.X == 48 || c.Y == 20) {
            return FALSE;
        }
    }
    COORD eat(COORD a, int*count) {
        COORD znaki = snake.front();
        COORD ass = snake.back();
        if ((znaki.X == a.X) && (znaki.Y == a.Y)) {
            snake.push_back(ass);
            a = apple();
            (*count)++;
        }
        return a;
    }
};



void drawFrame() {
    COORD pos = { 0, 0 };
    SetConsoleCursorPosition(console, pos);

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 48; j++) {
            SetConsoleCursorPosition(console, { short(j), short(i) });
            if (i != 0 && i != 19) {
                printf("\033[105m%c\033[0m", ' ');
                j += 47;
                SetConsoleCursorPosition(console, { short(j), short(i) });
                printf("\033[105m%c\033[0m", ' ');
                break;
            }
            printf("\033[105m%c\033[0m", ' ');
        }
    }
}


void getKey(Snake*snake) {
    Direction newDir = Direction::none;
    if (GetAsyncKeyState(VK_UP)) newDir = Direction::up;
    else if (GetAsyncKeyState(VK_LEFT)) newDir = Direction::left;
    else if (GetAsyncKeyState(VK_DOWN)) newDir = Direction::down;
    else if (GetAsyncKeyState(VK_RIGHT)) newDir = Direction::right;
    if (newDir == Direction::none) {
        return;
    }

    if (newDir != -snake->direction) snake->direction = newDir;
}

int main()
{
    setlocale(0, "");
    /*rand();*/ // 2 раза, для x и y    функция из которой мы не выходим пока не проиграли
    /*Sleep(300);*/ //цикл      отрисовка змейки как граница    удалить прошлое тело змейки
    srand(time(NULL));
    drawFrame();
    Snake s;
    COORD a = apple();
    int count = 0;
    while (true) {
        getKey(&s);
        a = s.eat(a, &count);
        s.cleanSnake();
        s.move();
        s.drawSnake();
        Sleep(300);
        if (s.check() == FALSE) {
            printf("Game over((((");
            return 0;
            }
        SetConsoleCursorPosition(console, { 50, 15 });
        printf("\033[95m%s%d\033[0m", "Счет: ", count);
        }
    return 0;
}