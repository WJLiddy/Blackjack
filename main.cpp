#include <iostream>
#include <raylib.h>
#include <list>
#include <functional>
#include "deal.h"
#include <iostream>

using namespace std;

#define Y_OFFSET 2
#define X_OFFSET 2
#define CELL_SIZE 20

int score = 0;

void drawTable(Strategy &s)
{
    int y = Y_OFFSET;
    for (int p = Strategy::PLAYER_MIN; p <= Strategy::PLAYER_MAX; ++p)
    {
        int x = X_OFFSET;
        DrawText(std::to_string(p).c_str(), x * CELL_SIZE, y * CELL_SIZE, 10, RED);
        ++x;
        for (int d = Strategy::DEALER_MIN; d <= Strategy::DEALER_MAX; ++d)
        {
            if (y == 2)
            {
                DrawText(std::to_string(d).c_str(), x * CELL_SIZE, (y - 1) * CELL_SIZE, 10, RED);
            }

            auto action = s.getAction(p, d);
            switch (action)
            {
            case Strategy::PlayerAction::H:
                DrawText("H", x * 20, y * 20, 10, GREEN);
                break;
            case Strategy::PlayerAction::S:
                DrawText("S", x * 20, y * 20, 10, WHITE);
                break;
            case Strategy::PlayerAction::D:
                DrawText("D", x * 20, y * 20, 10, BLUE);
                break;
            }
            ++x;
        }
        ++y;
    }
}

void checkInput(Strategy &s)
{
    auto mousePosition = GetMousePosition();

    int x = (mousePosition.x - ((-1.5 + X_OFFSET) * (CELL_SIZE))) / CELL_SIZE;
    int y = (mousePosition.y - ((-2 + Y_OFFSET) * (CELL_SIZE))) / CELL_SIZE;
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        s.setAction(y, x, Strategy::PlayerAction::H);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        s.setAction(y, x, Strategy::PlayerAction::S);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
    {
        s.setAction(y, x, Strategy::PlayerAction::D);
    }
}


void drawButtons(Strategy &s, std::list<std::tuple<Color,std::string>>& res2)
{
    Rectangle btn1{280.0f, 30.0f, 130.0f, 20.0f};
    auto mousePosition = GetMousePosition();
    DrawRectangleRec(btn1, WHITE);
    DrawText("Simulate 50000 Hands", btn1.x + 10, btn1.y + 10, 10, BLACK);

    if (CheckCollisionPointRec(mousePosition, btn1))
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            score = 0;
            res2.clear();
            for (int i = 0; i != 50000; ++i)
            {
                Deal d;
                int res = d.execute(s);
                score += res;
                Color c;
                switch (res)
                {
                case -2:
                    c = RED;
                    break;
                case -1:
                    c = ORANGE;
                    break;
                case 0:
                    c = WHITE;
                    break;
                case 1:
                    c = GREEN;
                    break;
                case 2:
                    c = BLUE;
                    break;
                }
                auto tup = std::make_tuple(c, d.print());
                res2.push_back(tup);
            }
        }
    }
}

void drawText(std::list<std::tuple<Color,std::string>>& res2)
{
    int y = 60;
    for(auto tup : res2)
    {
        auto c = std::get<0>(tup);
        auto s = std::get<1>(tup);
        DrawText(s.c_str(), 290, y, 10, c);
        y += 10;
    }
    DrawText(std::to_string(100.0 + (score*100.0 / 50000.0)).substr(0,5).c_str(), 50, 500, 40, WHITE);
}

int main()
{
    Strategy s;
    std::list<std::tuple<Color,std::string>> out;

    cout << "Hello World" << endl;

    InitWindow(500, 600, "Blackjack!");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        drawTable(s);
        drawButtons(s,out);
        drawText(out);
        checkInput(s);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}