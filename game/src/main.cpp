#include "rlImGui.h"
#define SCREEN_WIDTH 576
#define SCREEN_HEIGHT 800
#include <iostream>

using namespace std;
#include <vector>
#include <map>


//Tests comment
Vector2 centerScreen = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
Vector2 mousePOS;

int main(void)
{
    float buttonRadius = 50;
    Rectangle backScreen = Rectangle{0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
    Rectangle readScreen = { backScreen.width * .025,backScreen.height * .11,backScreen.width * .95,130 };
    map<string, Vector2> button;
    button["one"] = {static_cast<float>(backScreen.width * .12),static_cast<float>(backScreen.height * .85)};
    button["two"] = {button["one"].x+(buttonRadius*2)+33,button["one"].y};
    button["three"] = {button["two"].x+(buttonRadius*2)+33,button["two"].y};
    button["four"] = {button["one"].x,button["one"].y - (buttonRadius*2)-25};
    button["five"] = {button["two"].x,button["four"].y};
    button["six"] = {button["three"].x,button["four"].y};
    button["seven"] = {button["four"].x,button["four"].y-(buttonRadius*2)-25};
    button["eight"] = {button["five"].x,button["seven"].y};
    button["nine"] = {button["six"].x,button["eight"].y};
    button["zero"] = {0,0};
    button["equal"] = {0,0};
    button["minus"] = {0,0};
    button["plus"] = {0,0};
    button["multiply"] = {0,0};
    button["divide"] = {0,0};
    button["clear"] = {0,0};
    button["point"] = { 0,0 };


    {   /*
        std::map<string, Rectangle> boxes;
        boxes["box1"] = { -500,-500,40,40 };
        boxes["box2"] = { -500,-500,150,200 };
        boxes["box3"] = { -500,-500,20,60 };
        boxes["box4"] = { -500,-500,80,50 };
        boxes["box5"] = { -500,-500,250,15 };
        //*/
    }
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);

    int rotation;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        //DrawText("Hello World!", 16, 9, 20, RED);

        //Set Mouse Position x and y to new Var
        mousePOS = GetMousePosition();
        //Set which key is press to new Var
        int key = GetKeyPressed();
      
        //Adding Rectangles
        {   /*
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
                boxes["box3"].x = mousePOS.x - (boxes["box3"].width / 2);
                boxes["box3"].y = mousePOS.y - (boxes["box3"].height / 2);
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
            //Drawing Rectangles
            DrawRectanglePro(boxes["box1"], { 0,0 }, 0, GREEN);
            DrawRectanglePro(boxes["box2"], { 0,0 }, 0, RED);
            DrawRectanglePro(boxes["box3"], { 0,0 }, 0, BLUE);
            DrawRectanglePro(boxes["box4"], { 0,0 }, 0, PURPLE);
            DrawRectanglePro(boxes["box5"], { 0,0 }, 0, ORANGE);
            //*/
        }
        
        DrawRectangleRounded(backScreen, .25, 0, { 42, 47, 79,255 });
        DrawRectangleRounded(readScreen, .10, 0, { 145, 127, 179,200 });
        DrawCircleV(button["one"], buttonRadius, {229, 190, 236,255});
        DrawCircleV(button["two"], buttonRadius, { 229, 190, 236,255 });
        DrawCircleV(button["three"], buttonRadius, { 229, 190, 236,255 });
        DrawCircleV(button["four"], buttonRadius, { 229, 190, 236,255 });
        DrawCircleV(button["five"], buttonRadius, { 229, 190, 236,255 });
        DrawCircleV(button["six"], buttonRadius, { 229, 190, 236,255 });
        DrawCircleV(button["seven"], buttonRadius, { 229, 190, 236,255 });
        DrawCircleV(button["eight"], buttonRadius, { 229, 190, 236,255 });
        DrawCircleV(button["nine"], buttonRadius, { 229, 190, 236,255 });
        DrawCircleV(button["zero"], buttonRadius, { 229, 190, 236,255 });
        DrawCircleV(button["clear"], buttonRadius, { 229, 190, 236,255 });




         EndDrawing();
    }

    CloseWindow();
    return 0;
}