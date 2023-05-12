#include "rlImGui.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#include <iostream>

using namespace std;
#include <vector>
#include <map>


//Tests comment
Vector2 mousePOS;
Vector2 centerScreen = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
int main(void)
{
    Rectangle box = Rectangle{ -500,-500,30,80 };

    std::map<string, Rectangle> boxes;
    boxes["box1"] = { -500,-500,40,40 };
    boxes["box2"] = { -500,-500,150,200 };
    boxes["box3"] = { -500,-500,20,60 };
    boxes["box4"] = { -500,-500,80,50};
    boxes["box5"] = { -500,-500,250,15 };

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);

    int rotation;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello World!", 16, 9, 20, RED);
        mousePOS = GetMousePosition();

        int key = GetKeyPressed();
        switch (key)
        {
        case KEY_ONE:
            boxes["box1"].x = mousePOS.x - (boxes["box1"].width / 2);
            boxes["box1"].y = mousePOS.y - (boxes["box1"].height / 2);
            key = NULL;
            break;
        case KEY_TWO:
            boxes["box2"].x = mousePOS.x - (boxes["box2"].width / 2);
            boxes["box2"].y = mousePOS.y - (boxes["box2"].height / 2);
                key = NULL;
            break;
        case KEY_THREE:
            boxes["box3"].x = mousePOS.x - (boxes["box4"].width / 2);
            boxes["box3"].y = mousePOS.y - (boxes["box4"].height / 2);
                key = NULL;
            break;
        case KEY_FOUR:
            boxes["box4"].x = mousePOS.x - (boxes["box4"].width / 2);
            boxes["box4"].y = mousePOS.y - (boxes["box4"].height / 2);
                key = NULL;
            break;
        case KEY_FIVE:
            boxes["box5"].x = mousePOS.x - (boxes["box5"].width / 2);
            boxes["box5"].y = mousePOS.y - (boxes["box5"].height / 2);
                key = NULL;
            break;
        case KEY_BACKSPACE:
            for (auto& element : boxes)
            {
                element.second.x = -500;
            }

            break;
        }

        DrawRectanglePro(boxes["box1"], {0,0}, 0, GREEN);
        DrawRectanglePro(boxes["box2"], {0,0}, 0, RED);
        DrawRectanglePro(boxes["box3"], {0,0}, 0, BLUE);
        DrawRectanglePro(boxes["box4"], {0,0}, 0, PURPLE);
        DrawRectanglePro(boxes["box5"], {0,0}, 0, ORANGE);

     







         EndDrawing();
    }

    CloseWindow();
    return 0;
}